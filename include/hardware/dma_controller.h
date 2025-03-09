/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: dma_controller.h
 * Açıklama: DMA kontrolcü sınıfı header dosyası
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_DMA_CONTROLLER_H
#define ASRPRO_DMA_CONTROLLER_H

#include <cstdint>
#include <memory>

namespace asrpro {
namespace hardware {

// DMA kanal yapılandırması
struct DMAChannelConfig {
    uint32_t sourceAddr;      // Kaynak adres
    uint32_t destAddr;        // Hedef adres
    uint32_t transferSize;    // Transfer boyutu
    uint8_t channelPriority;  // Kanal önceliği (0-3)
    bool circular;            // Dairesel mod
};

class DMAController {
public:
    static DMAController& getInstance();

    bool initChannel(uint8_t channel, const DMAChannelConfig& config);
    bool startTransfer(uint8_t channel);
    bool waitForComplete(uint8_t channel);
    void stopTransfer(uint8_t channel);
    
    uint32_t getTransferredCount(uint8_t channel);
    bool hasError(uint8_t channel);

private:
    DMAController() = default;
    ~DMAController() = default;
    DMAController(const DMAController&) = delete;
    DMAController& operator=(const DMAController&) = delete;
};

} // namespace hardware
} // namespace asrpro

#endif // ASRPRO_DMA_CONTROLLER_H