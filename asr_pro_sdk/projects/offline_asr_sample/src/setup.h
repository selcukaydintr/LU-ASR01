#ifndef __SETUP_H__
#define __SETUP_H__


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
#include "asrpro_gpio.h"
#include "wiring.h"
//uint8_t ampower=0;

void setup();



#ifdef __cplusplus
}
#endif

#endif

