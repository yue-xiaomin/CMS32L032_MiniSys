/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    userdefine.h
* @brief   This file includes user definition.
* @version 1.0.0
* @date    2019/12/24
***********************************************************************************************************************/
#ifndef _USER_DEF_H
#define _USER_DEF_H

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/
#ifndef __TYPEDEF__

typedef unsigned short 	MD_STATUS;
/* Status list definition */
#define MD_STATUSBASE        (0x00U)
#define MD_OK                (MD_STATUSBASE + 0x00U) /* register setting OK */
#define MD_SPT               (MD_STATUSBASE + 0x01U) /* IIC stop */
#define MD_NACK              (MD_STATUSBASE + 0x02U) /* IIC no ACK */
#define MD_BUSY1             (MD_STATUSBASE + 0x03U) /* busy 1 */
#define MD_BUSY2             (MD_STATUSBASE + 0x04U) /* busy 2 */
#define MD_OVERRUN           (MD_STATUSBASE + 0x05U) /* IIC OVERRUN occur */

/* Error list definition */
#define MD_ERRORBASE         (0x80U)
#define MD_ERROR             (MD_ERRORBASE + 0x00U)  /* error */
#define MD_ARGERROR          (MD_ERRORBASE + 0x01U)  /* error agrument input error */
#define MD_ERROR1            (MD_ERRORBASE + 0x02U)  /* error 1 */
#define MD_ERROR2            (MD_ERRORBASE + 0x03U)  /* error 2 */
#define MD_ERROR3            (MD_ERRORBASE + 0x04U)  /* error 3 */
#define MD_ERROR4            (MD_ERRORBASE + 0x05U)  /* error 4 */
#define MD_ERROR5            (MD_ERRORBASE + 0x06U)  /* error 5 */
#endif

#define TESOPT	*((volatile uint8_t *)(0x4004384C))  /*!< (@ 0x4004384C) PGA protect register                          */
#define TESCTL	*((volatile uint8_t *)(0x4004384D))  /*!< (@ 0x4004384D) PGA output control register                   */
#define TRMW    *((volatile uint8_t *)(0x40021C08))
#define TRMR    *((volatile uint8_t *)(0x40021C09))
#define TRMT    *((volatile uint8_t *)(0x40021C0A))
#define CNTLD   *((volatile uint16_t *)(0x40021C28)) /*!< (@ 0x40021C28) counter load value of wakeup time             */
	
//#define RTL_SIMULATION

/***********************************************************************************************************************
Macro definitions of SCI usage:
Each channel of SCI has three functions: UART, SPI, and IIC. You can only choose one function to use.
***********************************************************************************************************************/
/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
#define USE_SCI_UART0_TX      /*! Using CH0 of SCI0 as UART Transmitter */
//#define USE_SCI_SPI00         /*! Using CH0 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC00         /*! Using CH0 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
#define USE_SCI_UART0_RX      /*! Using CH1 of SCI0 as UART Receiver */
//#define USE_SCI_SPI01         /*! Using CH1 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC01         /*! Using CH1 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
#define USE_SCI_UART1_TX      /*! Using CH2 of SCI0 as UART Transmitter */
//#define USE_SCI_SPI10         /*! Using CH2 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC10         /*! Using CH2 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can only define ONE of the following THREE MACROs according to your application */
#define USE_SCI_UART1_RX      /*! Using CH3 of SCI0 as UART Receiver */
//#define USE_SCI_SPI11         /*! Using CH3 of SCI0 as SPI Transmitter or Receiver */
//#define USE_SCI_IIC11         /*! Using CH3 of SCI0 as IIC Transmitter or Receiver */

/* ToDo: You can define the following MACRO and USE_SCI_UART2_TX or USE_SCI_UART2_RX MACROs to use Infra-Red transmitter or receiver */
//#define USE_IRDA              /*! Enable Infra-Red transmission with UART2 */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
    SPI_MODE_0 = 0,  // Mode 0: CPOL = 0, CPHA = 0; i.e. CKP = 1, DAP = 1 
    SPI_MODE_1 = 1,  // Mode 1: CPOL = 0, CPHA = 1; i.e. CKP = 1, DAP = 0 
    SPI_MODE_2 = 2,  // Mode 2: CPOL = 1, CPHA = 0; i.e. CKP = 0, DAP = 1 
    SPI_MODE_3 = 3,  // Mode 3: CPOL = 1, CPHA = 1; i.e. CKP = 0, DAP = 0 
} spi_mode_t;

/***********************************************************************************************************************
GPIO Typedef definitions
***********************************************************************************************************************/
#define GPIO_FUNC_GPIO 0x00
#define GPIO_FUNC_INTP0 0x02
#define GPIO_FUNC_INTP1 0x03
#define GPIO_FUNC_INTP2 0x04
#define GPIO_FUNC_INTP3 0x05
#define GPIO_FUNC_TI00 0x06
#define GPIO_FUNC_TI01 0x07
#define GPIO_FUNC_TI02 0x08
#define GPIO_FUNC_TI03 0x09
#define GPIO_FUNC_TI10 0x0A
#define GPIO_FUNC_TI11 0x0B
#define GPIO_FUNC_TI12 0x0C
#define GPIO_FUNC_TI13 0x0D
#define GPIO_FUNC_TO00 0x0E
#define GPIO_FUNC_TO01 0x0F
#define GPIO_FUNC_TO02 0x10
#define GPIO_FUNC_TO03 0x11
#define GPIO_FUNC_TO10 0x12
#define GPIO_FUNC_TO11 0x13
#define GPIO_FUNC_TO12 0x14
#define GPIO_FUNC_TO13 0x15
#define GPIO_FUNC_SCLA0 0x16
#define GPIO_FUNC_SDA0 0x17
#define GPIO_FUNC_CLKBUZ0 0x18
#define GPIO_FUNC_CLKBUZ1 0x19
#define GPIO_FUNC_RTC1HZ 0x1A
#define GPIO_FUNC_SPI_SS 0x1C
#define GPIO_FUNC_SPI_MOSI 0x1D
#define GPIO_FUNC_SPI_MISO 0x1E
#define GPIO_FUNC_SPI_CLK 0x1F
#define GPIO_FUNC_SS00 0x26
#define GPIO_FUNC_SS10 0x27
#define GPIO_FUNC_SCLK00 0x28
#define GPIO_FUNC_SCL00 0x28

