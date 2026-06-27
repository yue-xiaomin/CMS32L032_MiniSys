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

#include "qfplib-m0-tiny.h"
#include "qfpio.h"


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

void qfplib_tiny_test(void) {
    printf("========== Qfplib-M0-tiny 功能测试 ==========\r\n");

    // -------------------- 基本算术运算 --------------------
    float a = 3.1415926f, b = 2.7182818f;
    printf("\r\n[基本算术运算]\r\n");
    printf("qfp_fadd(%f, %f) = %f\r\n", a, b, qfp_fadd(a, b));
    printf("qfp_fsub(%f, %f) = %f\r\n", a, b, qfp_fsub(a, b));
    printf("qfp_fmul(%f, %f) = %f\r\n", a, b, qfp_fmul(a, b));
    printf("qfp_fdiv(%f, %f) = %f\r\n", a, b, qfp_fdiv(a, b));
    printf("qfp_fdiv_fast(%f, %f) = %f\r\n", a, b, qfp_fdiv_fast(a, b));
    printf("qfp_fsqrt(%f)     = %f\r\n", 2.0f, qfp_fsqrt(2.0f));
    printf("qfp_fsqrt_fast(%f)= %f\r\n", 2.0f, qfp_fsqrt_fast(2.0f));
    printf("qfp_fcmp(%f, %f) = %d\r\n", a, b, qfp_fcmp(a, b));

    // -------------------- 三角函数 --------------------
    float angle = 0.785398163f;   // π/4 = 45°
    printf("\r\n[三角函数 (弧度)]\r\n");
    printf("qfp_fsin(%f) = %f\r\n", angle, qfp_fsin(angle));
    printf("qfp_fcos(%f) = %f\r\n", angle, qfp_fcos(angle));
    printf("qfp_ftan(%f) = %f\r\n", angle, qfp_ftan(angle));
    printf("qfp_fatan2(%f, %f) = %f\r\n", 1.0f, 1.0f, qfp_fatan2(1.0f, 1.0f));

    // -------------------- 指数与对数 --------------------
    printf("\r\n[指数/对数]\r\n");
    printf("qfp_fexp(%f) = %f\r\n", 1.0f, qfp_fexp(1.0f));
    printf("qfp_fln(%f)  = %f\r\n", 2.7182818f, qfp_fln(2.7182818f));

    // -------------------- 浮点 ? 整数/定点转换 --------------------
    float pi = 3.1415926f;
    int   fix32;
    unsigned int ufix32;
    printf("\r\n[浮点 → 整数/定点]\r\n");
    printf("qfp_float2int(%f)    = %d\r\n", pi, qfp_float2int(pi));
    printf("qfp_float2fix(%f,16) = %d (Q16.16)\r\n", pi, qfp_float2fix(pi, 16));
    printf("qfp_float2uint(%f)   = %u\r\n", pi, qfp_float2uint(pi));
    printf("qfp_float2ufix(%f,16)= %u (UQ16.16)\r\n", pi, qfp_float2ufix(pi, 16));

    printf("\r\n[整数/定点 → 浮点]\r\n");
    int   ival = 3141592;
    unsigned int uval = 3141592;
    printf("qfp_int2float(%d)    = %f\r\n", ival, qfp_int2float(ival));
    fix32 = qfp_float2fix(pi, 16);
    printf("qfp_fix2float(%d,16) = %f\r\n", fix32, qfp_fix2float(fix32, 16));
    printf("qfp_uint2float(%u)   = %f\r\n", uval, qfp_uint2float(uval));
    ufix32 = qfp_float2ufix(pi, 16);
    printf("qfp_ufix2float(%u,16)= %f\r\n", ufix32, qfp_ufix2float(ufix32, 16));

    // -------------------- 字符串转换 --------------------
//    printf("\r\n[字符串转换]\r\n");
//    char buf[32];
//    float test_val = 123.456789f;
//    qfp_float2str(test_val, buf, 0);       // fmt=0 自动格式
//    printf("qfp_float2str(%f, fmt=0) = \"%s\"\r\n", test_val, buf);
//    qfp_float2str(test_val, buf, 3);       // 保留3位小数
//    printf("qfp_float2str(%f, fmt=3) = \"%s\"\r\n", test_val, buf);

//    char input[] = "3.14159";
//    float result;
//    char *endptr;
//    int ret = qfp_str2float(&result, input, &endptr);
//    printf("qfp_str2float(\"%s\") -> result=%f, ret=%d, endptr=\"%s\"\r\n",
//           input, result, ret, endptr);

//    // 测试带错误的情况
//    char bad_input[] = "12.34abc";
//    ret = qfp_str2float(&result, bad_input, &endptr);
//    printf("qfp_str2float(\"%s\") -> result=%f, ret=%d, endptr=\"%s\"\r\n",
//           bad_input, result, ret, endptr);

    printf("\r\n========== 测试结束 ==========\r\n");
}

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

	delay_init();
	LED_Init();


    qfplib_tiny_test();
//	/* 初始化I2C (快速模式 400Kbps) */
//	if (I2C_Init(I2C_SPEED_FAST) != I2C_OK) {
//		printf("I2C Init Failed\r\n");
//		while(1);
//	}

//	/* I2C设备扫描 */
//	I2C_Scan();

    while(1)
    {


        LED_Flash(LED_USER, 5, 200);
    }
}
