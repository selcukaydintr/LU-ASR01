/**
 * ===========================================================
 * Proje: Zuzu v1 - ASR-PRO Hata Ayıklama Modülü
 * Dosya: asr_pro_debug.h
 * Açıklama: ASR-PRO için hata ayıklama ve kontrol
 * 
 * Versiyon: 1.0.0
 * ===========================================================
 */

 #ifndef ASR_PRO_DEBUG_H
 #define ASR_PRO_DEBUG_H
 
 #include <cstdint>
 #include "asr_pro_defines.h"
 
 class ASRPRODebug {
 public:
     // Hata kodları
     enum ErrorCode {
         ERR_NONE = 0,
         ERR_INIT_FAILED = -1,
         ERR_INVALID_STATE = -2, 
         ERR_TIMEOUT = -3,
         ERR_BUFFER_OVERFLOW = -4,
         ERR_BUFFER_UNDERFLOW = -5,
         ERR_INVALID_PARAM = -6,
         ERR_HARDWARE = -7
     };
 
     // BNPU durumu kontrolü
     struct BNPUStatus {
         bool isReady;
         bool isBusy;
         bool hasError;
         uint32_t errorCode;
         uint32_t registers[8];
     };
 
     // DMA durumu kontrolü 
     struct DMAStatus {
         bool isActive;
         bool hasError;
         uint32_t transferred;
         uint32_t remaining;
     };
 
     // Bellek durumu
     struct MemoryStatus {
         uint32_t freeRAM;
         uint32_t usedRAM;
         uint32_t freeFlash;
         uint32_t usedFlash;
     };
 
     // Donanım kontrolü
     bool checkHardware() {
         // Temel donanım kontrolü
         if (!checkBNPU()) return false;
         if (!checkDMA()) return false;
         if (!checkMemory()) return false;
         return true;
     }
 
     // BNPU kontrolü
     BNPUStatus checkBNPU() {
         BNPUStatus status;
         volatile uint32_t* bnpuStatus = (volatile uint32_t*)BNPU_STATUS;
         
         status.isReady = (*bnpuStatus & BNPU_STATUS_READY);
         status.isBusy = (*bnpuStatus & BNPU_STATUS_BUSY);
         status.hasError = (*bnpuStatus & BNPU_STATUS_ERROR);
         
         return status;
     }
 
     // DMA kontrolü 
     DMAStatus checkDMA() {
         DMAStatus status;
         volatile uint32_t* dmaStatus = (volatile uint32_t*)DMA_STATUS;
         
         status.isActive = (*dmaStatus & 0x1);
         status.hasError = (*dmaStatus & 0x2);
         status.transferred = *(volatile uint32_t*)(DMA_BASE + 0x20);
         status.remaining = *(volatile uint32_t*)(DMA_BASE + 0x24);
         
         return status;
     }
 
     // Bellek kontrolü
     MemoryStatus checkMemory() {
         MemoryStatus status;
         
         // SRAM kullanımı
         status.freeRAM = SRAM_SIZE - getUsedRAM();
         status.usedRAM = getUsedRAM();
         
         // Flash kullanımı
         status.freeFlash = FLASH_SIZE - getUsedFlash();
         status.usedFlash = getUsedFlash();
         
         return status;
     }
 
     // Hata durumlarını logla
     void logError(ErrorCode error, const char* message) {
         char buffer[256];
         snprintf(buffer, sizeof(buffer), 
                 "ASR-PRO Error [%d]: %s", error, message);
         
         // UART üzerinden gönder
         sendDebugMessage(buffer);
     }
 
     // Watchdog Timer kontrolü
     bool checkWatchdog() {
         volatile uint32_t* wwdgStatus = (volatile uint32_t*)(0x40010000);
         return (*wwdgStatus & 0x1) == 0;
     }
 
 private:
     uint32_t getUsedRAM() {
         // SRAM kullanımı hesaplama
         return (*(volatile uint32_t*)(SRAM_BASE + 0x4));
     }
     
     uint32_t getUsedFlash() {
         // Flash kullanımı hesaplama
         return (*(volatile uint32_t*)(FLASH_BASE + 0x8));
     }
     
     void sendDebugMessage(const char* msg) {
         // UART üzerinden debug mesajı gönder
         volatile uint32_t* uartData = (volatile uint32_t*)UART_DR(UART0_BASE);
         while (*msg) {
             *uartData = *msg++;
             while (*(volatile uint32_t*)UART_FR(UART0_BASE) & (1 << 5));
         }
     }
 };
 
 #endif // ASR_PRO_DEBUG_H