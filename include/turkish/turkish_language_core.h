/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: turkish_language_core.h
 * Açıklama: Türkçe dil çekirdeği
 * Bağımlılıklar: stdint.h, vector, string
 * 
 * Versiyon: 0.2.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

class TurkishLanguageCore {
public:
    // Türkçe karakter seti
    static const std::vector<char> TURKISH_CHARS;
    
    // Türkçe ses-harf eşleşmeleri
    struct PhonemeMap {
        std::string grapheme;  // Yazılı form
        std::string phoneme;   // Ses formu
        float frequency;       // Kullanım sıklığı
    };

    // Türkçe dilbilgisi kuralları
    struct GrammarRules {
        bool vowelHarmony;     // Büyük ünlü uyumu
        bool consonantHarmony;  // Ünsüz benzeşmesi
        bool finalDevoicing;    // Ünsüz yumuşaması
    };

    // Dil modeli parametreleri
    struct ModelParams {
        float beamWidth;       // Işın genişliği
        float lmWeight;        // Dil modeli ağırlığı
        float wakeWordBoost;   // Tetikleme kelimesi güçlendirme
    };
};