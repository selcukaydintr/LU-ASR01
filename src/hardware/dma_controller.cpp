#include "hardware/dma_controller.h"

namespace asrpro {
namespace hardware {

// DMA register tanımları
#define DMA_CHANNEL_BASE(ch)    (DMA_BASE + (ch * 0x20))
#define DMA_CH_CTRL(ch)         (DMA_CHANNEL_BASE(ch) + 0x00)
#define DMA_CH_CONFIG(ch)       (DMA_CHANNEL_BASE(ch) + 0x04)
#define DMA_CH_SRC(ch)          (DMA_CHANNEL_BASE(ch) + 0x08)
#define DMA_CH_DST(ch)          (DMA_CHANNEL_BASE(ch) + 0x0C)
#define DMA_CH_SIZE(ch)         (DMA_CHANNEL_BASE(ch) + 0x10)
#define DMA_CH_STATUS(ch)       (DMA_CHANNEL_BASE(ch) + 0x14)

DMAController& DMAController::getInstance() {
    static DMAController instance;
    return instance;
}

bool DMAController::initChannel(uint8_t channel, const DMAChannelConfig& config) {
    if (channel >= 8) return false; // Maksimum 8 kanal
    
    // Kanal kontrolü sıfırla
    *(volatile uint32_t*)DMA_CH_CTRL(channel) = 0;
    
    // Kaynak ve hedef adresleri ayarla
    *(volatile uint32_t*)DMA_CH_SRC(channel) = config.sourceAddr;
    *(volatile uint32_t*)DMA_CH_DST(channel) = config.destAddr;
    
    // Transfer boyutu
    *(volatile uint32_t*)DMA_CH_SIZE(channel) = config.transferSize;
    
    // Kanal yapılandırması
    uint32_t chConfig = 0;
    chConfig |= (config.channelPriority & 0x3) << 16;
    chConfig |= config.circular ? (1 << 8) : 0;
    
    *(volatile uint32_t*)DMA_CH_CONFIG(channel) = chConfig;
    
    return true;
}

bool DMAController::startTransfer(uint8_t channel) {
    if (channel >= 8) return false;
    
    // Transfer başlat
    *(volatile uint32_t*)DMA_CH_CTRL(channel) |= 0x1;
    
    return true;
}

bool DMAController::waitForComplete(uint8_t channel) {
    if (channel >= 8) return false;
    
    volatile uint32_t* status = (volatile uint32_t*)DMA_CH_STATUS(channel);
    
    while ((*status & 0x1) == 0) {
        if (*status & 0x2) { // Hata biti
            return false;
        }
    }
    
    return true;
}

void DMAController::stopTransfer(uint8_t channel) {
    if (channel >= 8) return;
    
    // Transfer durdur
    *(volatile uint32_t*)DMA_CH_CTRL(channel) &= ~0x1;
}

uint32_t DMAController::getTransferredCount(uint8_t channel) {
    if (channel >= 8) return 0;
    
    return *(volatile uint32_t*)(DMA_CH_STATUS(channel) + 0x4);
}

bool DMAController::hasError(uint8_t channel) {
    if (channel >= 8) return true;
    
    return (*(volatile uint32_t*)DMA_CH_STATUS(channel) & 0x2) != 0;
}

} // namespace hardware
} // namespace asrpro