#define GPIO_FUNC_SCLK01 0x29
#define GPIO_FUNC_SCL01 0x29

#define GPIO_FUNC_SCLK10 0x2A
#define GPIO_FUNC_SCL10 0x2A

#define GPIO_FUNC_SCLK11 0x2B
#define GPIO_FUNC_SCL11 0x2B

#define GPIO_FUNC_SDI00 0x2C
#define GPIO_FUNC_SDA00 0x2C
#define GPIO_FUNC_RXD0 0x2C

#define GPIO_FUNC_SDI01 0x2D
#define GPIO_FUNC_SDA01 0x2D

#define GPIO_FUNC_SDI10 0x2E
#define GPIO_FUNC_SDA10 0x2E
#define GPIO_FUNC_RXD1 0x2E

#define GPIO_FUNC_SDI11 0x2F
#define GPIO_FUNC_SDA11 0x2F

#define GPIO_FUNC_SDO00 0x30
#define GPIO_FUNC_TXD0 0x30
#define GPIO_FUNC_SDO01 0x31
#define GPIO_FUNC_SDO10 0x32
#define GPIO_FUNC_TXD1 0x32
#define GPIO_FUNC_SDO11 0x33
#define GPIO_FUNC_EPWMO00 0x38
#define GPIO_FUNC_EPWMO01 0x39
#define GPIO_FUNC_EPWMO02 0x3A
#define GPIO_FUNC_EPWMO03 0x3B
#define GPIO_FUNC_EPWMO04 0x3C
#define GPIO_FUNC_EPWMO05 0x3D
#define GPIO_FUNC_EPWMO06 0x3E
#define GPIO_FUNC_EPWMO07 0x3F



/** @addtogroup Peripherals_Port_Setting_Definations
  * @{
  */

/* ================================================================================================================== */
/* ================                                       TM40                                       ================ */
/* ================================================================================================================== */
/**
  * @brief TM40 TI00~3 and TO00~3 Port Setting 
  */

#define TI00_PORT_SETTING() do{ \
        PORT->P10CFG = GPIO_FUNC_TI00;	    /* P10 default alternate function */ \
        PORT->PM1  |=  (1 << 0);    /* P10 is used as TI00 input */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 digital function */ \
}while(0)

#define TI01_PORT_SETTING() do{ \
        PORT->P11CFG = GPIO_FUNC_TI01;	    /* P11 default alternate function */ \
        PORT->PM1  |=  (1 << 1);    /* P11 is used as TI01 input */ \
        PORT->PMC1 &= ~(1 << 1);    /* P11 digital function */ \
}while(0)

#define TI02_PORT_SETTING() do{ \
        PORT->P22CFG = GPIO_FUNC_TI02;	    /* P22 default alternate function */ \
        PORT->PM2  |=  (1 << 2);    /* P22 is used as TI02 input */ \
        PORT->PMC2 &= ~(1 << 2);    /* P22 digital function */ \
}while(0)

#define TI03_PORT_SETTING() do{ \
        PORT->P23CFG = GPIO_FUNC_TI03;	    /* P23 default alternate function */ \
        PORT->PM2  |=  (1 << 3);    /* P23 is used as TI03 input */ \
        PORT->PMC2 &= ~(1 << 3);    /* P23 digital function */ \
}while(0)

#define TO00_PORT_SETTING() do{ \
        PORT->P30CFG = GPIO_FUNC_TO00;	    /* P30 default alternate fucntion */ \
        PORT->P3   &= ~(1 << 0);    /* P30 output low level */ \
        PORT->PM3  &= ~(1 << 0);    /* P30 is used as TO00 output */ \
        PORT->POM3 &= ~(1 << 0);    /* P30 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
}while(0)

#define TO01_PORT_SETTING() do{ \
        PORT->P31CFG = GPIO_FUNC_TO01;	    /* P31 default alternate function */ \
        PORT->P3   &= ~(1 << 1);    /* P31 output low level */ \
        PORT->PM3  &= ~(1 << 1);    /* P31 is used as TO01 output */ \
        PORT->POM3 &= ~(1 << 1);    /* P31 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
}while(0)

#define TO02_PORT_SETTING() do{ \
        PORT->P32CFG = GPIO_FUNC_TO02;	    /* P32 default alternate function */ \
        PORT->P3   &= ~(1 << 2);    /* P32 output low level */ \
        PORT->PM3  &= ~(1 << 2);    /* P32 is used as TO02 output */ \
        PORT->POM3 &= ~(1 << 2);    /* P32 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 2);    /* P32 digital function */ \
}while(0)

#define TO03_PORT_SETTING() do{ \
        PORT->P31CFG = GPIO_FUNC_TO03;	    /* P33 default alternate function */ \
        PORT->P3   &= ~(1 << 3);    /* P33 output low level */ \
        PORT->PM3  &= ~(1 << 3);    /* P33 is used as TO03 output */ \
        PORT->POM3 &= ~(1 << 3);    /* P33 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 3);    /* P33 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       TM41                                       ================ */
/* ================================================================================================================== */

/**
  * @brief TM41 TI10~3 and TO10~3 Port Setting 
  */

/* ToDo: You can allocate the TI10 to any desired pins with TI10PCFG register */
#define TI10_PORT_SETTING() do{ \
        PORT->P10CFG = GPIO_FUNC_TI10;	    /* allocate TI10 to P10 */ \
        PORT->PM1  |=  (1 << 0);    /* P10 is used as TI10 input */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 digital function */ \
}while(0)

/* ToDo: You can allocate the TI11 to any desired pins with TI11PCFG register */
#define TI11_PORT_SETTING() do{ \
        PORT->P11CFG = GPIO_FUNC_TI11;	    /* allocate TI11 to P11 */ \
        PORT->PM1  |=  (1 << 1);    /* P11 is used as TI11 input */ \
        PORT->PMC1 &= ~(1 << 1);    /* P11 digital function */ \
}while(0)

/* ToDo: You can allocate the TI12 to any desired pins with TI12PCFG register */
#define TI12_PORT_SETTING() do{ \
        PORT->P12CFG = GPIO_FUNC_TI12;	    /* allocate TI12 to P12 */ \
        PORT->PM1  |=  (1 << 2);    /* P12 is used as TI12 input */ \
        PORT->PMC1 &= ~(1 << 2);    /* P12 digital function */ \
}while(0)

