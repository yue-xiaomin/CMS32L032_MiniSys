/**
  ******************************************************************************
  * @file    delay.h
  * @brief   SysTick延时驱动
  * @note    提供毫秒/微秒级延时, 支持中断和轮询两种方式
  ******************************************************************************
  */
#ifndef DELAY_H
#define DELAY_H

#include "CMS32L032.h"
#include <stdint.h>

/**
  * @brief  初始化SysTick延时模块
  * @note   在main()中调用一次即可
  */
void delay_init(void);

/**
  * @brief  毫秒延时 (轮询方式, 不依赖中断)
  * @param  ms: 延时毫秒数 (0~65535)
  */
void delay_ms(uint32_t ms);

/**
  * @brief  微秒延时 (轮询方式, 不依赖中断)
  * @param  us: 延时微秒数 (0~1000)
  */
void delay_us(uint32_t us);

#endif
