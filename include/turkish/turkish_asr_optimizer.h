/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: turkish_asr_optimizer.h
 * Açıklama: Türkçe ASR optimizasyon modülü
 * Bağımlılıklar: turkish_asr.h, bnpu_driver.h
 * 
 * Versiyon: 0.3.2
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_TURKISH_ASR_OPTIMIZER_H
#define ASRPRO_TURKISH_ASR_OPTIMIZER_H

#include "turkish_asr.h"
#include "hardware/bnpu_driver.h"
#include <vector>
#include <memory>

namespace asrpro {
namespace turkish {

class TurkishASROptimizer {
public:
    struct OptimizationConfig {
        uint32_t batchSize{64};        // BNPU batch boyutu
        uint32_t dmaBufferSize{4096};  // DMA tampon boyutu
        bool useCache{true};           // Önbellek kullanımı
        float beamThreshold{0.01f};    // Işın eşiği
    };

    // DMA transfer optimizasyonu
    struct DMAOptimization {
        uint8_t channelPriority;      // DMA kanal önceliği
        bool circularMode;            // Dairesel mod
        uint32_t burstSize;          // Burst transfer boyutu
    };

    bool init(const OptimizationConfig& config);
    bool optimizePerformance();
    bool configureDMA(const DMAOptimization& dmaConfig);

private:
    OptimizationConfig config;
    std::unique_ptr<hardware::BNPUDriver> bnpu;
};

} // namespace turkish
} // namespace asrpro

#endif // ASRPRO_TURKISH_ASR_OPTIMIZER_H