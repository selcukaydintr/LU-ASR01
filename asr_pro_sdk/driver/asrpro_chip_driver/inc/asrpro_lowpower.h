/**
 * @file asrpro_lowpower.h
 * @brief 电源管理驱动
 * @version 0.9
 * @date 2019-02-23
 * 
 * @copyright Copyright (c) 2019 haohaodada Technology Co., Ltd.
 * 
 */
#ifndef _asrpro_LOWPOWER_H_
#define _asrpro_LOWPOWER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

/* 配置需要的模式 */
#define POWER_MODE_DOWN_FREQUENCY_EN          1
#define POWER_MODE_OSC_FREQUENCY_EN           1
#define POWER_MODE_SLEEP_EN                   0 //sleep模式暂时不使用
#define POWER_MODE_DEEP_SLEEP_EN              0 //deep sleep模式暂时不使用

/**
 * @ingroup asrpro_chip_driver
 * @defgroup asrpro_lowpower asrpro_lowpower
 * @brief asrpro芯片电源管理驱动
 * @{
 */

typedef enum
{
    POWER_MODE_ERR = -1,          /*!< ERR                     */
    POWER_MODE_NORMAL = 0,        /*!< 正常模式                */
    POWER_MODE_DOWN_FREQUENCY = 1,/*!< 降频模式                */
    POWER_MODE_OSC_FREQUENCY = 2, /*!< 晶振时钟模式            */

    POWER_MODE_SLEEP = 998,       /*!< 休眠模式                */
    POWER_MODE_DEEP_SLEEP = 999,  /*!< 深度休眠模式            */
}power_mode_t;

void register_lowpower_user_fn(void * enter_lowpower_fn,void * exit_lowpower_fn);
power_mode_t power_mode_switch(power_mode_t power_mode);
power_mode_t get_curr_power_mode(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* _asrpro_LOWPOWER_H_ */
