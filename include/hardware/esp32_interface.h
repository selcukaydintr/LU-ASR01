/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: esp32_interface.h
 * Açıklama: ESP32 Cam iletişim arayüzü
 * Bağımlılıklar: FreeRTOS.h, uart_controller.h
 * 
 * Versiyon: 0.9.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_ESP32_INTERFACE_H
#define ASRPRO_ESP32_INTERFACE_H

#include "FreeRTOS.h"
#include "hardware/uart_controller.h"
#include <vector>
#include <memory>

namespace asrpro {
namespace hardware {

// ESP32 Cam yapılandırması
struct ESP32Config {
    // Kamera ayarları
    struct {
        uint16_t width{640};
        uint16_t height{480};
        uint8_t quality{10};
        bool grayscale{true};
    } camera;

    // UART ayarları
    struct {
        uint32_t baudRate{115200};
        uint16_t rxBufferSize{4096};
        uint16_t txBufferSize{4096};
    } uart;

    // Protokol ayarları
    struct {
        uint8_t startByte{0xAA};
        uint8_t endByte{0xFF};
        uint16_t packetSize{1024};
    } protocol;
};

class ESP32Interface {
public:
    static ESP32Interface& getInstance();

    // Başlatma ve yapılandırma
    bool init(const ESP32Config& config);
    bool configure(const ESP32Config& config);
    
    // Kamera kontrolü
    bool startCamera();
    bool stopCamera();
    bool captureFrame(std::vector<uint8_t>& frameData);
    
    // UART iletişimi
    bool sendData(const uint8_t* data, size_t size);
    bool receiveData(uint8_t* data, size_t size);
    
    // Durum kontrolü
    bool isConnected() const;
    bool isCameraActive() const;
    const char* getErrorString() const;

private:
    ESP32Interface() = default;
    ~ESP32Interface() = default;
    
    struct Impl;
    std::unique_ptr<Impl> pImpl;

    // FreeRTOS task işlevleri
    static void cameraTask(void* params);
    static void uartRxTask(void* params);
    static void uartTxTask(void* params);
};

} // namespace hardware
} // namespace asrpro

#endif // ASRPRO_ESP32_INTERFACE_H