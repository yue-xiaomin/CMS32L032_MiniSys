/**************************************************************************//**
 * @file     system_CMS32L032.c
 * @brief    CMSIS Cortex-M0+ 设备外设访问层源文件 (CMS32L032)
 * @version  1.0.0
 * @date     2019/12/24
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include "CMS32L032.h"


/** @addtogroup Configuration_of_User_Option_Byte
  * @{
  */

/* HOCO频率配置枚举 */
typedef enum {
  HOCO_FREQ_64MHZ = 0xE8, 	/*!< fHOCO = 64MHz, fIH = 64MHz  	*/
  HOCO_FREQ_48MHZ = 0xE0, 	/*!< fHOCO = 48MHz, fIH = 48MHz  	*/
  HOCO_FREQ_32MHZ = 0xE9, 	/*!< fHOCO = 64MHz, fIH = 32MHz  	*/
  HOCO_FREQ_24MHZ = 0xE1, 	/*!< fHOCO = 48MHz, fIH = 24MHz  	*/
  HOCO_FREQ_16MHZ = 0xEA, 	/*!< fHOCO = 64MHz, fIH = 16MHz  	*/
  HOCO_FREQ_12MHZ = 0xE2, 	/*!< fHOCO = 48MHz, fIH = 12MHz  	*/
  HOCO_FREQ_8MHZ  = 0xEB, 	/*!< fHOCO = 64MHz, fIH =  8MHz  	*/
  HOCO_FREQ_6MHZ  = 0xE3, 	/*!< fHOCO = 48MHz, fIH =  6MHz  	*/
  HOCO_FREQ_4MHZ  = 0xEC, 	/*!< fHOCO = 64MHz, fIH =  4MHz  	*/
  HOCO_FREQ_3MHZ  = 0xE4, 	/*!< fHOCO = 48MHz, fIH =  3MHz  	*/
  HOCO_FREQ_2MHZ  = 0xED, 	/*!< fHOCO = 64MHz, fIH =  2MHz  	*/
} hoco_freq_t;

/*----------------------------------------------------------------------------
  用户选项字节
 *----------------------------------------------------------------------------*/
/* 注意: 在此处添加设备初始化所需的宏定义
         以下是不同系统频率的示例 */

