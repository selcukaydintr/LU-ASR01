/**
 * @file asrpro_pwm.h
 * @brief  PWM驱动文件
 * @version 0.1
 * @date 2019-04-03
 *
 * @copyright Copyright (c) 2019  haohaodada Technology Co., Ltd.
 *
 */

#ifndef _CI100X_PWM_H_
#define _CI100X_PWM_H_

#include "asrpro_system.h"

/**
 * @ingroup asrpro_chip_driver
 * @defgroup asrpro_pwm asrpro_pwm
 * @brief asrpro芯片PWM驱动
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 控制器定义
 */
typedef enum
{
    PWM0 = HAL_PWM0_BASE,/*!< PWM0控制器 */
    PWM1 = HAL_PWM1_BASE,/*!< PWM1控制器 */
    PWM2 = HAL_PWM2_BASE,/*!< PWM2控制器 */
    PWM3 = HAL_PWM3_BASE,/*!< PWM3控制器 */
    PWM4 = HAL_PWM4_BASE,/*!< PWM4控制器 */
    PWM5 = HAL_PWM5_BASE,/*!< PWM5控制器 */
}pwm_base_t;

/**
 * @brief PWM配置结构体
 */
typedef struct
{
	unsigned int clk_sel;           /*!< 时钟源选择，0:内部时钟，1:外部时钟 */
    unsigned int freq;              /*!< pwm频率 单位：HZ */
    unsigned int duty;              /*!< pwm占空比 */
    unsigned int duty_max;          /*!< pwm最大占空比 */
}pwm_init_t;

void pwm_init(pwm_base_t base,pwm_init_t init);
void pwm_start(pwm_base_t base);
void pwm_stop(pwm_base_t base);
void pwm_set_duty(pwm_base_t base,unsigned int duty,unsigned int duty_max);
void pwm_set_restart_md(pwm_base_t base, uint8_t cmd);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif
