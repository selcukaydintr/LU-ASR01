/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: bnpu_driver.cpp
 * Açıklama: BNPU (Sinir Ağı İşlem Birimi) sürücü implementasyonu
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#include "hardware/bnpu_driver.h"
#include "hardware/dma_controller.h"
#include <memory>
#include <vector>

namespace asrpro {
namespace hardware {

class BNPUDriver::Impl {
private:
    bool initialized;
    BNPUConfig config;
    DMAController& dmaCtrl;
    
    // BNPU bellek alanları
    struct {
        uint32_t inputAddr;    // Giriş tamponu adresi
        uint32_t outputAddr;   // Çıkış tamponu adresi
        uint32_t weightAddr;   // Ağırlık matrisi adresi
        uint32_t ctrlReg;      // Kontrol register'ı
        uint32_t statusReg;    // Durum register'ı
    } registers;

    // DMA kanalları
    struct {
        uint8_t input;         // Giriş DMA kanalı
        uint8_t output;        // Çıkış DMA kanalı
        uint8_t weight;        // Ağırlık DMA kanalı
    } dmaChannels;

public:
    Impl() 
        : initialized(false)
        , dmaCtrl(DMAController::getInstance())
    {
        // DMA kanallarını ayarla
        dmaChannels.input = 0;
        dmaChannels.output = 1;
        dmaChannels.weight = 2;
        
        // Register adreslerini ayarla
        registers.inputAddr = BNPU_BASE + 0x00;
        registers.outputAddr = BNPU_BASE + 0x04;
        registers.weightAddr = BNPU_BASE + 0x08;
        registers.ctrlReg = BNPU_BASE + 0x0C;
        registers.statusReg = BNPU_BASE + 0x10;
    }

    bool init(const BNPUConfig& cfg) {
        config = cfg;
        
        // BNPU donanımını sıfırla
        *(volatile uint32_t*)registers.ctrlReg = 0x1;
        
        // DMA kanallarını yapılandır
        DMAChannelConfig dmaConfig;
        dmaConfig.channelPriority = 2;
        
        // Giriş DMA
        dmaConfig.destAddr = registers.inputAddr;
        if (!dmaCtrl.initChannel(dmaChannels.input, dmaConfig)) {
            return false;
        }
        
        // Çıkış DMA
        dmaConfig.sourceAddr = registers.outputAddr;  
        if (!dmaCtrl.initChannel(dmaChannels.output, dmaConfig)) {
            return false;
        }
        
        // BNPU yapılandırma
        uint32_t bnpuConfig = 0;
        bnpuConfig |= (config.inputSize & 0xFF) << 0;
        bnpuConfig |= (config.hiddenSize & 0xFF) << 8;
        bnpuConfig |= (config.outputSize & 0xFF) << 16;
        bnpuConfig |= (config.numLayers & 0x0F) << 24;
        
        *(volatile uint32_t*)registers.ctrlReg = bnpuConfig;
        
        initialized = true;
        return true;
    }

    bool process(const void* input, void* output) {
        if (!initialized) return false;
        
        // Giriş verisini DMA ile aktar
        DMAChannelConfig dmaConfig;
        dmaConfig.sourceAddr = (uint32_t)input;
        dmaConfig.transferSize = config.inputSize * sizeof(float);
        
        if (!dmaCtrl.initChannel(dmaChannels.input, dmaConfig)) {
            return false;
        }
        
        // İşlemi başlat
        *(volatile uint32_t*)registers.ctrlReg |= 0x2;
        
        // İşlem tamamlanmasını bekle
        while ((*(volatile uint32_t*)registers.statusReg & 0x1) == 0) {
            if (*(volatile uint32_t*)registers.statusReg & 0x2) {
                // Hata oluştu
                return false;
            }
        }
        
        // Çıkış verisini DMA ile al
        dmaConfig.destAddr = (uint32_t)output;
        dmaConfig.transferSize = config.outputSize * sizeof(float);
        
        if (!dmaCtrl.initChannel(dmaChannels.output, dmaConfig)) {
            return false;
        }
        
        return dmaCtrl.waitForComplete(dmaChannels.output);
    }
};

// Singleton instance getter
BNPUDriver& BNPUDriver::getInstance() {
    static BNPUDriver instance;
    return instance;
}

bool BNPUDriver::init(const BNPUConfig& config) {
    if (!pImpl) {
        pImpl = std::make_unique<Impl>();
    }
    return pImpl->init(config);
}

bool BNPUDriver::process(const void* input, void* output) {
    if (!pImpl) return false;
    return pImpl->process(input, output);
}

void BNPUDriver::shutdown() {
    pImpl.reset();
}

} // namespace hardware
} // namespace asrpro