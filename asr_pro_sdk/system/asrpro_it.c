/**
 ******************************************************************************
 * @文件    asrpro_it.c
 * @版本    V1.0.0
 * @日期    2022-2-11
 * @概要    这个文件是haohaodada公司的asrpro芯片程序的各个外设中断服务函数.
 ******************************************************************************
 * @注意
 *
 * 版权归haohaodada公司所有，未经允许不得使用或修改
 *
 ******************************************************************************
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "asrpro_dma.h"
#include "asrpro_it.h"
#include "asrpro_iic.h"
#include "asrpro_TimerWdt.h"
#include "asrpro_iwdg.h"
#include "ci_log.h"
#include "asrpro_iisdma.h"

__attribute__((weak)) void MAIL_BOX_IRQHandler(void){}
__attribute__((weak)) void IWDG_IRQHandler(void){}
__attribute__((weak)) void TWDG_IRQHandler(void){}
__attribute__((weak)) void SCU_IRQHandler(void){}
__attribute__((weak)) void NPU_IRQHandler(void){}
__attribute__((weak)) void ADC_IRQHandler(void){}
__attribute__((weak)) void DMA_IRQHandler(void){
	dma_irq_handler();
}
__attribute__((weak)) void TIMER0_IRQHandler(void){}
__attribute__((weak)) void TIMER1_IRQHandler(void){}
__attribute__((weak)) void TIMER2_IRQHandler(void){}
__attribute__((weak)) void TIMER3_IRQHandler(void){}
__attribute__((weak)) void IIC0_IRQHandler(void){}//有点大
__attribute__((weak)) void PA_IRQHandler(void){}//有点大
__attribute__((weak)) void PB_IRQHandler(void){}//有点大
__attribute__((weak)) void UART0_IRQHandler(void){}//有点大
__attribute__((weak)) void UART1_IRQHandler(void){}
__attribute__((weak)) void UART2_IRQHandler(void){}
__attribute__((weak)) void IIS0_IRQHandler(void){}
__attribute__((weak)) void IIS1_IRQHandler(void){}
__attribute__((weak)) void IIS2_IRQHandler(void){}
__attribute__((weak)) void IIS_DMA_IRQHandler(void){}//有点大
__attribute__((weak)) void ALC_IRQHandler(void){}
__attribute__((weak)) void PDM_IRQHandler(void){}
__attribute__((weak)) void DTR_IRQHandler(void){}
__attribute__((weak)) void V11_OK_IRQHandler(void){}
__attribute__((weak)) void VDT_IRQHandler(void){}
__attribute__((weak)) void EXT0_IRQHandler(void){}
__attribute__((weak)) void EXT1_IRQHandler(void){}
__attribute__((weak)) void AON_TIM_INT0_IRQHandler(void){}
__attribute__((weak)) void AON_TIM_INT1_IRQHandler(void){}
__attribute__((weak)) void AON_EFUSE_IRQHandler(void){}
__attribute__((weak)) void AON_PC_IRQHandler(void){}

/***************** (C) COPYRIGHT haohaodada Technology Co., Ltd. *****END OF FILE****/
