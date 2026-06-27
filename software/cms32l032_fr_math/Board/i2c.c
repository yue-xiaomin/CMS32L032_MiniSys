/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   I2C板级驱动 - 基于IICA0模块, 引脚直接配置
  * @note    硬件连接: SCL=P31, SDA=P30
  ******************************************************************************
  */

#include "i2c.h"
#include "userdefine.h"
#include "iica.h"
#include "delay.h"
#include <stdio.h>

/* 外部变量: IICA0 SDK驱动全局变量 */
extern volatile uint8_t   g_iica0_tx_end;
extern volatile uint8_t   g_iica0_rx_end;
extern volatile uint8_t * gp_iica0_tx_address;
extern volatile uint16_t  g_iica0_tx_cnt;
extern volatile uint8_t * gp_iica0_rx_address;
extern volatile uint16_t  g_iica0_rx_len;
extern volatile uint16_t  g_iica0_rx_cnt;

/**
  * @brief  I2C引脚配置 (SCL=P31, SDA=P30)
  */
static void i2c_port_init(void)
{
    /* P31 -> SCLA0 (SCL) */
    PORT->P31CFG = GPIO_FUNC_SCLA0;   /* 复用功能: SCLA0 */
    PORT->P3   &= ~(1 << 1);          /* 输出低电平 */
    PORT->PM3  &= ~(1 << 1);          /* 输出模式 */
    PORT->PMC3 &= ~(1 << 1);          /* 数字功能 */

    /* P30 -> SDAA0 (SDA) */
    PORT->P30CFG = GPIO_FUNC_SDA0;    /* 复用功能: SDAA0 */
    PORT->P3   &= ~(1 << 0);          /* 输出低电平 */
    PORT->PM3  &= ~(1 << 0);          /* 输出模式 */
    PORT->PMC3 &= ~(1 << 0);          /* 数字功能 */
}

/**
  * @brief  初始化I2C模块 (快速模式 400Kbps)
  * @retval I2C_OK: 成功
  */
int I2C_Init(uint8_t speed)
{
    /* 使能IICA0时钟 */
    CGC->PER0 |= CGC_PER0_IICA0EN_Msk;

    /* 停止IICA操作 */
    IICA->IICCTL00 = 0x00;

    /* 禁用并清除中断 */
    INTC_DisableIRQ(IICA_IRQn);
    INTC_ClearPendingIRQ(IICA_IRQn);

    /* 配置速度模式 */
    if (speed == I2C_SPEED_STANDARD) {
        IICA->IICCTL01 = 0x00;            /* 标准模式 */
        IICA->IICWL0   = 0x4B;            /* 100Kbps@32MHz 低电平宽度 */
        IICA->IICWH0   = 0x53;            /* 100Kbps@32MHz 高电平宽度 */
    } else {
        IICA->IICCTL01 = 0x08;            /* 快速模式 */
        IICA->IICCTL01 |= 0x04;           /* 数字滤波器开启 */
        IICA->IICWL0   = 0x14;            /* 400Kbps@32MHz 低电平宽度 */
        IICA->IICWH0   = 0x12;            /* 400Kbps@32MHz 高电平宽度 */
    }

    IICA->IICCTL01 |= 0x01;              /* 选择fCLK/2 */
    IICA->SVA0      = 0x98;              /* 从机地址 */
    IICA->IICF0    |= 0x02;              /* 无需检测停止条件即可产生起始条件 */
    IICA->IICF0    |= 0x01;              /* 禁用通信预约 */
    IICA->IICCTL00 |= 0x08;              /* 第9个时钟下降沿产生中断 */
    IICA->IICCTL00 |= 0x04;              /* 使能应答 */
    IICA->IICCTL00 |= 0x80;              /* 使能IICA操作 */
    IICA->IICCTL00 |= 0x40;              /* 退出通信并进入待机模式 */

    /* 使能中断 */
    INTC_EnableIRQ(IICA_IRQn);

    /* 配置I2C引脚: SCL=P31, SDA=P30 (板级配置, 覆盖SDK默认) */
    i2c_port_init();

    return I2C_OK;
}

