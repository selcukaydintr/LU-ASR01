/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi
 * Dosya: uart_controller.h
 * Açıklama: UART iletişim kontrolcüsü
 * Bağımlılıklar: FreeRTOS.h, queue.h, semphr.h
 * 
 * Versiyon: 0.7.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_UART_CONTROLLER_H
#define ASRPRO_UART_CONTROLLER_H

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include <cstdint>
#include <string>

namespace asrpro {
namespace hardware {

// UART yapılandırma
struct UARTConfig {
    uint32_t baudRate{115200};      // Baud rate
    uint8_t dataBits{8};           // Veri biti
    uint8_t stopBits{1};           // Stop biti
    bool useParity{false};         // Parite kontrolü
    uint16_t rxBufferSize{2048};   // RX buffer boyutu
    uint16_t txBufferSize{2048};   // TX buffer boyutu
};

// UART protokol tipleri
enum class UARTProtocol {
    ESP32,      // ESP32 Cam protokolü
    RPI_PICO,   // RPi Pico protokolü
    STANDARD    // Standart UART
};

class UARTController {
public:
    static UARTController& getInstance();
    
    // Temel işlemler
    bool init(const UARTConfig& config);
    bool deinit();
    bool isInitialized() const;
    
    // Veri iletişimi
    bool transmit(const uint8_t* data, size_t size);
    bool receive(uint8_t* data, size_t size, uint32_t timeout);
    
    // Protokol yönetimi
    bool setProtocol(UARTProtocol protocol);
    bool configureProtocol(const void* config);

    // Durum kontrolü
    bool isTxEmpty() const;
    bool isRxAvailable() const;
    uint32_t getRxCount() const;

private:
    UARTController() = default;
    ~UARTController() = default;
    UARTController(const UARTController&) = delete;
    UARTController& operator=(const UARTController&) = delete;

    // FreeRTOS kaynakları
    QueueHandle_t txQueue{nullptr};
    QueueHandle_t rxQueue{nullptr};
    SemaphoreHandle_t txSemaphore{nullptr};
    SemaphoreHandle_t rxSemaphore{nullptr};

    UARTConfig config;
    UARTProtocol currentProtocol{UARTProtocol::STANDARD};
    bool initialized{false};

    // IRQ işleyicileri
    static void uartTxIRQHandler(void* param);
    static void uartRxIRQHandler(void* param);
};

} // namespace hardware
} // namespace asrpro

#endif // ASRPRO_UART_CONTROLLER_H