/* ToDo: You can allocate the TI13 to any desired pins with TI13PCFG register */
#define TI13_PORT_SETTING() do{ \
        PORT->P13CFG = GPIO_FUNC_TI13;	    /* allocate TI13 to P13 */ \
        PORT->PM1  |=  (1 << 3);    /* P13 is used as TI13 input */ \
        PORT->PMC1 &= ~(1 << 3);    /* P13 digital function */ \
}while(0)

/* ToDo: You can allocate the TO10 to any desired pins with PxxCFG register */
#define TO10_PORT_SETTING() do{ \
        PORT->P34CFG = GPIO_FUNC_TO10;	    /* allocate TO10 to P34 */ \
        PORT->P3   &= ~(1 << 4);    /* P34 output low level */ \
        PORT->PM3  &= ~(1 << 4);    /* P34 is used as TO10 output */ \
        PORT->POM3 &= ~(1 << 4);    /* P34 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 4);    /* P34 digital function */ \
}while(0)

/* ToDo: You can allocate the TO11 to any desired pins with PxxCFG register */
#define TO11_PORT_SETTING() do{ \
        PORT->P35CFG = GPIO_FUNC_TO11;	    /* allocate TO11 to P35 */ \
        PORT->P3   &= ~(1 << 5);    /* P35 output low level */ \
        PORT->PM3  &= ~(1 << 5);    /* P35 is used as TO11 output */ \
        PORT->POM3 &= ~(1 << 5);    /* P35 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 5);    /* P35 digital function */ \
}while(0)

/* ToDo: You can allocate the TO12 to any desired pins with PxxCFG register */
#define TO12_PORT_SETTING() do{ \
        PORT->P36CFG = GPIO_FUNC_TO12;	    /* allocate TO12 to P36 */ \
        PORT->P3   &= ~(1 << 6);    /* P36 output low level */ \
        PORT->PM3  &= ~(1 << 6);    /* P36 is used as TO12 output */ \
        PORT->POM3 &= ~(1 << 6);    /* P36 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 6);    /* P36 digital function */ \
}while(0)

/* ToDo: You can allocate the TO13 to any desired pins with PxxCFG register */
#define TO13_PORT_SETTING() do{ \
        PORT->P37CFG = GPIO_FUNC_TO13;	    /* allocate TO13 to P37 */ \
        PORT->P3   &= ~(1 << 7);    /* P37 output low level */ \
        PORT->PM3  &= ~(1 << 7);    /* P37 is used as TO13 output */ \
        PORT->POM3 &= ~(1 << 7);    /* P37 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 7);    /* P37 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       EPWM                                       ================ */
/* ================================================================================================================== */

/**
  * @brief EPWM Port Setting（Alternative to fixed port)
  */

/* ToDo: You should modify the defination according to your application */
#define EPWM_PORT_SETTING() do{ \
        EPWMO00_PORT_SETTING(); \
        EPWMO01_PORT_SETTING(); \
        EPWMO02_PORT_SETTING(); \
        EPWMO03_PORT_SETTING(); \
        EPWMO04_PORT_SETTING(); \
        EPWMO05_PORT_SETTING(); \
        EPWMO06_PORT_SETTING(); \
        EPWMO07_PORT_SETTING(); \
}while(0)

#define EPWMO00_PORT_SETTING() do{ \
        PORT->P30CFG = GPIO_FUNC_EPWMO00;        /* P30 default Alternate function */ \
        PORT->P3   &= ~(1 << 0);    /* P30 output low level */ \
        PORT->PM3  &= ~(1 << 0);    /* P30 is used as EPWMO00 output */ \
        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
}while(0)

#define EPWMO01_PORT_SETTING() do{ \
        PORT->P31CFG = GPIO_FUNC_EPWMO01;        /* P31 default Alternate function */ \
        PORT->P3   &= ~(1 << 1);    /* P31 output low level */ \
        PORT->PM3  &= ~(1 << 1);    /* P31 is used as EPWMO01 output */ \
        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
}while(0)

#define EPWMO02_PORT_SETTING() do{ \
        PORT->P32CFG = GPIO_FUNC_EPWMO02;        /* P32 default Alternate function */ \
        PORT->P3   &= ~(1 << 2);    /* P32 output low level */ \
        PORT->PM3  &= ~(1 << 2);    /* P32 is used as EPWMO02 output */ \
        PORT->PMC3 &= ~(1 << 2);    /* P32 digital function */ \
}while(0)

#define EPWMO03_PORT_SETTING() do{ \
        PORT->P33CFG = GPIO_FUNC_EPWMO03;        /* P33 default Alternate function */ \
        PORT->P3   &= ~(1 << 3);    /* P33 output low level */ \
        PORT->PM3  &= ~(1 << 3);    /* P33 is used as EPWMO03 output */ \
        PORT->PMC3 &= ~(1 << 3);    /* P33 digital function */ \
}while(0)

#define EPWMO04_PORT_SETTING() do{ \
        PORT->P34CFG = GPIO_FUNC_EPWMO04;        /* P34 default Alternate function */ \
        PORT->P3   &= ~(1 << 4);    /* P34 output low level */ \
        PORT->PM3  &= ~(1 << 4);    /* P34 is used as EPWMO04 output */ \
        PORT->PMC3 &= ~(1 << 4);    /* P34 digital function */ \
}while(0)

#define EPWMO05_PORT_SETTING() do{ \
        PORT->P35CFG = GPIO_FUNC_EPWMO05;        /* P35 default Alternate function */ \
        PORT->P3   &= ~(1 << 5);    /* P35 output low level */ \
        PORT->PM3  &= ~(1 << 5);    /* P35 is used as EPWMO05 output */ \
        PORT->PMC3 &= ~(1 << 5);    /* P35 digital function */ \
}while(0)

#define EPWMO06_PORT_SETTING() do{ \
        PORT->P36CFG = GPIO_FUNC_EPWMO06;        /* P36 default Alternate function */ \
        PORT->P3   &= ~(1 << 6);    /* P36 output low level */ \
        PORT->PM3  &= ~(1 << 6);    /* P36 is used as EPWMO06 output */ \
        PORT->PMC3 &= ~(1 << 6);    /* P36 digital function */ \
}while(0)

