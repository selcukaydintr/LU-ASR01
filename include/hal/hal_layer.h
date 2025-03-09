/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: hal_layer.h
 * Açıklama: Donanım soyutlama katmanı
 * Bağımlılıklar: stdint.h, FreeRTOS.h
 * 
 * Versiyon: 0.6.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_HAL_LAYER_H
#define ASRPRO_HAL_LAYER_H

#include <stdint.h>
#include "FreeRTOS.h"

namespace asrpro {
namespace hal {

// HAL konfigürasyon yapısı
struct HALConfig {
    // UART yapılandırması
    struct {
        uint32_t baudRate{115200};
        uint8_t dataBits{8};
        uint8_t stopBits{1};
        bool useFlowControl{false};
    } uart;

    // DMA yapılandırması
    struct {
        uint32_t bufferSize{4096};
        uint8_t priority{2};
        bool circular{true};
    } dma;

    // BNPU yapılandırması
    struct {
        uint32_t clockSpeed{240000000};
        uint32_t memorySize{1024 * 1024};
        bool enableCache{true};
    } bnpu;
};

class HALLayer {
public:
    static HALLayer& getInstance();

    // Başlatma ve yapılandırma
    bool init(const HALConfig& config);
    bool deinit();
    bool configure(const HALConfig& config);

    // UART işlemleri
    bool uartInit();
    bool uartTransmit(const uint8_t* data, size_t size);
    bool uartReceive(uint8_t* data, size_t size);

    // DMA işlemleri
    bool dmaInit();
    bool dmaTransfer(const void* src, void* dest, size_t size);
    bool dmaStop();

    // BNPU işlemleri
    bool bnpuInit();
    bool bnpuProcess(const void* input, void* output, size_t size);
    bool bnpuReset();

    // Durum sorgulama
    bool isInitialized() const;
    const char* getErrorString() const;

private:
    HALLayer() = default;
    ~HALLayer() = default;
    HALLayer(const HALLayer&) = delete;
    HALLayer& operator=(const HALLayer&) = delete;

    struct Impl;
    std::unique_ptr<Impl> pImpl;
};

} // namespace hal
} // namespace asrpro

#endif // ASRPRO_HAL_LAYER_H