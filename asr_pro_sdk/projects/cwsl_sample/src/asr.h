#ifndef __ASR_H__
#define __ASR_H__
#define TW_ASR_PRO
#include "WString.h"



#ifdef __cplusplus
extern "C"
{
#endif
#include "stdint.h"
#include <stdlib.h>



#include "asrpro_system.h"
#include "command_info.h"
#include "voice_module_uart_protocol.h"
#include "i2c_protocol_module.h"
#include "asrpro_core_misc.h"
#include "system_hook.h"
#include "asrpro_pwm.h"
#include "asrpro_gpio.h"
#include "prompt_player.h"
#include "wiring.h"
#include "queue.h"
#include "system_msg_deal.h"
#define   gpio_pin_0        pin_0
#define   gpio_pin_1        pin_1
#define   gpio_pin_2        pin_2
#define   gpio_pin_3        pin_3
#define   gpio_pin_4        pin_4
#define   gpio_pin_5        pin_5
#define   gpio_pin_6        pin_6
#define   gpio_pin_7        pin_7

#define PI 3.14
typedef struct
{
	volatile uint32_t gpio_data[256];    /*!< 0x000-0x3FC 数据寄存器 */
	volatile uint32_t gpio_dir;          /*!< 0x400-0x404 输入输出控制寄存器 */
	volatile uint32_t gpio_is;           /*!< 0x404-0x408 中断源（边沿/电平）寄存器 */
	volatile uint32_t gpio_ibe;          /*!< 0x408-0x40C 中断源双边沿触发寄存器 */
	volatile uint32_t gpio_iev;          /*!< 0x40C-0x410 中断事件寄存器 */
	volatile uint32_t gpio_ie;           /*!< 0x410-0x414 中断屏蔽寄存器 */
	volatile  uint32_t gpio_ris;          /*!< 0x414-0x418 中断原始状态寄存器 */
	volatile  uint32_t gpio_mis;          /*!< 0x418-0x41C 中断屏蔽状态寄存器 */
	volatile uint32_t gpio_ic;           /*!< 0x41C-0x420 中断清除寄存器 */
	volatile uint32_t gpio_afsel;        /*!< 0x420-0x424 模式控制寄存器 */
}gpio_register_t;

void ASR_CODE();
#define enter_wakeup(x)  enter_wakeup_deal(x,INVALID_HANDLE)
#define pinToFun  cpp_pinToFun


/*
void ASR_send_id(uint8_t id)
{

sys_msg_t send_msg;
send_msg.msg_type=SYS_MSG_TYPE_ASR;
send_msg.msg_data.asr_data.asr_status=MSG_ASR_STATUS_GOOD_RESULT;
send_msg.msg_data.asr_data.asr_cmd_handle=cmd_info_find_command_by_id(id);
send_msg_to_sys_task(&send_msg,NULL);

}


*/
const uint8_t cpp_pinToFun[28]=
{
    0,//PA_0
    1,
    6,
    7,
    8,
    9,
    10,
    11,
    12,//PB_0
    13,
    14,
    15,
    16,
    17,
    28,
    19,
    20,//PC_0
    26,
    27,
    28,
    29,
    30,
    31,//PD_0
    32,
    33,
    34,
    35,
    36,
};


#ifdef __cplusplus
}
#endif
// #include "iot.h"
// #include "SetWifi.h"
#endif