#define EPWMO07_PORT_SETTING() do{ \
        PORT->P37CFG = GPIO_FUNC_EPWMO07;        /* P37 default Alternate function */ \
        PORT->P3   &= ~(1 << 7);    /* P37 output low level */ \
        PORT->PM3  &= ~(1 << 7);    /* P37 is used as EPWMO07 output */ \
        PORT->PMC3 &= ~(1 << 7);    /* P37 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      RTC1HZ                                      ================ */
/* ================================================================================================================== */

/**
  * @brief RTC1HZ Port Setting (Alternative to fixed port)
  */

#define RTC1HZ_PORT_SETTING() do{ \
        PORT->P30CFG = GPIO_FUNC_RTC1HZ;        /* P32 default Alternate function */ \
        PORT->P3   &= ~(1 << 2);    /* P32 output low level */ \
        PORT->PM3  &= ~(1 << 2);    /* P32 is used as RTC1HZ output */ \
        PORT->PMC3 &= ~(1 << 2);    /* P32 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                      CLKBUZ                                      ================ */
/* ================================================================================================================== */

/**
  * @brief CLKBUZ0 Port Setting (CLKBUZ0 alternative to any port, CLKBUZ1 alternative to fixed port)
  */

/* ToDo: You can allocate the CLKBUZ0 to any desired pins with PxxCFG register */
#define CLKBUZ0_PORT_SETTING() do{ \
        PORT->P30CFG = GPIO_FUNC_CLKBUZ0;       /* allocate CLKBUZ0 to P30 */ \
        PORT->P3   &= ~(1 << 0);   /* P30 output low level */ \
        PORT->PM3  &= ~(1 << 0);   /* P30 is used as CLKBUZ0 output */ \
        PORT->PMC3 &= ~(1 << 0);   /* P30 digital function */ \
}while(0)

#define CLKBUZ1_PORT_SETTING() do{ \
        PORT->P31CFG = GPIO_FUNC_CLKBUZ1;        /* P31 default Alternate function */ \
        PORT->P3   &= ~(1 << 1);    /* P31 output low level */ \
        PORT->PM3  &= ~(1 << 1);    /* P31 is used as CLKBUZ1 output */ \
        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        ADC                                       ================ */
/* ================================================================================================================== */

/**
  * @brief ADC Port Setting
  */

/* ToDo: Please comment out the following unused ANIx setting according to your application needs. */
#define ADC_PORT_SETTING() do{ \
        PORT->PMC2 |= (1 << 2);   /* Set ANI2(P22) pin */ \
        /* PORT->PMC2 |= (1 << 3); */   /* P23 = RXD0, 禁止切模拟 */ \
        /* PORT->PMC2 |= (1 << 4); */   /* P24 = TXD0, 禁止切模拟 */ \
        PORT->PMC2 |= (1 << 5);   /* Set ANI5(P25) pin */ \
        PORT->PMC2 |= (1 << 6);   /* Set ANI6(P26) pin */ \
        PORT->PMC0 |= (1 << 1);   /* Set ANI16(P01) pin */ \
        PORT->PMC0 |= (1 << 2);   /* Set ANI17(P02) pin */ \
        PORT->PMC1 |= (1 << 0);   /* Set ANI18(P10) pin */ \
        PORT->PMC1 |= (1 << 1);   /* Set ANI19(P11) pin */ \
        PORT->PMC3 |= (1 << 0);   /* Set ANI7(P30) pin */ \
        PORT->PMC3 |= (1 << 1);   /* Set ANI8(P31) pin */ \
        PORT->PMC3 |= (1 << 2);   /* Set ANI9(P32) pin */ \
        PORT->PMC3 |= (1 << 3);   /* Set ANI10(P33) pin */ \
        PORT->PMC3 |= (1 << 4);   /* Set ANI11(P34) pin */ \
        PORT->PMC3 |= (1 << 5);   /* Set ANI12(P35) pin */ \
}while(0)

/* ================================================================================================================== */
/* ================                                        CMP                                       ================ */
/* ================================================================================================================== */

// /**
//   * @brief CMP Port Setting
//   */

// #define VCOUT0_PORT_SETTING() do { \
//         PORT->PM12  &= ~(1 << 0);  /* VCOUT0 output to P120 */ \
//         PORT->PMC12 &= ~(1 << 0);  /* VCOUT0 output to P120 */ \
// }while(0)

// #define VCOUT1_PORT_SETTING() do { \
//         PORT->PM5   &= ~(1 << 0);  /* VCOUT1 output to P50 */ \
//         PORT->PMC5  &= ~(1 << 0);  /* VCOUT1 output to P50 */ \
// }while(0)

// /* ToDo: Please comment out the VREF0 setting if don't used VREF0 as negative(-) side input of CMP */
// #define CMP0_PORT_SETTING() do{ \
//         PORT->PMC2  |= (1 << 2);  /* Set VCIN0(P22) pin */ \
//         PORT->PMC14 |= (1 << 7);  /* Set VREF0(P147) pin */ \
//         VCOUT0_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT0 signal to port */ \
// }while(0)

// /* ToDo: Please comment out the VCINxx setting if don't used it as positive(+) side input of CMP */
// #define CMP1_PORT_SETTING() do{ \
//         PORT->PMC0  |= (1 << 0);  /* Set VCIN10(P00) pin */ \
//         PORT->PMC0  |= (1 << 1);  /* Set VCIN11(P01) pin */ \
//         PORT->PMC2  |= (1 << 0);  /* Set VCIN12(P20) pin */ \
//         PORT->PMC2  |= (1 << 1);  /* Set VCIN13(P21) pin */ \
//         VCOUT1_PORT_SETTING();    /* ToDo: Please delete me if you don't output VCOUT1 signal to port */ \
// }while(0)

/* ================================================================================================================== */
/* ================                                        PGA                                       ================ */
/* ================================================================================================================== */

// /**
//   * @brief PGA Port Setting
//   */

// #define PGA0O_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 4);   /* PGA0O output to P24 */ \
// }while(0)

// #define PGA1O_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 2);   /* PGA1O output to P22 */ \
// }while(0)

// #define PGA0IN_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 2);  /* PGA0IN input from P22 */ \
// }while(0)

