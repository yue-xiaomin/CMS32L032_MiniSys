/**
  ******************************************************************************
  * @file    dataflash.h
  * @brief   数据Flash驱动 - 用于存储用户配置数据
  * @note    数据Flash区域: 0x500200, 大小: 1KB (2个扇区, 每扇区512字节)
  ******************************************************************************
  */
#ifndef DATAFLASH_H
#define DATAFLASH_H

#include "CMS32L032.h"

/** @defgroup DATAFLASH_Constants 数据Flash常量定义
  * @{
  */
#define DATAFLASH_BASE_ADDR     0x500200    /**< 数据Flash起始地址 */
#define DATAFLASH_SIZE          1024        /**< 数据Flash总大小(字节) */
#define DATAFLASH_SECTOR_SIZE   512         /**< 每个扇区大小(字节) */
#define DATAFLASH_SECTOR_COUNT  2           /**< 扇区总数 */
/** @} */

/** @defgroup DATAFLASH_API 数据Flash接口函数
  * @{
  */
/**
  * @brief  初始化数据Flash
  * @param  None
  * @retval None
  */
void DataFlash_Init(void);

/**
  * @brief  从数据Flash读取数据
  * @param  offset: 偏移地址 (0 ~ DATAFLASH_SIZE-1)
  * @param  buf: 读取数据存储缓冲区
  * @param  len: 读取字节数
  * @retval 0: 成功, -1: 参数错误
  */
int DataFlash_Read(uint16_t offset, uint8_t *buf, uint16_t len);

/**
  * @brief  向数据Flash写入数据
  * @param  offset: 偏移地址 (0 ~ DATAFLASH_SIZE-1)
  * @param  buf: 待写入数据缓冲区
  * @param  len: 写入字节数 (不能超过512字节)
  * @retval 0: 成功, -1: 参数错误
  */
int DataFlash_Write(uint16_t offset, uint8_t *buf, uint16_t len);

/**
  * @brief  擦除指定扇区
  * @param  sector: 扇区编号 (0 或 1)
  * @retval 0: 成功, -1: 参数错误
  */
int DataFlash_EraseSector(uint8_t sector);

/**
  * @brief  擦除全部数据Flash (2个扇区)
  * @param  None
  * @retval 0: 成功, 非0: 失败
  */
int DataFlash_EraseAll(void);
/** @} */

#endif
