/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: audio_processor.h
 * Açıklama: Ses işleme ve öznitelik çıkarımı
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_AUDIO_PROCESSOR_H
#define ASRPRO_AUDIO_PROCESSOR_H

#include "audio_types.h"
#include <memory>

namespace asrpro {
namespace audio {

class AudioProcessor {
public:
    struct Config {
        uint32_t frameSize;     // Çerçeve boyutu
        uint32_t hopSize;       // Atlama boyutu
        uint32_t fftSize;       // FFT boyutu
        uint32_t melBands;      // Mel filtre bankası sayısı
        uint32_t mfccCoeffs;    // MFCC katsayı sayısı
        
        Config()
            : frameSize(512)
            , hopSize(256)
            , fftSize(512)
            , melBands(40)
            , mfccCoeffs(13)
        {}
    };

    AudioProcessor();
    ~AudioProcessor();

    // Temel işlevler
    bool init(const Config& config);
    bool process(const AudioBuffer& input, MFCCFeatures& output);
    void shutdown();

    // Sinyal işleme
    bool applyPreEmphasis(AudioBuffer& buffer, float coefficient = 0.97f);
    bool extractMFCC(const AudioBuffer& buffer, MFCCFeatures& features);

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace audio
} // namespace asrpro

#endif // ASRPRO_AUDIO_PROCESSOR_H