/**
  ******************************************************************************
  * @file    led.h
  * @brief   LED驱动 - 开发板LED控制
  * @note    当前开发板LED连接在P2.6, 低电平点亮
  ******************************************************************************
  */
#ifndef LED_H
#define LED_H

#include "CMS32L032.h"
#include "gpio.h"

/** @defgroup LED_TypeDef LED编号定义
  * @{
  */
typedef enum {
    LED_USER = 0,   /**< 用户LED (P2.6) */
    LED_MAX         /**< LED总数 */
} LED_TypeDef;
/** @} */

/** @defgroup LED_Cfg LED配置结构体
  * @{
  */
typedef struct {
    PORT_TypeDef port;          /**< 端口号 */
    PIN_TypeDef  pin;           /**< 引脚号 */
    uint8_t      active_level;  /**< 有效电平: 0=低电平点亮, 1=高电平点亮 */
} LED_Cfg_t;
/** @} */

/** @defgroup LED_API LED接口函数
  * @{
  */
/**
  * @brief  初始化所有LED引脚为输出模式, 并关闭LED
  * @param  None
  * @retval None
  */
void LED_Init(void);

/**
  * @brief  点亮指定LED
  * @param  led: LED编号 (LED_USER)
  * @retval None
  */
void LED_On(LED_TypeDef led);

/**
  * @brief  熄灭指定LED
  * @param  led: LED编号 (LED_USER)
  * @retval None
  */
void LED_Off(LED_TypeDef led);

/**
  * @brief  翻转指定LED状态
  * @param  led: LED编号 (LED_USER)
  * @retval None
  */
void LED_Toggle(LED_TypeDef led);

/**
  * @brief  LED闪烁
  * @param  led: LED编号 (LED_USER)
  * @param  times: 闪烁次数
  * @param  interval_ms: 闪烁间隔(毫秒)
  * @retval None
  */
void LED_Flash(LED_TypeDef led, uint8_t times, uint32_t interval_ms);
/** @} */

#endif
