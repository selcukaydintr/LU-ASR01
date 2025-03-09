#include "hardware/uart_interface.h"
#include "asrpro_uart.h"
#include "hardware/dma_controller.h"

namespace asrpro {
namespace hardware {

class ASRPROUart : public IUARTInterface {
private:
    UART_TypeDef* uart;
    DMAController& dmaCtrl;
    UARTConfig config;
    bool initialized;

public:
    ASRPROUart(UART_TypeDef* uartBase) : 
        uart(uartBase),
        dmaCtrl(DMAController::getInstance()),
        initialized(false) {}

    bool init(const UARTConfig& cfg) override {
        config = cfg;
        
        // UART donanımını başlat
        scu_set_device_reset((unsigned int)uart);
        scu_set_device_reset_release((unsigned int)uart);
        
        // Baud rate ayarla
        UART_BAUDRATEConfig(uart, (UART_BaudRate)config.baudRate);
        
        // Veri formatını ayarla
        UART_LCRConfig(uart, 
            (UART_WordLength)config.dataBits,
            (UART_StopBits)config.stopBits, 
            (UART_Parity)config.parity);

        // FIFO ayarları
        UART_RXFIFOConfig(uart, UART_FIFOLevel1_4);
        UART_TXFIFOConfig(uart, UART_FIFOLevel1_8);
        
        // DMA aktif et
        UART_TXRXDMAConfig(uart, UART_RXDMA);
        UART_TXRXDMAConfig(uart, UART_TXDMA);

        // UART aktif et
        UART_EN(uart, ENABLE);
        
        initialized = true;
        return true;
    }

    // Diğer metotların implementasyonları...
};

} // namespace hardware
} // namespace asrpro