//-------- <<< 使用上下文菜单中的配置向导 >>> ------------------
const uint8_t user_opt_data[4] __attribute__((used)) __attribute__((section(".ARM.__AT_0x000000C0"))) =
{

/**
 * @brief WDT控制字节 (C0H)
 * 详见用户手册
 *     7   |    6    |    5    |   4   |   3   |   2   |   1   |   0
 * --------|---------|---------|-------|-------|-------|-------|----------
 *  WDTINT | WINDOW1 | WINDOW0 | WDTON | WDCS2 | WDCS1 | WDCS0 | WDSTBYON
 * --------|---------|---------|-------|-------|-------|-------|----------
 */
// <h> WDT控制选项字节 (C0H)
//   <e.4> 使能WDT (WDTON)
//   <o.5..6> 看门狗窗口打开周期设置                   <2=> 75%        <3=> 100%
//   <o.1..3> 看门狗溢出时间设置                       <0=> 2^6/fIL    <1=> 2^7/fIL
//                                                     <2=> 2^8/fIL    <3=> 2^9/fIL
//                                                     <4=> 2^11/fIL   <5=> 2^13/fIL
//                                                     <6=> 2^14/fIL   <7=> 2^16/fIL
//   <e.0>    待机模式下运行设置 (WDSTBYON)
//            <i> WDT在SLEEP/DEEPSLEEP模式下运行
//     </e>
//   <e.7>    中断使能
//            <i> 当溢出时间达到75% + 1/2 fIL时产生间隔中断
//     </e>
//   </e>
// </h>
    0x0E,

/**
 * @brief LVD控制字节 (C1H)
 * 详见用户手册
 *    7   |   6   |   5   |   4   |   3   |   2   |    1    |    0
 * -------|-------|-------|-------|-------|-------|---------|----------
 *  VPOC2 | VPOC1 | VPOC0 |   1   | LVIS1 | LVIS0 | LVIMDS1 | LVIMDS0
 * -------|-------|-------|-------|-------|-------|---------|----------
 */
// <h> LVD控制选项字节 (C1H)
//     <o.0..7> 电压检测设置 (VLVD)                    <0xFF=> ( LVD关闭 )
//                                                     <0x3D=> VLVD = 1.88V/1.84V    ( 中断模式 )
//                                                     <0x39=> VLVD = 1.98V/1.94V    ( 中断模式 )
//                                                     <0x35=> VLVD = 2.09V/2.04V    ( 中断模式 )
//                                                     <0x5D=> VLVD = 2.50V/2.45V    ( 中断模式 )
//                                                     <0x59=> VLVD = 2.61V/2.55V    ( 中断模式 )
//                                                     <0x55=> VLVD = 2.71V/2.65V    ( 中断模式 )
//                                                     <0x7D=> VLVD = 2.81V/2.75V    ( 中断模式 )
//                                                     <0x79=> VLVD = 2.92V/2.86V    ( 中断模式 )
//                                                     <0x75=> VLVD = 3.02V/2.96V    ( 中断模式 )
//                                                     <0x3F=> VLVD = 1.88V/1.84V    ( 复位模式 )
//                                                     <0x3B=> VLVD = 1.98V/1.94V    ( 复位模式 )
//                                                     <0x37=> VLVD = 2.09V/2.04V    ( 复位模式 )
//                                                     <0x5F=> VLVD = 2.50V/2.45V    ( 复位模式 )
//                                                     <0x5B=> VLVD = 2.61V/2.55V    ( 复位模式 )
//                                                     <0x57=> VLVD = 2.71V/2.65V    ( 复位模式 )
//                                                     <0x7F=> VLVD = 2.81V/2.75V    ( 复位模式 )
//                                                     <0x7B=> VLVD = 2.92V/2.86V    ( 复位模式 )
//                                                     <0x77=> VLVD = 3.02V/2.96V    ( 复位模式 )
//                                                     <0x3A=> VLVDH = 1.98V/1.94V, VLVDL = 1.84V    ( 中断和复位模式 )
//                                                     <0x36=> VLVDH = 2.09V/2.04V, VLVDL = 1.84V    ( 中断和复位模式 )
//                                                     <0x32=> VLVDH = 3.13V/3.06V, VLVDL = 1.84V    ( 中断和复位模式 )
//                                                     <0x5A=> VLVDH = 2.61V/2.55V, VLVDL = 2.45V    ( 中断和复位模式 )
//                                                     <0x56=> VLVDH = 2.71V/2.65V, VLVDL = 2.45V    ( 中断和复位模式 )
//                                                     <0x52=> VLVDH = 3.75V/3.67V, VLVDL = 2.45V    ( 中断和复位模式 )
//                                                     <0x7A=> VLVDH = 2.92V/2.86V, VLVDL = 2.75V    ( 中断和复位模式 )
//                                                     <0x76=> VLVDH = 3.02V/2.96V, VLVDL = 2.75V    ( 中断和复位模式 )
//                                                     <0x72=> VLVDH = 4.06V/3.98V, VLVDL = 2.75V    ( 中断和复位模式 )
// </h>
    0xFF,

/**
 * @brief HOCO控制字节 (FRQSEL)
 * 详见用户手册
 *    7   |   6   |   5   |    4    |    3    |    2    |    1    |    0
 * -------|-------|-------|---------|---------|---------|---------|---------
 *    1   |   1   |   1   | FRQSEL4 | FRQSEL3 | FRQSEL2 | FRQSEL1 | FRQSEL0
 * -------|-------|-------|---------|---------|---------|---------|---------
 */
// <h> HOCO控制选项字节 (C2H)
//   <o.0..4> 高速OCO时钟设置                          <0xE8=> fHOCO = 64MHz, fIH = 64MHz
//                                                     <0xE0=> fHOCO = 48MHz, fIH = 48MHz
//                                                     <0xE9=> fHOCO = 64MHz, fIH = 32MHz
//                                                     <0xE1=> fHOCO = 48MHz, fIH = 24MHz
//                                                     <0xEA=> fHOCO = 64MHz, fIH = 16MHz
//                                                     <0xE2=> fHOCO = 48MHz, fIH = 12MHz
//                                                     <0xEB=> fHOCO = 64MHz, fIH =  8MHz
//                                                     <0xE3=> fHOCO = 48MHz, fIH =  6MHz
//                                                     <0xEC=> fHOCO = 64MHz, fIH =  4MHz
//                                                     <0xE4=> fHOCO = 48MHz, fIH =  3MHz
//                                                     <0xED=> fHOCO = 64MHz, fIH =  2MHz
// </h>
    0xE8, 

/**
 * @brief Flash保护控制字节
 * 详见用户手册
 */
// <h> OCD控制选项字节 (C3H)
//   <o.0..7> 片上调试设置 (OCDEN)                   <0xFF=> 使能  <0xC3=> 禁止
//            <i> OCDM(500004H) == 0x3C && OCDEN == 0xC3: 调试器无法擦除/写入/读取Flash
//            <i> OCDM(500004H) != 0x3C && OCDEN == 0xC3: 调试器只能整片擦除Flash, 无法写入/读取
// </h>
    0xFF

};

//-------- <<< 配置部分结束 >>> ------------------
/** @} */ /* 用户选项字节配置组结束 */

/*----------------------------------------------------------------------------
  系统时钟变量
 *----------------------------------------------------------------------------*/
