/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: turkish_tts.h
 * Açıklama: Türkçe metin okuma modülü
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

class TurkishTTS {
public:
    // Ses sentezi yapılandırması
    struct Config {
        float speechRate;      // Konuşma hızı (0.5-2.0)
        float pitch;           // Ses tonu (0.5-2.0)
        std::string voiceId;   // Ses karakteri ID
        bool useEmphasis;      // Vurgu kullanımı
    };

    // Türkçe telaffuz kuralları
    struct PronunciationRules {
        bool applyVowelHarmony;     // Ünlü uyumu
        bool applyConsonantHarmony; // Ünsüz uyumu
        bool useStressMarking;      // Vurgu işaretleri
    };
};