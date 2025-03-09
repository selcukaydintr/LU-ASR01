/**
 * ===========================================================
 * Proje: Zuzu v1 - ASR-PRO Register Tanımlamaları
 * Dosya: asr_pro_defines.h
 * Açıklama: ASR-PRO çipi register ve değişken tanımlamaları
 * 
 * Versiyon: 1.0.0
 * Değişiklikler:
 * - [1.0.0] İlk sürüm
 * ===========================================================
 */

 #ifndef ASR_PRO_DEFINES_H
 #define ASR_PRO_DEFINES_H
 
 // Temel Özellikler
 #define ASR_PRO_CPU_FREQ      240000000   // 240MHz
 #define ASR_PRO_SRAM_SIZE     640000      // 640KB
 #define ASR_PRO_FLASH_SIZE    4194304     // 4MB
 
 // Bellek Haritası
 #define SRAM_BASE           0x1FF00000
 #define SRAM_SIZE          (640 * 1024)
 #define FLASH_BASE         0x00000000
 #define FLASH_SIZE         (4 * 1024 * 1024)
 
 // Periferik Base Adresleri
 #define BNPU_BASE          0x40000000
 #define DMA_BASE           0x40001000
 #define ADC_BASE           0x40002000
 #define DTR_FLASH_BASE     0x40004000
 #define GPIO0_BASE         0x40020000
 #define GPIO1_BASE         0x40021000
 #define UART0_BASE         0x40022000
 #define UART1_BASE         0x40023000
 #define UART2_BASE         0x40024000
 #define IIS0_BASE          0x40025000
 
 // BNPU Registers
 #define BNPU_CTRL         (BNPU_BASE + 0x00)
 #define BNPU_STATUS       (BNPU_BASE + 0x04)
 #define BNPU_CONFIG       (BNPU_BASE + 0x08)
 #define BNPU_WEIGHT_ADDR  (BNPU_BASE + 0x0C)
 #define BNPU_INPUT_ADDR   (BNPU_BASE + 0x10)
 #define BNPU_OUTPUT_ADDR  (BNPU_BASE + 0x14)
 
 // BNPU Status Bits
 #define BNPU_STATUS_READY 0x01
 #define BNPU_STATUS_BUSY  0x02
 #define BNPU_STATUS_ERROR 0x04
 #define BNPU_STATUS_DONE  0x08
 
 // UART Registers
 #define UART_DR(base)     ((base) + 0x000)
 #define UART_RSR(base)    ((base) + 0x004)
 #define UART_FR(base)     ((base) + 0x018)
 #define UART_IBRD(base)   ((base) + 0x024)
 #define UART_FBRD(base)   ((base) + 0x028)
 #define UART_LCR_H(base)  ((base) + 0x02C)
 #define UART_CR(base)     ((base) + 0x030)
 #define UART_IFLS(base)   ((base) + 0x034)
 #define UART_IMSC(base)   ((base) + 0x038)
 #define UART_RIS(base)    ((base) + 0x03C)
 #define UART_MIS(base)    ((base) + 0x040)
 #define UART_ICR(base)    ((base) + 0x044)
 
 // DMA Registers
 #define DMA_STATUS        (DMA_BASE + 0x000)
 #define DMA_CFG           (DMA_BASE + 0x004)
 #define DMA_CTRL          (DMA_BASE + 0x008)
 #define DMA_INT_STAT      (DMA_BASE + 0x00C)
 #define DMA_INT_TC_STAT   (DMA_BASE + 0x010)
 #define DMA_INT_TC_CLR    (DMA_BASE + 0x014)
 #define DMA_INT_ERR_STAT  (DMA_BASE + 0x018)
 #define DMA_INT_ERR_CLR   (DMA_BASE + 0x01C)
 
 // ADC Registers
 #define ADC_CTRL          (ADC_BASE + 0x000)
 #define ADC_STAT          (ADC_BASE + 0x004)
 #define ADC_DATA          (ADC_BASE + 0x008)
 #define ADC_INT_EN        (ADC_BASE + 0x00C)
 #define ADC_INT_STAT      (ADC_BASE + 0x010)
 #define ADC_INT_CLR       (ADC_BASE + 0x014)
 
 // I2S Registers 
 #define IIS_CTRL          (IIS0_BASE + 0x000)
 #define IIS_STAT          (IIS0_BASE + 0x004)
 #define IIS_CLKDIV        (IIS0_BASE + 0x008)
 #define IIS_TXDATA        (IIS0_BASE + 0x00C)
 #define IIS_RXDATA        (IIS0_BASE + 0x010)
 
 // Interrupt Numbers
 typedef enum {
     INT_WWDG        = 0,
     INT_SCU         = 1,
     INT_ADC         = 3,
     INT_TIMER0      = 5,
     INT_TIMER1      = 6,
     INT_TIMER2      = 7,
     INT_TIMER3      = 8,
     INT_IIC         = 9,
     INT_GPIO0       = 10,
     INT_GPIO1       = 11,
     INT_UART0       = 12,
     INT_UART1       = 13,
     INT_UART2       = 14,
     INT_IIS0        = 15,
     INT_PDM         = 20,
     INT_DTR         = 21,
     INT_VDT         = 23,
     INT_EXT0        = 24,
     INT_EXT1        = 25,
     INT_IWDG        = 26,
     INT_EFUSE       = 29,
     INT_GPIO2       = 30
 } IRQn_Type;
 
 // System Control Bits
 #define SCU_CTRL_ENABLE   (1 << 0)
 #define SCU_CTRL_SLEEP    (1 << 1)
 #define SCU_CTRL_DEEPSLEEP (1 << 2)
 
 // GPIO Pin Functions
 typedef enum {
     GPIO_FUNC_INPUT = 0,
     GPIO_FUNC_OUTPUT = 1,
     GPIO_FUNC_ALT1 = 2,
     GPIO_FUNC_ALT2 = 3,
     GPIO_FUNC_ALT3 = 4,
     GPIO_FUNC_ALT4 = 5
 } GPIO_Function;
 
 // DMA Channel Priority
 typedef enum {
     DMA_PRIORITY_LOW = 0,
     DMA_PRIORITY_MEDIUM = 1,
     DMA_PRIORITY_HIGH = 2,
     DMA_PRIORITY_VERY_HIGH = 3
 } DMA_Priority;
 
 #endif // ASR_PRO_DEFINES_H