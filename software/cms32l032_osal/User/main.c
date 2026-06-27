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

#include "osal_main.h"


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




int main()
{
	MD_STATUS status;

	SystemCoreClockUpdate();
	status = UART0_Init(SystemCoreClock, 250000);
	if(status == MD_ERROR)
	{
		while(1);
	}

	printf("Hello, CMS32L032 Demo\r\n");

    RST_Get_Flag();

    osal_main();

    while(1)
    {

    }
}