/* 注意: 使用系统初始化后获得的系统时钟频率值初始化SystemCoreClock
         即调用SystemInit()后的系统时钟频率 */
uint32_t SystemCoreClock;  		/* 系统时钟频率 (内核时钟) */



/*----------------------------------------------------------------------------
  时钟函数
 *----------------------------------------------------------------------------*/
/**
  * @brief  获取HOCO时钟频率
  * @param  None
  * @retval HOCO时钟频率(Hz)
  */
uint32_t CLK_GetHocoFreq(void)
{

  uint32_t freq;
  uint8_t  frqsel  = (*(uint8_t *)0x000000C2U);  /* 读取选项字节C2H */
           frqsel &= 0xF8;  	/* 屏蔽低3位 */
           frqsel |= CGC->HOCODIV;	/* 加上HOCODIV分频值 */

  freq = 1000000U;  /* 默认fIH = 1MHz, 以下情况除外 */

  switch(frqsel)
  {
      case HOCO_FREQ_64MHZ:
          freq = 64000000U; 	/* fIH = 64MHz 	*/
          break;
      case HOCO_FREQ_48MHZ:
          freq = 48000000U; 	/* fIH = 48MHz 	*/
          break;
      case HOCO_FREQ_32MHZ:
          freq = 32000000U; 	/* fIH = 32MHz 	*/
          break;
      case HOCO_FREQ_24MHZ:
          freq = 24000000U; 	/* fIH = 24MHz 	*/
          break;
      case HOCO_FREQ_16MHZ:
          freq = 16000000U; 	/* fIH = 16MHz 	*/
          break;
      case HOCO_FREQ_12MHZ:
          freq = 12000000U; 	/* fIH = 12MHz 	*/
          break;
      case HOCO_FREQ_8MHZ:
          freq = 8000000U; 	/* fIH = 8MHz 	*/
          break;
      case HOCO_FREQ_6MHZ:
          freq = 6000000U; 	/* fIH = 6MHz 	*/
          break;
      case HOCO_FREQ_4MHZ:
          freq = 4000000U; 	/* fIH = 4MHz 	*/
          break;
      case HOCO_FREQ_3MHZ:
          freq = 3000000U; 	/* fIH = 3MHz 	*/
          break;
      case HOCO_FREQ_2MHZ:
          freq = 2000000U; 	/* fIH = 2MHz 	*/
          break;
  }

  return(freq);
}

/**
  * @brief  更新系统时钟频率
  * @note   根据当前寄存器设置计算系统频率
  *         用户修改寄存器后可调用此函数获取新的系统时钟
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
  SystemCoreClock = CLK_GetHocoFreq();
}

/**
  * @brief  系统初始化函数
  * @note   此函数在main()之前调用, 不要使用全局变量
  *         RW段可能在此函数之后被覆盖
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
  /* 禁止RAM奇偶校验错误复位 */
  SAF->RPECTL = 0x80U;

  /* 配置WDT */
  CGC->WDTCFG0 = 0x1A;
  CGC->WDTCFG1 = 0x2B;
  CGC->WDTCFG2 = 0x3C;
  CGC->WDTCFG3 = 0x4D;

  /* 调试停止控制 */
  DBG->DBGSTOPCR = 0;

  /* 获取系统时钟频率 */
  SystemCoreClock = CLK_GetHocoFreq();

#if 1  //Driver添加xxx_user.c后可以使用，后续需要自己根据需要调整优先级  
  /* 清除NVIC所有中断挂起位 */
  NVIC->ICPR[0U] = 0xFFFFFFFF;

  /* 使能NVIC所有中断 */
  NVIC->ISER[0U] = 0xFFFFFFFF;

  /* 设置NVIC所有中断优先级为最低 */
  NVIC->IP[0U] = 0xC0C0C0C0;
  NVIC->IP[1U] = 0xC0C0C0C0;
  NVIC->IP[2U] = 0xC0C0C0C0;
  NVIC->IP[3U] = 0xC0C0C0C0;
  NVIC->IP[4U] = 0xC0C0C0C0;
  NVIC->IP[5U] = 0xC0C0C0C0;
  NVIC->IP[6U] = 0xC0C0C0C0;
  NVIC->IP[7U] = 0xC0C0C0C0;
#endif

  /* 重启看门狗定时器 */
  if(user_opt_data[0]&0x10) //add：只有开启后才运行重新计数
    WDT->WDTE = 0xACU;
}

/***********************************************************************************************************************
* 函数名称: IRQ00_Handler
* 功能说明: LVD低压检测中断处理函数
* 输入参数: 无
* 返回值:   无
***********************************************************************************************************************/
void IRQ00_Handler(void)
{
	INTC_ClearPendingIRQ(LVI_IRQn);
}