// #define PGA0GND_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 3);  /* PGA0GND input from P23 */ \
// }while(0)

// #define PGA1IN_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 4);  /* PGA1IN input from P24 */ \
// }while(0)

// #define PGA1GND_PORT_SETTING() do { \
//         PORT->PMC2 |= (1 << 5);  /* PGA1GND input from P25 */ \
// }while(0)

/* ================================================================================================================== */
/* ================                                       SCI0/1                                       ================ */
/* ================================================================================================================== */

/**
  * @brief UART0 Port Setting（Alternative to any port) 
  */

/* ToDo: You can allocate the TXD0 to any desired pins with PxxCFG register */
#define TXD0_PORT_SETTING() do{ \
        PORT->P24CFG = GPIO_FUNC_TXD0;        /* allocate TXD0 to P24 */ \
        PORT->P2   |=  (1 << 4);    /* P24 output high level */ \
        PORT->PM2  &= ~(1 << 4);    /* P24 is used as TXD0 output */ \
        PORT->POM2 &= ~(1 << 4);    /* P24 is normal output mode */ \
        PORT->PMC2 &= ~(1 << 4);    /* P24 digital function */ \
}while(0)

/* ToDo: You can allocate the RXD0 to any desired pins with RXD0PCFG register */
#define RXD0_PORT_SETTING() do{ \
        PORT->P23CFG = GPIO_FUNC_RXD0;      /* allocate RXD0 to P23 */ \
        PORT->PM2  |=  (1 << 3);    /* P23 is used as RXD0 input */ \
        PORT->PMC2 &= ~(1 << 3);    /* P23 digital function */ \
}while(0)

/**
  * @brief SPI00 Port Setting（Alternative to any port)
  */

/* ToDo: You can allocate the SS00 to any desired pins with SS00PCFG register */
#define SS00_PORT_SETTING() do{ \
        PORT->P22CFG = 0x00;       /* allocate SS00 to P22 */ \
        PORT->PM2  |=  (1 << 2);     /* P22 is used as SS00 input */ \
        PORT->PU2  |=  (1 << 2);     /* P22 pull up resistor enable */ \
        PORT->PMC2 &= ~(1 << 2);     /* P22 digital function */ \
}while(0)

/* ToDo: You can allocate the SS00 to any desired pins */
#define SS00_PORT_SET() do{ \
        PORT->PSET2 = (1 << 2);      /* P22 output high level */ \
}while(0)

/* ToDo: You can allocate the SS00 to any desired pins */
#define SS00_PORT_CLR() do{ \
        PORT->PCLR2 = (1 << 2);      /* P22 output low level */ \
}while(0)

/* ToDo: You can allocate the SCLKI00 to any desired pins with SCLKI00PCFG register */
#define SCLKI00_PORT_SETTING() do{ \
        PORT->P30CFG = GPIO_FUNC_SCLK00;    /* allocate SCLKI00 to P30 */ \
        PORT->PM3  |=  (1 << 0);     /* P30 is used as SCLK00 input */ \
        PORT->PMC3 &= ~(1 << 0);     /* P30 digital function */ \
}while(0)

/* ToDo: You can allocate the SCLKO00 to any desired pins with PxxCFG register */
#define SCLKO00_PORT_SETTING() do{ \
        PORT->P30CFG = GPIO_FUNC_SCLK00;        /* allocate SCLKO00 to P30 */ \
        PORT->P3   |=  (1 << 0);    /* P30 output high level */ \
        PORT->PM3  &= ~(1 << 0);    /* P30 is used as SCLK00 output */ \
        PORT->POM3 &= ~(1 << 0);    /* P30 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
}while(0)

/* ToDo: You can allocate the SDO00 to any desired pins with PxxCFG register */
#define SDO00_PORT_SETTING() do{ \
        PORT->P31CFG = GPIO_FUNC_SDO00;        /* allocate SDO00 to P31 */ \
        PORT->P3   |=  (1 << 1);    /* P31 output high level */ \
        PORT->PM3  &= ~(1 << 1);    /* P31 is used as SDO00 output */ \
        PORT->POM3 &= ~(1 << 1);    /* P31 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
}while(0)

/* ToDo: You can allocate the SDI00 to any desired pins with SDI00PCFG register */
#define SDI00_PORT_SETTING() do{ \
        PORT->P32CFG = GPIO_FUNC_SDI00;     /* allocate SDI00 to P32 */ \
        PORT->PM3  |=  (1 << 2);    /* P32 is used as SDI00 input */ \
        PORT->PMC3 &= ~(1 << 2);    /* P32 digital function */ \
}while(0)

/**
  * @brief IIC00 Port Setting（Alternative to any port)
  */

/* ToDo: You can allocate the SCL00 to any desired pins with PxxCFG register */
//#define SCL00_PORT_SETTING() do{ \
//        PORT->P30CFG = GPIO_FUNC_SCL00;        /* allocate SCL00 to P30 */ \
//        PORT->P3   |=  (1 << 0);    /* P30 output high level */ \
//        PORT->PM3  &= ~(1 << 0);    /* P30 is used as SCL00 output */ \
//        PORT->POM3 |=  (1 << 0);    /* P30 is N-ch open-drain output mode */ \
//        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
//}while(0)

///* ToDo: You can allocate the SDA00 to any desired pins with SDA00PCFG register */
//#define SDA00_PORT_SETTING() do{ \
//        PORT->P31CFG = GPIO_FUNC_SDA00;     /* allocate SDA00 to P31 */ \
//        PORT->P3   |=  (1 << 1);    /* P31 output high level */ \
//        PORT->PM3  &= ~(1 << 1);    /* P31 is used as SDA00 inout */ \
//        PORT->POM3 |=  (1 << 1);    /* P31 is N-ch open-drain output mode */ \
//        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
//}while(0)

/**
  * @brief SPI01 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_SETTING() do{ \
        PORT->P23CFG = 0x00;         /* P23 default GPIO function */ \
        PORT->P2   |=  (1 << 3);     /* P23 output high level */ \
        PORT->PM2  &= ~(1 << 3);     /* P23 is used as SS01 output */ \
        PORT->PMC2 &= ~(1 << 3);     /* P23 digital function */ \
}while(0)

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_SET() do{ \
        PORT->PSET2 = (1 << 3);      /* P23 output high level */ \
}while(0)

