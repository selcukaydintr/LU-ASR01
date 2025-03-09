/**
 * ===========================================================
 * Proje: ASR-PRO Plugin Sistemi 
 * Dosya: uart_interface.h
 * Açıklama: UART iletişim arayüzü
 * 
 * Versiyon: 0.1.0
 * Tarih: 2025-03-09
 * ===========================================================
 */

#ifndef ASRPRO_UART_INTERFACE_H
#define ASRPRO_UART_INTERFACE_H

#include <cstdint>
#include "asrpro_system.h"

namespace asrpro {
namespace hardware {

// UART yapılandırma yapısı
struct UARTConfig {
    uint32_t baudRate;     // Baud rate (örn: 115200)
    uint8_t dataBits;      // Veri biti sayısı (5-8)
    uint8_t stopBits;      // Stop bit sayısı (1-2) 
    uint8_t parity;        // Parite (0:Yok, 1:Tek, 2:Çift)
    bool flowControl;      // Akış kontrolü
    
    UARTConfig() :
        baudRate(115200),
        dataBits(8),
        stopBits(1),
        parity(0),
        flowControl(false)
    {}
};

// UART iletişim arayüzü
class IUARTInterface {
public:
    virtual ~IUARTInterface() = default;
    
    // Temel işlemler
    virtual bool init(const UARTConfig& config) = 0;
    virtual bool deinit() = 0;
    
    // Veri iletişimi
    virtual int32_t write(const uint8_t* data, uint32_t size) = 0;
    virtual int32_t read(uint8_t* data, uint32_t size) = 0;
    
    // Durum kontrolü
    virtual bool isTxEmpty() = 0;
    virtual bool isRxEmpty() = 0;
    virtual void flush() = 0;
    
    // Kesme yönetimi
    virtual void enableInterrupt(uint32_t mask) = 0;
    virtual void disableInterrupt(uint32_t mask) = 0;
    virtual uint32_t getInterruptStatus() = 0;
};

} // namespace hardware
} // namespace asrpro

#endif // ASRPRO_UART_INTERFACE_H