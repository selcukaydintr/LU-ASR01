/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: audio_types.h
 * Açıklama: Ses işleme için temel veri tipleri
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_AUDIO_TYPES_H
#define ASRPRO_AUDIO_TYPES_H

#include <cstdint>
#include <vector>

namespace asrpro {
namespace audio {

// Ses formatı yapılandırması
struct AudioFormat {
    uint32_t sampleRate;    // Örnekleme hızı (Hz)
    uint16_t channelCount;  // Kanal sayısı
    uint16_t bitsPerSample; // Örnek başına bit
};

// Ses tamponu
class AudioBuffer {
public:
    AudioBuffer(size_t size) : data_(size) {}
    
    int16_t* data() { return data_.data(); }
    const int16_t* data() const { return data_.data(); }
    size_t size() const { return data_.size(); }

private:
    std::vector<int16_t> data_;
};

// MFCC öznitelik vektörü
struct MFCCFeatures {
    std::vector<float> coefficients;
    uint32_t frameCount;
    uint32_t coeffCount;
};

} // namespace audio
} // namespace asrpro

#endif // ASRPRO_AUDIO_TYPES_H