/* ToDo: You can allocate the SS01 to any desired pins */
#define SS01_PORT_CLR() do{ \
        PORT->PCLR2 = (1 << 3);      /* P23 output low level */ \
}while(0)

#define SCLKI01_PORT_SETTING() do{ \
        PORT->P24CFG = GPIO_FUNC_SCLK01;        /* P24 default Alternate function */ \
        PORT->PM2  |=  (1 << 4);    /* P24 is used as SCLK00 input */ \
        PORT->PMC2 &= ~(1 << 4);    /* P24 digital function */ \
}while(0)

#define SCLKO01_PORT_SETTING() do{ \
        PORT->P24CFG = GPIO_FUNC_SCLK01;        /* P24 default Alternate function */ \
        PORT->P2   |=  (1 << 4);    /* P24 output high level */ \
        PORT->PM2  &= ~(1 << 4);    /* P24 is used as SCLK00 output */ \
        PORT->POM2 &= ~(1 << 4);    /* P24 is normal output mode */ \
        PORT->PMC2 &= ~(1 << 4);    /* P24 digital function */ \
}while(0)

#define SDO01_PORT_SETTING() do{ \
        PORT->P25CFG = GPIO_FUNC_SDO01;        /* P25 default Alternate function */ \
        PORT->P2   |=  (1 << 5);    /* P25 output high level */ \
        PORT->PM2  &= ~(1 << 5);    /* P25 is used as SDO01 output */ \
        PORT->POM2 &= ~(1 << 5);    /* P25 is normal output mode */ \
        PORT->PMC2 &= ~(1 << 5);    /* P25 digital function */ \
}while(0)

#define SDI01_PORT_SETTING() do{ \
        PORT->P26CFG = GPIO_FUNC_SDI01;        /* P26 default Alternate function */ \
        PORT->PM2  |=  (1 << 6);    /* P26 is used as SDI01 input */ \
        PORT->PMC2 &= ~(1 << 6);    /* P26 digital function */ \
}while(0)

/**
  * @brief IIC01 Port Setting (Alternative to fixed port)
  */

//#define SCL01_PORT_SETTING() do{ \
//        PORT->P25CFG = GPIO_FUNC_SCL01;        /* P25 default Alternate function */ \
//        PORT->P2   |=  (1 << 5);    /* P25 output high level */ \
//        PORT->PM2  &= ~(1 << 5);    /* P25 is used as SCL01 output */ \
//        PORT->POM2 |=  (1 << 5);    /* P25 is N-ch open-drain output mode */ \
//        PORT->PMC2 &= ~(1 << 5);    /* P25 digital function */ \
//}while(0)

//#define SDA01_PORT_SETTING() do{ \
//        PORT->P24CFG = GPIO_FUNC_SDA01;        /* P24 default Alternate function */ \
//        PORT->P2   |=  (1 << 4);    /* P24 output high level */ \
//        PORT->PM2  &= ~(1 << 4);    /* P24 is used as SDA01 inout */ \
//        PORT->POM2 |=  (1 << 4);    /* P24 is N-ch open-drain output mode */ \
//        PORT->PMC2 &= ~(1 << 4);    /* P24 digital function */ \
//}while(0)

/**
  * @brief UART1 Port Setting (Alternative to any port)
  */

/* ToDo: You can allocate the TXD1 to any desired pins with PxxCFG register */
#define TXD1_PORT_SETTING() do{ \
        PORT->P33CFG = GPIO_FUNC_TXD1;        /* allocate TXD1 to P33 */ \
        PORT->P3   |=  (1 << 3);    /* P33 output high level */ \
        PORT->PM3  &= ~(1 << 3);    /* P33 is used as TXD1 output */ \
        PORT->POM3 &= ~(1 << 3);    /* P33 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 3);    /* P33 digital function */ \
}while(0)

/* ToDo: You can allocate the RXD1 to any desired pins with RXD1PCFG register */
#define RXD1_PORT_SETTING() do{ \
        PORT->P34CFG = GPIO_FUNC_RXD1;      /* allocate RXD1 to P34 */ \
        PORT->PM3  |=  (1 << 4);    /* P34 is used as RXD1 input */ \
        PORT->PMC3 &= ~(1 << 4);    /* P34 digital function */ \
}while(0)

/**
  * @brief SPI10 Port Setting (SCLK10 alternative to fixed port, SDI10/SDO10 alternative to any port)
  */

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_SETTING() do{ \
        PORT->P32CFG = 0x00;         /* P32 default GPIO function */ \
        PORT->P3   |=  (1 << 2);     /* P32 output high level */ \
        PORT->PM3  &= ~(1 << 2);     /* P32 is used as SS10 output */ \
        PORT->PMC3 &= ~(1 << 2);     /* P32 digital function */ \
}while(0)

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_SET() do{ \
        PORT->PSET3 = (1 << 2);      /* P32 output high level */ \
}while(0)

/* ToDo: You can allocate the SS10 to any desired pins */
#define SS10_PORT_CLR() do{ \
        PORT->PCLR3 = (1 << 2);      /* P32 output low level */ \
}while(0)

#define SCLKI10_PORT_SETTING() do{ \
        PORT->P33CFG = GPIO_FUNC_SCLK10;       /* P33 default Alternate function */ \
        PORT->PM3  |=  (1 << 3);   /* P33 is used as SCLK10 input */ \
        PORT->PMC3 &= ~(1 << 3);   /* P33 digital function */ \
}while(0)

#define SCLKO10_PORT_SETTING() do{ \
        PORT->P33CFG = GPIO_FUNC_SCLK10;       /* P33 default Alternate function */ \
        PORT->P3   |=  (1 << 3);   /* P33 output high level */ \
        PORT->PM3  &= ~(1 << 3);   /* P33 is used as SCLK10 output */ \
        PORT->POM3 &= ~(1 << 3);   /* P33 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 3);   /* P33 digital function */ \
}while(0)

/* ToDo: You can allocate the SDO10 to any desired pins with PxxCFG register */
#define SDO10_PORT_SETTING() do{ \
        PORT->P35CFG = GPIO_FUNC_SDO10;        /* allocate SDO10 to P35 */ \
        PORT->P3   |=  (1 << 5);    /* P35 output high level */ \
        PORT->PM3  &= ~(1 << 5);    /* P35 is used as SDO10 output */ \
        PORT->POM3 &= ~(1 << 5);    /* P35 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 5);    /* P35 digital function */ \
}while(0)

