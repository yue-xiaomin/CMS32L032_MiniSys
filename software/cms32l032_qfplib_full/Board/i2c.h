/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   I2C驱动 - 基于IICA0模块, 支持主从收发
  * @note    硬件连接: SCL=P31, SDA=P30
  ******************************************************************************
  */
#ifndef I2C_H
#define I2C_H

#include "CMS32L032.h"
#include <stdint.h>

/** @defgroup I2C_Constants I2C常量定义
  * @{
  */
#define I2C_OK          0   /**< 操作成功 */
#define I2C_ERROR       (-1) /**< 操作失败 */
#define I2C_TIMEOUT     (-2) /**< 超时错误 */
#define I2C_NACK        (-3) /**< 未收到应答 */
/** @} */

/** @defgroup I2C_Speed I2C速度模式
  * @{
  */
#define I2C_SPEED_STANDARD  0   /**< 标准模式: 100Kbps */
#define I2C_SPEED_FAST      1   /**< 快速模式: 400Kbps */
/** @} */

/** @defgroup I2C_API I2C接口函数
  * @{
  */
/**
  * @brief  初始化I2C模块
  * @param  speed: 速度模式 (I2C_SPEED_STANDARD 或 I2C_SPEED_FAST)
  * @retval I2C_OK: 成功, 其他: 错误码
  */
int I2C_Init(uint8_t speed);

/**
  * @brief  I2C主机发送数据
  * @param  slave_addr: 从机地址 (7位, 不含R/W位)
  * @param  data: 发送数据缓冲区
  * @param  len: 发送数据长度
  * @param  timeout_ms: 超时时间(毫秒), 0=不等待
  * @retval I2C_OK: 成功, 其他: 错误码
  */
int I2C_MasterSend(uint8_t slave_addr, const uint8_t *data, uint16_t len, uint32_t timeout_ms);

/**
  * @brief  I2C主机接收数据
  * @param  slave_addr: 从机地址 (7位, 不含R/W位)
  * @param  data: 接收数据缓冲区
  * @param  len: 接收数据长度
  * @param  timeout_ms: 超时时间(毫秒), 0=不等待
  * @retval I2C_OK: 成功, 其他: 错误码
  */
int I2C_MasterReceive(uint8_t slave_addr, uint8_t *data, uint16_t len, uint32_t timeout_ms);

/**
  * @brief  I2C写入寄存器 (先发送寄存器地址, 再发送数据)
  * @param  slave_addr: 从机地址
  * @param  reg_addr: 寄存器地址
  * @param  data: 写入数据
  * @param  len: 数据长度
  * @retval I2C_OK: 成功, 其他: 错误码
  */
int I2C_WriteReg(uint8_t slave_addr, uint8_t reg_addr, const uint8_t *data, uint16_t len);

/**
  * @brief  I2C读取寄存器 (先发送寄存器地址, 再读取数据)
  * @param  slave_addr: 从机地址
  * @param  reg_addr: 寄存器地址
  * @param  data: 读取数据缓冲区
  * @param  len: 数据长度
  * @retval I2C_OK: 成功, 其他: 错误码
  */
int I2C_ReadReg(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

/**
  * @brief  I2C设备扫描 - 扫描总线上所有从机设备
  * @retval 发现的设备数量
  */
int I2C_Scan(void);

/**
  * @brief  停止I2C模块
  * @retval None
  */
void I2C_Stop(void);
/** @} */

#endif
