/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: rpi_pico_interface.h
 * Açıklama: RPi Pico iletişim arayüzü
 * Bağımlılıklar: FreeRTOS.h, uart_controller.h
 * 
 * Versiyon: 0.9.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_RPI_PICO_INTERFACE_H
#define ASRPRO_RPI_PICO_INTERFACE_H

#include "FreeRTOS.h"
#include "hardware/uart_controller.h"
#include <memory>

namespace asrpro {
namespace hardware {

// RPi Pico yapılandırması
struct RPiPicoConfig {
    // UART yapılandırması
    struct {
        uint32_t baudRate{115200};
        uint16_t rxBufferSize{4096};
        uint16_t txBufferSize{4096};
        bool useFlowControl{false};
    } uart;

    // DMA yapılandırması
    struct {
        uint16_t channelSize{1024};
        bool circularMode{true};
        uint8_t priority{1};
    } dma;

    // Protokol yapılandırması
    struct {
        uint8_t startByte{0xBB};
        uint8_t endByte{0xEE};
        uint16_t packetSize{512};
    } protocol;
};

class RPiPicoInterface {
public:
    static RPiPicoInterface& getInstance();
    
    // Temel işlemler
    bool init(const RPiPicoConfig& config);
    bool configure(const RPiPicoConfig& config);
    
    // Veri iletişimi
    bool sendToASR(const uint8_t* data, size_t size);
    bool receiveFromESP32(uint8_t* data, size_t size);
    
    // Durum kontrolü
    bool isConnected() const;
    bool isProcessing() const;
    const char* getErrorString() const;

private:
    RPiPicoInterface() = default;
    ~RPiPicoInterface() = default;
    
    struct Impl;
    std::unique_ptr<Impl> pImpl;

    // FreeRTOS task işlevleri
    static void dataProcessTask(void* params);
    static void uartHandlerTask(void* params);
};

} // namespace hardware
} // namespace asrpro

#endif // ASRPRO_RPI_PICO_INTERFACE_H