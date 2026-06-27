#include <stdio.h>
#include "CMS32L032.h"
#include "userdefine.h"
#include "sci.h"
#include "clk.h"
#include "rst.h"
#include "rtc.h"
#include "gpio.h"
#include "led.h"
#include "adc.h"
#include "i2c.h"
#include "delay.h"
#include "dataflash.h"

//#define USE_DATAFLASH_TEST


//64MHz时钟下各波特率在0.2%误差限制内的结果：
//波特率	预分频	SDR	实际波特率	误差	结果
//9600	    /32	103	9616	0.17%	OK
//19200	    /16	103	19231	0.16%	OK
//38400	    /8	103	38462	0.16%	OK
//57600	    /8	68	57971	0.64%	FAIL
//115200	/4	68	115942	0.64%	FAIL
//250000	/1	127	250000	0%	OK
//500000	/1	63	500000	0%	OK
//1000000	/1	31	1000000	0%	OK


#ifdef USE_DATAFLASH_TEST
void DataFlash_Test(void)
{
    uint8_t wbuf[64];
    uint8_t rbuf[64];
    uint16_t i;
    int ret;
    uint8_t pass = 1;

    printf("\r\n--- DataFlash Test Start ---\r\n");

    /* 1. 擦除全部 */
    printf("[1] EraseAll... ");
    ret = DataFlash_EraseAll();
    if (ret != 0) { printf("FAIL(ret=%d)\r\n", ret); return; }
    /* 验证擦除后全为0xFF */
    DataFlash_Read(0, rbuf, 64);
    for (i = 0; i < 64; i++) {
        if (rbuf[i] != 0xFF) { pass = 0; break; }
    }
    printf(pass ? "OK\r\n" : "FAIL(not 0xFF)\r\n");

    /* 2. 写入并回读验证 (扇区0, 偏移0) */
    printf("[2] Write+Read sector0... ");
    for (i = 0; i < 64; i++) wbuf[i] = (uint8_t)i;
    ret = DataFlash_Write(0, wbuf, 64);
    if (ret != 0) { printf("FAIL(write ret=%d)\r\n", ret); return; }
    DataFlash_Read(0, rbuf, 64);
    pass = 1;
    for (i = 0; i < 64; i++) {
        if (rbuf[i] != wbuf[i]) { pass = 0; printf("offset %d: expected 0x%02X got 0x%02X\r\n", i, wbuf[i], rbuf[i]); break; }
    }
    printf(pass ? "OK\r\n" : "FAIL\r\n");

    /* 3. 扇区边界写入 (偏移480, 横跨扇区0和扇区1) */
    printf("[3] Cross-sector write(480~544)... ");
    for (i = 0; i < 64; i++) wbuf[i] = (uint8_t)(0xA0 + i);
    ret = DataFlash_Write(480, wbuf, 64);
    if (ret != 0) { printf("FAIL(write ret=%d)\r\n", ret); return; }
    DataFlash_Read(480, rbuf, 64);
    pass = 1;
    for (i = 0; i < 64; i++) {
        if (rbuf[i] != wbuf[i]) { pass = 0; break; }
    }
    printf(pass ? "OK\r\n" : "FAIL\r\n");

    /* 4. 擦除单个扇区 (扇区1), 验证扇区0不受影响 */
    printf("[4] EraseSector(1), check sector0... ");
    DataFlash_EraseSector(1);
    DataFlash_Read(0, rbuf, 64);
    pass = 1;
    for (i = 0; i < 64; i++) {
        if (rbuf[i] != (uint8_t)i) { pass = 0; break; }
    }
    /* 扇区1应全为0xFF */
    DataFlash_Read(512, rbuf, 16);
    for (i = 0; i < 16; i++) {
        if (rbuf[i] != 0xFF) { pass = 0; break; }
    }
    printf(pass ? "OK\r\n" : "FAIL\r\n");

    /* 5. 覆盖写入 */
    printf("[5] Overwrite... ");
    for (i = 0; i < 32; i++) wbuf[i] = 0xBB;
    DataFlash_Write(0, wbuf, 32);
    DataFlash_Read(0, rbuf, 32);
    pass = 1;
    for (i = 0; i < 32; i++) {
        if (rbuf[i] != 0xBB) { pass = 0; break; }
    }
    /* 偏移32~63应保持原值 */
    DataFlash_Read(32, rbuf, 32);
    for (i = 0; i < 32; i++) {
        if (rbuf[i] != (uint8_t)(32 + i)) { pass = 0; break; }
    }
    printf(pass ? "OK\r\n" : "FAIL\r\n");

    printf("--- DataFlash Test Done ---\r\n\r\n");
}
#endif

int main()
{
	MD_STATUS status;
	uint16_t adc_value;
	uint16_t adc_buf[8];
	int16_t temperature;

	SystemCoreClockUpdate();
	status = UART0_Init(SystemCoreClock, 250000);
	if(status == MD_ERROR)
	{
		while(1);
	}

	printf("Hello, CMS32L032 Demo\r\n");

    RST_Get_Flag();

	delay_init();
	LED_Init();
	ADC_Init();

#ifdef USE_DATAFLASH_TEST
	DataFlash_Test();
#endif

//	/* 初始化I2C (快速模式 400Kbps) */
//	if (I2C_Init(I2C_SPEED_FAST) != I2C_OK) {
//		printf("I2C Init Failed\r\n");
//		while(1);
//	}

//	/* I2C设备扫描 */
//	I2C_Scan();

    while(1)
    {
        adc_value = ADC_Converse(ADC_TEMPERSENSOR0, 8, adc_buf);
        temperature = adc_get_temperature(adc_value);
        printf("ADC Value: %d, Temperature: %d C\r\n", adc_value, temperature);

        LED_Flash(LED_USER, 5, 200);
    }
}
