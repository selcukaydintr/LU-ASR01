
#include "wiring.h"
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

const uint8_t pinToFun[28]=
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
    18,
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

/************************************************************************
  * @brief  延时1微秒.
  * @param  none
  * @return none
  **********************************************************************/
void delay1us(){
    volatile unsigned int i,j;
    taskENTER_CRITICAL();
    for(i=0;i<1;i++)
    {
        for(j=0;j<10;j++)
        {
        }
    }
    taskEXIT_CRITICAL();
}

/************************************************************************
  * @brief  延时5微秒.
  * @param  none
  * @return none
  **********************************************************************/
void delay5us(){
    volatile unsigned int i,j;
    taskENTER_CRITICAL();
    for(i=0;i<1;i++)
    {
        for(j=0;j<140;j++)
        {
        }
    }
    taskEXIT_CRITICAL();
}

/************************************************************************
  * @brief  延时10微秒.
  * @param  none
  * @return none
  **********************************************************************/
void delay10us(){
    volatile unsigned int i,j;
    taskENTER_CRITICAL();
    for(i=0;i<1;i++)
    {
        for(j=0;j<210;j++)
        {
        }
    }
    taskEXIT_CRITICAL();
}

/************************************************************************
  * @brief  延时50微秒.
  * @param  none
  * @return none
  **********************************************************************/
void delay50us(){
    volatile unsigned int i,j;
    taskENTER_CRITICAL();
    for(i=0;i<1;i++)
    {
        for(j=0;j<980;j++)
        {
        }
    }
    taskEXIT_CRITICAL();
}

/************************************************************************
  * @brief  延时100微秒.
  * @param  none
  * @return none
  **********************************************************************/
void delay100us(){
    volatile unsigned int i,j;
    taskENTER_CRITICAL();
    for(i=0;i<1;i++)
    {
        for(j=0;j<2000;j++)
        {
        }
    }
    taskEXIT_CRITICAL();
}

/************************************************************************
  * @brief  延时x毫秒(系统级延时).
  * @param  x   延时毫秒数（系统心跳为2ms，所以延时时间为2ms的倍数）
  * @return none
  **********************************************************************/
void delay(uint32_t x)
{
    if(x==1)
    {
        x=1;
    }else{
        x=x/2;
    }
    vTaskDelay(x);
}

/************************************************************************
  * @brief  引脚配置.
  * @param  pin   引脚
  * @param  Mode  模式
  *               input:输入
  *               output：输出
  * @return none
  **********************************************************************/
void pinMode(uint8_t pin,uint8_t Mode)
{
    uint32_t gpio,pins;
    if(pin<16){
        gpio=HAL_PA_BASE+(pin/8)*0x1000;
    }
    else if(pin<24)
    {
        gpio=HAL_PC_BASE;
    }else{
        gpio=HAL_PD_BASE;
    }
    pins=1<<(pin%8);
    scu_set_device_gate(gpio,ENABLE);
    if(Mode)
    {
        gpio_set_output_mode(gpio,pins);
    }else{
        gpio_set_input_mode(gpio,pins);
        if(pin==0||pin==1)dpmu_set_io_direction((PinPad_Name)pinToFun[pin],DPMU_IO_DIRECTION_INPUT); //设置引脚功能为输入模式
    }   
}

/************************************************************************
  * @brief  引脚输出.
  * @param  pin     引脚
  * @param  dig     高/低电平
  * @return none
  **********************************************************************/
void digitalWrite(uint8_t pin,uint8_t dig)
{
    uint32_t gpio,pins;
    if(pin<16){
        gpio=HAL_PA_BASE+(pin/8)*0x1000;
    }
    else if(pin<24)
    {
        gpio=HAL_PC_BASE;
    }else{
        gpio=HAL_PD_BASE;
    }
    pins=0x01<<(pin%8);
    if(dig)
    {
        gpio_set_output_high_level(gpio,pins);
    }else{
        gpio_set_output_low_level(gpio,pins);
    }
}