/* ToDo: You can allocate the SDI10 to any desired pins with SDI10PCFG register */
#define SDI10_PORT_SETTING() do{ \
        PORT->P34CFG = GPIO_FUNC_SDI10;     /* allocate SDI10 to P34 */ \
        PORT->PM3  |=  (1 << 4);    /* P34 is used as SDI10 input */ \
        PORT->PMC3 &= ~(1 << 4);    /* P34 digital function */ \
}while(0)

/**
  * @brief IIC10 Port Setting (SCL10 alternative to fixed port, SDA10 alternative to any port)
  */

//#define SCL10_PORT_SETTING() do{ \
//        PORT->P33CFG = GPIO_FUNC_SCL10;       /* P33 default Alternate function */ \
//        PORT->P3   |=  (1 << 3);   /* P33 output  */ \
//        PORT->PM3  &= ~(1 << 3);   /* P33 is used as SCL10 output */ \
//        PORT->POM3 |=  (1 << 3);   /* P33 is N-ch open-drain output mode */ \
//        PORT->PMC3 &= ~(1 << 3);   /* P33 digital function */ \
//}while(0)

///* ToDo: You can allocate the SDA10 to any desired pins with SDA10PCFG register */
//#define SDA10_PORT_SETTING() do{ \
//        PORT->P34CFG = GPIO_FUNC_SDA10;     /* allocate SDA10 to P34 */ \
//        PORT->P3   |=  (1 << 4);    /* P34 output high level */ \
//        PORT->PM3  &= ~(1 << 4);    /* P34 is used as SDA10 inout */ \
//        PORT->POM3 |=  (1 << 4);    /* P34 is N-ch open-drain output mode */ \
//        PORT->PMC3 &= ~(1 << 4);    /* P34 digital function */ \
//}while(0)

/**
  * @brief SPI11 Port Setting (Alternative to fixed port)
  */

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_SETTING() do{ \
        PORT->P22CFG = 0x00;         /* P22 default GPIO function */ \
        PORT->P2   |=  (1 << 2);     /* P22 output high level */ \
        PORT->PM2  &= ~(1 << 2);     /* P22 is used as SS11 output */ \
        PORT->PMC2 &= ~(1 << 2);     /* P22 digital function */ \
}while(0)

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_SET() do{ \
        PORT->PSET2 = (1 << 2);      /* P22 output high level */ \
}while(0)

/* ToDo: You can allocate the SS11 to any desired pins */
#define SS11_PORT_CLR() do{ \
        PORT->PCLR2 = (1 << 2);      /* P22 output low level */ \
}while(0)

#define SCLKI11_PORT_SETTING() do{ \
        PORT->P23CFG = GPIO_FUNC_SCLK11;        /* P23 default Alternate function */ \
        PORT->PM2  |=  (1 << 3);    /* P23 is used as SCLK11 input */ \
        PORT->PMC2 &= ~(1 << 3);    /* P23 digital function */ \
}while(0)

#define SCLKO11_PORT_SETTING() do{ \
        PORT->P23CFG = GPIO_FUNC_SCLK11;        /* P23 default Alternate function */ \
        PORT->P2   |=  (1 << 3);    /* P23 output high level */ \
        PORT->PM2  &= ~(1 << 3);    /* P23 is used as SCLK11 output */ \
        PORT->POM2 &= ~(1 << 3);    /* P23 is normal output mode */ \
        PORT->PMC2 &= ~(1 << 3);    /* P23 digital function */ \
}while(0)

#define SDO11_PORT_SETTING() do{ \
        PORT->P24CFG = GPIO_FUNC_SDO11;        /* P24 default Alternate function */ \
        PORT->P2   |=  (1 << 4);    /* P24 output high level */ \
        PORT->PM2  &= ~(1 << 4);    /* P24 is used as SDO11 output */ \
        PORT->POM2 &= ~(1 << 4);    /* P24 is normal output mode */ \
        PORT->PMC2 &= ~(1 << 4);    /* P24 digital function */ \
}while(0)

#define SDI11_PORT_SETTING() do{ \
        PORT->P25CFG = GPIO_FUNC_SDI11;        /* P25 default Alternate function */ \
        PORT->PM2  |=  (1 << 5);    /* P25 is used as SDI11 input */ \
        PORT->PMC2 &= ~(1 << 5);    /* P25 digital function */ \
}while(0)

/**
  * @brief IIC11 Port Setting (Alternative to fixed port)
  */

//#define SCL11_PORT_SETTING() do{ \
//        PORT->P10CFG = GPIO_FUNC_SCL11;        /* P10 default Alternate function */ \
//        PORT->P1   |=  (1 << 0);    /* P10 output high level */ \
//        PORT->PM1  &= ~(1 << 0);    /* P10 is used as SCL11 output */ \
//        PORT->POM1 |=  (1 << 0);    /* P10 is N-ch open-drain output mode */ \
//        PORT->PMC1 &= ~(1 << 0);    /* P10 digital function */ \
//}while(0)

//#define SDA11_PORT_SETTING() do{ \
//        PORT->P11CFG = GPIO_FUNC_SDA11;        /* P11 default Alternate function */ \
//        PORT->P1   |=  (1 << 1);    /* P11 output high level */ \
//        PORT->PM1  &= ~(1 << 1);    /* P11 is used as SDA11 inout */ \
//        PORT->POM1 |=  (1 << 1);    /* P11 is N-ch open-drain output mode */ \
//        PORT->PMC1 &= ~(1 << 1);    /* P11 digital function */ \
//}while(0)

/* ================================================================================================================== */
/* ================                                       SPI                                        ================ */
/* ================================================================================================================== */

/**
  * @brief SPI Port Setting（Alternative to three group port)
  */
#define SPI_MASTER_PORT
//#define SPI_SLAVE_PORT

/* ToDo: Please define one of the following macro and comment out others accroding to your application */
#ifdef SPI_MASTER_PORT
#define NSS_PORT_SETTING() do{ \
        PORT->P3   |=  (1 << 0);    /* P30 output high level */ \
        PORT->PM3  &= ~(1 << 0);    /* P30 is used as NSS output */ \
        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
}while(0)

