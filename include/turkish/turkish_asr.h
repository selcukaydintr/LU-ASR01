/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: turkish_asr.h
 * Açıklama: Türkçe konuşma tanıma modülü
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

class TurkishASR {
public:
    // Türkçe fonem seti
    static const std::vector<std::string> PHONEMES = {
        "a", "e", "ı", "i", "o", "ö", "u", "ü",  // Ünlüler
        "b", "c", "ç", "d", "f", "g", "ğ", "h",  // Ünsüzler
        "j", "k", "l", "m", "n", "p", "r", "s",
        "ş", "t", "v", "y", "z"
    };

    // Akustik model ve dil modeli yapılandırması
    struct Config {
        std::string acousticModelPath;
        std::string languageModelPath;
        float beamWidth;
        bool enablePunctuation;
    };
};