/************************************************************************
  * @brief  引脚输入.
  * @param  pin     引脚
  * @return 读取到的引脚电平
  **********************************************************************/
uint8_t digitalRead(uint8_t pin)
{
    uint32_t gpio,pins;
    if(pin<16){
        gpio=HAL_PA_BASE+(pin/8)*0x1000;
    }
    else if(pin<24)
    {
        gpio=HAL_PC_BASE;
    }else{
        gpio=HAL_PD_BASE;
    }
    pins=0x01<<(pin%8);
    gpio_register_t* gpioP = (gpio_register_t*)gpio;
    if((gpioP->gpio_data[pins])==0)
    {
        return 0;
    }else{
        return 1;
    }
}

/************************************************************************
  * @brief  读取ADC值.
  * @param  pin     引脚
  * @return 读取到的ADC值
  **********************************************************************/
uint32_t analogRead(uint8_t pin)
{
    uint8_t ch=pinToFun[pin];
    scu_set_device_gate(HAL_ADC_BASE,1);     //打开ADC时钟
    dpmu_set_adio_reuse(ch,ANALOG_MODE);       //配置ADC通道5的引脚为模拟功能，更多请查看asrpro_sch.h的IO复用注释
    dpmu_set_io_pull(ch,DPMU_IO_PULL_DISABLE);    //关闭引脚内部上下拉
    //dpmu_set_io_pull(ch,DPMU_IO_PULL_UP);
    eclic_irq_enable(ADC_IRQn);       //使能中断
    __eclic_irq_set_vector(ADC_IRQn, (int32_t)ADC_irqhandle);   //指定中断服务函数
    adc_poweron();             
    adc_signal_mode(31-ch);   //初始化成普通软件触发模式 
    adc_soc_soft_ctrl(ENABLE);     //ADC软件触发（软件强制开始转换）
    adc_wait_int(31-ch);       //等待中断
    return adc_get_result(31-ch);
}

/************************************************************************
  * @brief  设置引脚功能.
  * @param  pin         引脚
  * @param  funtest     功能
  *                     FIRST_FUNCTION  第一功能,
  *                     SECOND_FUNCTION 第二功能,
  *                     THIRD_FUNCTION  第三功能,
  *                     FORTH_FUNCTION  第四功能,
  *                     FIFTH_FUNCTION  第五功能,
  *                     SIXTH_FUNCTION  第六功能。
  * @return none
  **********************************************************************/
void setPinFun(uint8_t pin,IOResue_FUNCTION funtest)
{
    uint8_t pins;
    pins=pinToFun[pin];
    dpmu_set_io_reuse(pins,funtest);
}

/************************************************************************
  * @brief  设置引脚为GPIO模式.
  * @param  pin     引脚
  * @return none
  **********************************************************************/
void set_pin_to_gpio_mode(uint8_t pin) 
{
    if(pin<2)dpmu_set_adio_reuse((PinPad_Name)pinToFun[pin],DIGITAL_MODE);
    if((pin<=23) && (pin>=17)) //设置功能为GPIO
    {
        dpmu_set_adio_reuse((PinPad_Name)pinToFun[pin],DIGITAL_MODE);
        setPinFun(pin,SECOND_FUNCTION);
    }
    else
    {
        setPinFun(pin,FIRST_FUNCTION);
    }
}

/************************************************************************
  * @brief  配置ADC通道5的引脚为模拟功能，更多请查看asrpro_sch.h的IO复用注释.
  * @param  pin         引脚
  * @param  adio_mode   模式
  * @return none
  **********************************************************************/
void adMode(uint8_t pin,uint8_t adio_mode)
{
  dpmu_set_adio_reuse(pinToFun[pin],adio_mode);
}

