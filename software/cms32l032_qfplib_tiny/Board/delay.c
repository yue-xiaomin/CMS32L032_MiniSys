/**
  ******************************************************************************
  * @file    delay.c
  * @brief   SysTick延时驱动实现
  ******************************************************************************
  */

#include "delay.h"

/** @brief 系统时钟频率 (Hz) */
static uint32_t g_sysclk_hz;

/**
  * @brief  初始化SysTick延时模块
  */
void delay_init(void)
{
    g_sysclk_hz = SystemCoreClock;
}

/**
  * @brief  毫秒延时 (轮询方式)
  * @param  ms: 延时毫秒数
  */
void delay_ms(uint32_t ms)
{
    uint32_t ticks_per_ms = g_sysclk_hz / 1000;

    while (ms--) {
        SysTick->LOAD = ticks_per_ms - 1;
        SysTick->VAL  = 0;
        SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
        SysTick->CTRL = 0;
    }
}

/**
  * @brief  微秒延时 (轮询方式, 适合短延时)
  * @param  us: 延时微秒数 (建议不超过1000)
  */
void delay_us(uint32_t us)
{
    uint32_t ticks_per_us = g_sysclk_hz / 1000000;

    while (us--) {
        SysTick->LOAD = ticks_per_us - 1;
        SysTick->VAL  = 0;
        SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
        SysTick->CTRL = 0;
    }
}
