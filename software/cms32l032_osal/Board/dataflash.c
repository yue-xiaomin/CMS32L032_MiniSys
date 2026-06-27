/**
  ******************************************************************************
  * @file    dataflash.c
  * @brief   数据Flash驱动实现
  * @note    数据Flash区域: 0x500200, 大小: 1KB
  *          扇区0: 0x500200 ~ 0x5003FF (512字节)
  *          扇区1: 0x500400 ~ 0x5005FF (512字节)
  ******************************************************************************
  */

/* 包含头文件 */
#include "dataflash.h"
#include "flash.h"

/** @brief 各扇区起始地址表 */
static uint32_t sector_base[] = {
    DATAFLASH_BASE_ADDR,                        /* 扇区0起始地址 */
    DATAFLASH_BASE_ADDR + DATAFLASH_SECTOR_SIZE /* 扇区1起始地址 */
};

/**
  * @brief  初始化数据Flash
  * @param  None
  * @retval None
  */
void DataFlash_Init(void)
{
    /* 目前无需特殊初始化 */
}

/**
  * @brief  从数据Flash读取数据
  * @param  offset: 偏移地址 (0 ~ DATAFLASH_SIZE-1)
  * @param  buf: 读取数据存储缓冲区
  * @param  len: 读取字节数
  * @retval 0: 成功, -1: 参数错误
  */
int DataFlash_Read(uint16_t offset, uint8_t *buf, uint16_t len)
{
    uint16_t i;
    uint8_t *ptr;

    /* 参数检查: 偏移+长度不能超过总大小 */
    if (offset + len > DATAFLASH_SIZE) {
        return -1;
    }

    /* 计算实际Flash地址并逐字节读取 */
    ptr = (uint8_t *)(DATAFLASH_BASE_ADDR + offset);
    for (i = 0; i < len; i++) {
        buf[i] = ptr[i];
    }

    return 0;
}

/**
  * @brief  向数据Flash写入数据
  * @note   内部自动处理擦除, 如目标区域为空则直接写入, 否则先擦除再写入
  * @param  offset: 偏移地址 (0 ~ DATAFLASH_SIZE-1)
  * @param  buf: 待写入数据缓冲区
  * @param  len: 写入字节数 (单次不能超过512字节)
  * @retval 0: 成功, -1: 参数错误
  */
int DataFlash_Write(uint16_t offset, uint8_t *buf, uint16_t len)
{
    /* 参数检查 */
    if (offset + len > DATAFLASH_SIZE) {
        return -1;
    }

    /* 调用底层flash_write, 自动判断是否需要擦除 */
    return flash_write(DATAFLASH_BASE_ADDR + offset, len, buf);
}

/**
  * @brief  擦除指定扇区
  * @param  sector: 扇区编号 (0 或 1)
  * @retval 0: 成功, -1: 参数错误
  */
int DataFlash_EraseSector(uint8_t sector)
{
    /* 参数检查 */
    if (sector >= DATAFLASH_SECTOR_COUNT) {
        return -1;
    }

    /* 擦除对应扇区 */
    return EraseSector(sector_base[sector]);
}

/**
  * @brief  擦除全部数据Flash
  * @note   会擦除2个扇区, 共1KB数据全部清空为0xFF
  * @param  None
  * @retval 0: 成功, 非0: 失败
  */
int DataFlash_EraseAll(void)
{
    uint8_t i;
    int ret;

    /* 逐个扇区擦除 */
    for (i = 0; i < DATAFLASH_SECTOR_COUNT; i++) {
        ret = EraseSector(sector_base[i]);
        if (ret != 0) {
            return ret;
        }
    }

    return 0;
}