/************************************************************************
  * @brief  PWM输出.
  * @param  base    PWM0-PWM5
  * @param  freq    频率
  * @param  duty_max    最大占空比值
  * @param  duty    占空比值
  *         （真正占空比值 = duty/duty_max）
  * @return none
  **********************************************************************/
void PWM_enble(pwm_base_t base,unsigned int freq,unsigned int duty_max,unsigned int duty)
{
  scu_set_device_gate(base,ENABLE);
  pwm_init_t pwminit;
  pwminit.clk_sel=0;
  pwminit.duty=duty;
  pwminit.duty_max=duty_max;
  pwminit.freq=freq;
  pwm_init(base,pwminit);
  pwm_start(base);  
}

/************************************************************************
  * @brief  设置引脚中断.
  * @param  pin     引脚
  * @param  s       触发方式
  *                 high_level_trigger   高电平触发中断
  *                 low_level_trigger    低电平触发中断
  *                 up_edges_trigger     上升沿触发中断
  *                 down_edges_trigger   下降沿触发中断
  *                 both_edges_trigger   双边沿触发中断
  * @param  addar   中断回调函数地址
  * @return none
  **********************************************************************/
void Set_GPIO_irq(uint8_t pin,gpio_trigger_t s,int32_t addar)
{
    uint32_t gpio,pins;
    gpio=HAL_PA_BASE+(pin/8)*0x1000;
    pins=0x01<<(pin%8);

    gpio_irq_trigger_config(gpio,pins,s);
    __eclic_irq_set_vector(PA_IRQn+(pin/8),(int32_t)addar);
    eclic_irq_enable(PA_IRQn+(pin/8));
}

/************************************************************************
  * @brief  清除引脚中断.
  * @param  pin     引脚
  * @return none
  **********************************************************************/
void Clear_GPIO_irq(uint8_t pin)
{
    uint32_t gpio,pins;
    gpio=HAL_PA_BASE+(pin/8)*0x1000;
    pins=0x01<<(pin%8);
    gpio_clear_irq_single(gpio,pins);
}

/************************************************************************
  * @brief  读取引脚中断状态.
  * @param  pin     引脚
  * @return 该引脚是否发生中断
  **********************************************************************/
uint8_t gpio_get_irq_status(uint8_t pin)
{
    uint32_t gpio,pins;
    gpio=HAL_PA_BASE+(pin/8)*0x1000;
    pins=0x01<<(pin%8);
   return (gpio_get_irq_raw_status_single(gpio,pins));
}

/************************************************************************
  * @brief  ms计时器.
  * @param  none
  * @return 计时值
  **********************************************************************/
uint32_t millis()
{
    uint32_t lo_temp=*(volatile uint32_t *)(TIMER_CTRL_ADDR + TIMER_MTIME);
    uint32_t hi_temp=*(volatile uint32_t *)(TIMER_CTRL_ADDR + TIMER_MTIME + 4);
    return (uint32_t)((((uint64_t)hi_temp << 32) | lo_temp)/18320);
}

/************************************************************************
  * @brief  us计时器.
  * @param  none
  * @return 计时值
  **********************************************************************/
uint64_t micros()
{
    uint32_t lo_temp=*(volatile uint32_t *)(TIMER_CTRL_ADDR + TIMER_MTIME);
    uint32_t hi_temp=*(volatile uint32_t *)(TIMER_CTRL_ADDR + TIMER_MTIME + 4);
    return (uint64_t)((((uint64_t)hi_temp << 32) | lo_temp)/18);
}

/************************************************************************
  * @brief  us级延时(死等方式，会卡线程).
  * @param  us      延时时间
  * @return none
  **********************************************************************/
void delayMicroseconds(uint32_t us)
{
    uint64_t t;
    taskENTER_CRITICAL();
    t = micros();
    while(1)
    {
        if((micros()- t) >= us)
        {
            break;
        }
    }
    taskEXIT_CRITICAL();
}
