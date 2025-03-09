/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: turkish_nlp.h
 * Açıklama: Türkçe doğal dil işleme modülü
 * Bağımlılıklar: string, vector, map
 * 
 * Versiyon: 0.3.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_TURKISH_NLP_H
#define ASRPRO_TURKISH_NLP_H

#include <string>
#include <vector>
#include <map>
#include "debug/error_handler.h"

namespace asrpro {
namespace turkish {

class TurkishNLP {
public:
    // Türkçe ses bilgisi yapısı
    struct Phonology {
        std::vector<std::string> vowels{"a","e","ı","i","o","ö","u","ü"};
        std::vector<std::string> consonants{
            "b","c","ç","d","f","g","ğ","h","j","k",
            "l","m","n","p","r","s","ş","t","v","y","z"
        };
        
        // Ses uyumu kuralları
        bool checkVowelHarmony(const std::string& word);
        bool checkConsonantHarmony(const std::string& word);
    };

    // Türkçe morfoloji yapısı
    struct Morphology {
        std::map<std::string, std::string> suffixes;
        std::vector<std::string> stems;
        
        bool analyzeMorphemes(const std::string& word, 
                            std::vector<std::string>& morphemes);
    };

    // Yapılandırma
    struct Config {
        bool useStemmingCache{true};    // Gövde bulma önbelleği
        bool useMorphologyCache{true};  // Morfoloji önbelleği
        std::string dictionaryPath;     // Sözlük dosya yolu
    };

    bool init(const Config& config);
    bool processText(const std::string& input, std::string& normalized);
    std::vector<std::string> tokenize(const std::string& text);

private:
    Phonology phonology;
    Morphology morphology;
    Config config;
    bool initialized{false};
};

} // namespace turkish
} // namespace asrpro

#endif // ASRPRO_TURKISH_NLP_H