#define NSS_PORT_SET() do{ \
        PORT->PSET3 =  (1 << 0);    /* P30 output high level */ \
}while(0)

#define NSS_PORT_CLR() do{ \
        PORT->PCLR3 =  (1 << 0);    /* P30 output low level */ \
}while(0)

#define SCK_PORT_SETTING() do{ \
				PORT->P31CFG = GPIO_FUNC_SPI_CLK; \
        PORT->P3   &= ~(1 << 1);    /* P31 output low level */ \
        PORT->PM3  &= ~(1 << 1);    /* P31 is used as SCK output */ \
        PORT->POM3 &= ~(1 << 1);    /* P31 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
}while(0)

#define MOSI_PORT_SETTING() do{ \
				PORT->P32CFG = GPIO_FUNC_SPI_MOSI; \
        PORT->P3   &= ~(1 << 2);    /* P32 output low level */ \
        PORT->PM3  &= ~(1 << 2);    /* P32 is used as MOSI output */ \
        PORT->POM3 &= ~(1 << 2);    /* P32 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 2);    /* P32 digital function */ \
}while(0)

#define MISO_PORT_SETTING() do{ \
				PORT->P33CFG = GPIO_FUNC_SPI_MISO; \
        PORT->PM3  |=  (1 << 3);    /* P33 is used as MISO input */ \
        PORT->PMC3 &= ~(1 << 3);    /* P33 digital function */ \
}while(0)
#endif

#ifdef SPI_SLAVE_PORT
#define NSS_PORT_SETTING() do{ \
				PORT->P30CFG = GPIO_FUNC_SPI_SS; \
        PORT->PM3  |=  (1 << 0);    /* P30 is used as SS00 input */ \
        PORT->PMC3 &= ~(1 << 0);    /* P30 digital function */ \
}while(0)

#define NSS_PORT_SET() do{ \
        __NOP(); \
}while(0)

#define NSS_PORT_CLR() do{ \
        __NOP(); \
}while(0)

#define SCK_PORT_SETTING() do{ \
        PORT->P31CFG = GPIO_FUNC_SPI_CLK;       /* SPI ports group 3 */ \
        PORT->PM3  |=  (1 << 1);    /* P31 is used as SCK input */ \
        PORT->PMC3 &= ~(1 << 1);    /* P31 digital function */ \
}while(0)

#define MOSI_PORT_SETTING() do{ \
				PORT->P32CFG = GPIO_FUNC_SPI_MOSI; \
        PORT->PM3  |=  (1 << 2);    /* P32 is used as MOSI input */ \
        PORT->PMC3 &= ~(1 << 2);    /* P32 digital function */ \
}while(0)

#define MISO_PORT_SETTING() do{ \
				PORT->P33CFG = GPIO_FUNC_SPI_MISO; \
        PORT->P3   &= ~(1 << 3);    /* P33 output low level */ \
        PORT->PM3  &= ~(1 << 3);    /* P33 is used as MISO output */ \
        PORT->POM3 &= ~(1 << 3);    /* P33 is normal output mode */ \
        PORT->PMC3 &= ~(1 << 3);    /* P33 digital function */ \
}while(0)
#endif


/* ================================================================================================================== */
/* ================                                       IICA                                       ================ */
/* ================================================================================================================== */

/**
  * @brief IICA0 Port Setting（Alternative to any port)
  */

/* ToDo: You can allocate the SCLA0 to any desired pins with SCLA0PCFG register */
#define SCLA0_PORT_SETTING() do{ \
        PORT->P10CFG = GPIO_FUNC_SCLA0;     /* allocate SCLA0 to P10 */ \
        PORT->P1   &= ~(1 << 0);    /* P10 output low level */ \
        PORT->PM1  &= ~(1 << 0);    /* P10 is used as SCLA0 output */ \
        PORT->PMC1 &= ~(1 << 0);    /* P10 digital function */ \
}while(0)

/* ToDo: You can allocate the SDAA0 to any desired pins with SDAA0PCFG register */
#define SDAA0_PORT_SETTING() do{ \
        PORT->P11CFG = GPIO_FUNC_SDA0;     /* allocate SDAA0 to P11 */ \
        PORT->P1   &= ~(1 << 1);    /* P11 output low level */ \
        PORT->PM1  &= ~(1 << 1);    /* P11 is used as SDAA0 inout */ \
        PORT->PMC1 &= ~(1 << 1);    /* P11 digital function */ \
}while(0)

/* ================================================================================================================== */
/* ================                                       INTP                                       ================ */
/* ================================================================================================================== */
/**
  * @brief INTP Port Setting 
  */
/* ToDo: You can allocate the INTP0 to any desired pins with INTP0PCFG register */
#define INTP0_PORT_SETTING() do{ \
        PORT->P23CFG = GPIO_FUNC_INTP0;     /* allocate INTP0 to P23 */ \
        PORT->PM2  |=  (1 << 3);   /* P23 is used as INTP0 input */ \
        PORT->PMC2 &= ~(1 << 3);   /* P23 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP1 to any desired pins with INTP1PCFG register */
#define INTP1_PORT_SETTING() do{ \
        PORT->P24CFG = GPIO_FUNC_INTP1;     /* allocate INTP1 to P24 */ \
        PORT->PM2  |=  (1 << 4);    /* P24 is used as INTP1 input */ \
        PORT->PMC2 &= ~(1 << 4);    /* P24 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP2 to any desired pins with INTP2PCFG register */
#define INTP2_PORT_SETTING() do{ \
        PORT->P25CFG = GPIO_FUNC_INTP2;     /* allocate INTP2 to P25 */ \
        PORT->PM2  |=  (1 << 5);    /* P25 is used as INTP2 input */ \
        PORT->PMC2 &= ~(1 << 5);    /* P25 digital function */ \
}while(0)

/* ToDo: You can allocate the INTP3 to any desired pins with INTP3PCFG register */
#define INTP3_PORT_SETTING() do{ \
        PORT->P26CFG = GPIO_FUNC_INTP3;     /* allocate INTP3 to P26 */ \
        PORT->PM2  |=  (1 << 6);    /* P26 is used as INTP3 input */ \
        PORT->PMC2 &= ~(1 << 6);    /* P26 digital function */ \
}while(0)

/** @} */ /* End of group Peripherals_Port_Setting_Definations */

#endif
