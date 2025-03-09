/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: turkish_language_processor.h
 * Açıklama: Türkçe dil işleme modülü
 * Bağımlılıklar: string, vector, map, debug/error_handler.h
 * 
 * Versiyon: 0.4.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_TURKISH_LANGUAGE_PROCESSOR_H
#define ASRPRO_TURKISH_LANGUAGE_PROCESSOR_H

#include <string>
#include <vector>
#include <map>
#include "debug/error_handler.h"

namespace asrpro {
namespace turkish {

// Türkçe lehçe/ağız yapısı
enum class TurkishDialect {
    STANDARD,   // Standart İstanbul Türkçesi
    KARADENIZ, // Karadeniz ağzı
    DOGU,      // Doğu Anadolu ağzı
    IC_ANADOLU, // İç Anadolu ağzı
    EGE        // Ege ağzı
};

class TurkishLanguageProcessor {
public:
    // Yapılandırma
    struct Config {
        TurkishDialect dialect{TurkishDialect::STANDARD};
        bool useVowelHarmony{true};
        bool useConsonantHarmony{true};
        bool enableSpellCheck{true};
        std::string customDictionaryPath;
    };

    // Morfolojik analiz sonucu
    struct MorphologicalResult {
        std::vector<std::string> stems;
        std::vector<std::string> suffixes;
        std::vector<std::string> phonemes;
        float confidence;
    };

    bool init(const Config& config);
    
    // Dil işleme
    bool processText(const std::string& input, std::string& normalized);
    bool extractPhonemes(const std::string& text, std::vector<std::string>& phonemes);
    bool analyzeGrammar(const std::string& text, std::vector<std::string>& errors);
    
    // Lehçe desteği
    bool convertToDialect(const std::string& input, 
                         TurkishDialect dialect,
                         std::string& output);

private:
    Config config;
    bool initialized{false};

    // Türkçe ses kuralları kontrolü
    bool checkVowelHarmony(const std::string& word);
    bool checkConsonantHarmony(const std::string& word);
    bool validateWord(const std::string& word);
};

} // namespace turkish
} // namespace asrpro

#endif // ASRPRO_TURKISH_LANGUAGE_PROCESSOR_H