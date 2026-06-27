/**
  ******************************************************************************
  * @file    led.c
  * @brief   LED驱动实现
  * @note    支持多个LED, 通过配置表定义各LED的端口/引脚/有效电平
  ******************************************************************************
  */

/* 包含头文件 */
#include "led.h"
#include "delay.h"

/** @brief LED配置表 - 定义各LED的硬件连接
  * @note  active_level: 0=低电平点亮, 1=高电平点亮
  */
static const LED_Cfg_t led_cfg[LED_MAX] = {
    [LED_USER] = { PORT2, PIN6, 0 },  /* 用户LED: P2.6, 低电平点亮 */
};

/**
  * @brief  初始化所有LED引脚为输出模式, 并关闭LED
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
    uint8_t i;
    for (i = 0; i < LED_MAX; i++) {
        PORT_Init(led_cfg[i].port, led_cfg[i].pin, OUTPUT);  /* 配置为输出模式 */
        LED_Off((LED_TypeDef)i);  /* 初始状态关闭 */
    }
}

/**
  * @brief  点亮指定LED
  * @param  led: LED编号
  * @retval None
  */
void LED_On(LED_TypeDef led)
{
    if (led_cfg[led].active_level)
        PORT_SetBit(led_cfg[led].port, led_cfg[led].pin);   /* 高电平点亮 */
    else
        PORT_ClrBit(led_cfg[led].port, led_cfg[led].pin);   /* 低电平点亮 */
}

/**
  * @brief  熄灭指定LED
  * @param  led: LED编号
  * @retval None
  */
void LED_Off(LED_TypeDef led)
{
    if (led_cfg[led].active_level)
        PORT_ClrBit(led_cfg[led].port, led_cfg[led].pin);   /* 高电平点亮, 则置低熄灭 */
    else
        PORT_SetBit(led_cfg[led].port, led_cfg[led].pin);   /* 低电平点亮, 则置高熄灭 */
}

/**
  * @brief  翻转指定LED状态
  * @param  led: LED编号
  * @retval None
  */
void LED_Toggle(LED_TypeDef led)
{
    PORT_ToggleBit(led_cfg[led].port, led_cfg[led].pin);
}

/**
  * @brief  LED闪烁指定次数后熄灭
  * @param  led: LED编号
  * @param  times: 闪烁次数
  * @param  interval_ms: 闪烁间隔(毫秒), 实际周期为2倍interval_ms
  * @retval None
  */
void LED_Flash(LED_TypeDef led, uint8_t times, uint32_t interval_ms)
{
    uint8_t i;
    for (i = 0; i < times; i++) {
        LED_Toggle(led);
        delay_ms(interval_ms);
    }
    LED_Off(led);  /* 闪烁结束后熄灭 */
}