/**
  * @brief  I2C主机发送数据
  * @param  slave_addr: 从机地址 (7位, 不含R/W位)
  * @param  data: 发送数据缓冲区
  * @param  len: 发送数据长度
  * @param  timeout_ms: 超时时间(毫秒)
  * @retval I2C_OK: 成功, 其他: 错误码
  */
int I2C_MasterSend(uint8_t slave_addr, const uint8_t *data, uint16_t len, uint32_t timeout_ms)
{
    MD_STATUS status;
    uint32_t wait = 20;

    status = IICA0_MasterSend((uint8_t)((slave_addr << 1) & 0xFE), (uint8_t *)data, len, (uint8_t)wait);
    if (status != MD_OK) {
        return I2C_ERROR;
    }

    while (g_iica0_tx_end == 0) {
        delay_ms(1);
        if (timeout_ms > 0) {
            timeout_ms--;
            if (timeout_ms == 0) {
                return I2C_TIMEOUT;
            }
        }
    }

    return I2C_OK;
}

/**
  * @brief  I2C主机接收数据
  * @param  slave_addr: 从机地址 (7位, 不含R/W位)
  * @param  data: 接收数据缓冲区
  * @param  len: 接收数据长度
  * @param  timeout_ms: 超时时间(毫秒)
  * @retval I2C_OK: 成功, 其他: 错误码
  */
int I2C_MasterReceive(uint8_t slave_addr, uint8_t *data, uint16_t len, uint32_t timeout_ms)
{
    MD_STATUS status;
    uint32_t wait = 20;

    status = IICA0_MasterReceive((uint8_t)((slave_addr << 1) | 0x01), data, len, (uint8_t)wait);
    if (status != MD_OK) {
        return I2C_ERROR;
    }

    while (g_iica0_rx_end == 0) {
        delay_ms(1);
        if (timeout_ms > 0) {
            timeout_ms--;
            if (timeout_ms == 0) {
                return I2C_TIMEOUT;
            }
        }
    }

    return I2C_OK;
}

/**
  * @brief  I2C写入寄存器 (先发送寄存器地址, 再发送数据)
  * @param  slave_addr: 从机地址
  * @param  reg_addr: 寄存器地址
  * @param  data: 写入数据
  * @param  len: 数据长度
  * @retval I2C_OK: 成功, 其他: 错误码
  */
int I2C_WriteReg(uint8_t slave_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len)
{
    int ret;

    ret = I2C_MasterSend(slave_addr, &reg_addr, 1, 100);
    if (ret != I2C_OK) {
        return ret;
    }

    return I2C_MasterSend(slave_addr, data, len, 100);
}

/**
  * @brief  I2C读取寄存器 (先发送寄存器地址, 再读取数据)
  * @param  slave_addr: 从机地址
  * @param  reg_addr: 寄存器地址
  * @param  data: 读取数据缓冲区
  * @param  len: 数据长度
  * @retval I2C_OK: 成功, 其他: 错误码
  */
int I2C_ReadReg(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
    int ret;

    ret = I2C_MasterSend(slave_addr, &reg_addr, 1, 100);
    if (ret != I2C_OK) {
        return ret;
    }

    return I2C_MasterReceive(slave_addr, data, len, 100);
}

/**
  * @brief  I2C设备扫描 - 扫描总线上所有从机设备
  * @param  None
  * @retval 发现的设备数量
  */
int I2C_Scan(void)
{
    uint8_t addr;
    uint8_t dummy;
    int count = 0;

    printf("I2C Scan (SCL=P31, SDA=P30)\r\n");
    printf("     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n");

    for (addr = 0x08; addr < 0x78; addr++) {
        if ((addr & 0x0F) == 0) {
            printf("%02X: ", addr);
        }

        /* 尝试读取1字节来检测设备 */
        g_iica0_rx_end = 0;
        if (I2C_MasterReceive(addr, &dummy, 1, 50) == I2C_OK) {
            printf("%02X ", addr);
            count++;
        } else {
            printf("-- ");
        }

        if ((addr & 0x0F) == 0x0F) {
            printf("\r\n");
        }
    }

    printf("\r\nFound %d device(s)\r\n", count);
    return count;
}

/**
  * @brief  停止I2C模块
  */
void I2C_Stop(void)
{
    IICA0_Stop();
}
