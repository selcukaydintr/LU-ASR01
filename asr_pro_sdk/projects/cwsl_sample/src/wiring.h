#ifndef __WIRING_H__
#define __WIRING_H__


#define uint16 uint16_t
#define uint8 uint8_t


#ifdef __cplusplus
extern "C"
{
#endif
#include "stdint.h"
#include <stdlib.h>
#include "command_info.h"
#include "voice_module_uart_protocol.h"
#include "i2c_protocol_module.h"
#include "asrpro_core_misc.h"
#include "asrpro_pwm.h"
#include "asrpro_adc.h"
#include "asrpro_gpio.h"
#include "asrpro_dpmu.h"
#include "asrpro_core_timer.h"
#include "math.h"
#include "prompt_player.h"

#include "asr_api.h"
#include <stdlib.h>
#include "sdk_default_config.h"
#include "ci_log.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "ci_flash_data_info.h"

#define TW_ASR_PRO

#define input 0
#define output 1
#define high 1
#define low 0
#define INPUT 0
#define OUTPUT 1


#define adc_read(x)  analogRead(x)
#define _nop_()   __asm volatile("nop")
typedef enum
{
    GPIOA_0,
    GPIOA_1,
    GPIOA_2,
    GPIOA_3,
    GPIOA_4,
    GPIOA_5,
    GPIOA_6,
    GPIOA_7,
    GPIOB_0,
    GPIOB_1,
    GPIOB_2,
    GPIOB_3,
    GPIOB_4,
    GPIOB_5,
    GPIOB_6,
    GPIOB_7,
    GPIOC_0,
    GPIOC_1,
    GPIOC_2,
    GPIOC_3,
    GPIOC_4,
    GPIOC_5,
    GPIOD_0,
    GPIOD_1,
    GPIOD_2,
    GPIOD_3,
    GPIOD_4,
    GPIOD_5,
}gpio_pin;

typedef enum
{
    PA_0,
    PA_1,
    PA_2,
    PA_3,
    PA_4,
    PA_5,
    PA_6,
    PA_7,
    PB_0,
    PB_1,
    PB_2,
    PB_3,
    PB_4,
    PB_5,
    PB_6,
    PB_7,
    PC_0,
    PC_1,
    PC_2,
    PC_3,
    PC_4,
    PC_5,
    PD_0,
    PD_1,
    PD_2,
    PD_3,
    PD_4,
    PD_5,
}gpio_p_pin;


/*当主频为168时，延时1us*/
void delay1us();
void delay5us();
void delay10us();
void delay50us();
void delay100us();
void delayMicroseconds(uint32_t us);
void delay(uint32_t x);
uint32_t millis();
uint64_t micros();

void pinMode(uint8_t pin,uint8_t Mode);

void digitalWrite(uint8_t pin,uint8_t dig);

uint8_t digitalRead(uint8_t pin);
uint32_t analogRead(uint8_t pin);

void setPinFun(uint8_t pin,IOResue_FUNCTION funtest);

void adMode(uint8_t pin,uint8_t adio_mode);

void PWM_enble(pwm_base_t base,unsigned int freq,unsigned int duty_max,unsigned int duty);
void Set_GPIO_irq(uint8_t pin,gpio_trigger_t s,int32_t addar);
void Clear_GPIO_irq(uint8_t pin);
uint8_t gpio_get_irq_status(uint8_t pin);

void set_pin_to_gpio_mode(uint8_t pin);  /* 设置引脚为GPIO模式 */

extern void set_state_enter_wakeup(uint32_t exit_wakup_ms);



#ifdef __cplusplus
}
#endif

#endif

