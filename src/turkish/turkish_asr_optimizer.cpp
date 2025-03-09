/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: turkish_asr_optimizer.cpp
 * Açıklama: Türkçe ASR optimizasyon implementasyonu
 * 
 * Versiyon: 0.3.2
 * Tarih: 2025-03-09
 * ===========================================================
 */

#include "turkish/turkish_asr_optimizer.h"
#include "debug/error_handler.h"

namespace asrpro {
namespace turkish {

bool TurkishASROptimizer::init(const OptimizationConfig& cfg) {
    config = cfg;
    try {
        // BNPU optimizasyonu
        bnpu = std::make_unique<hardware::BNPUDriver>();
        
        // BNPU yapılandırma
        hardware::BNPUConfig bnpuConfig;
        bnpuConfig.batchSize = config.batchSize;
        bnpuConfig.useCache = config.useCache;
        
        if (!bnpu->init(bnpuConfig)) {
            LOG_ERROR("BNPU başlatılamadı", "TurkishASROptimizer", 1);
            return false;
        }

        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR(e.what(), "TurkishASROptimizer", 2);
        return false;
    }
}

bool TurkishASROptimizer::optimizePerformance() {
    try {
        // BNPU performans optimizasyonu
        if (!bnpu->optimizePerformance()) {
            LOG_WARNING("BNPU performans optimizasyonu başarısız", 
                       "TurkishASROptimizer");
        }

        // Bellek optimizasyonu
        if (config.useCache) {
            bnpu->enableCache();
        }

        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR(e.what(), "TurkishASROptimizer", 3);
        return false;
    }
}

bool TurkishASROptimizer::configureDMA(const DMAOptimization& dmaConfig) {
    try {
        // DMA yapılandırması
        hardware::DMAConfig config;
        config.channelPriority = dmaConfig.channelPriority;
        config.circularMode = dmaConfig.circularMode;
        config.burstSize = dmaConfig.burstSize;

        if (!bnpu->configureDMA(config)) {
            LOG_ERROR("DMA yapılandırması başarısız", "TurkishASROptimizer", 4);
            return false;
        }

        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR(e.what(), "TurkishASROptimizer", 5);
        return false;
    }
}

} // namespace turkish
} // namespace asrpro