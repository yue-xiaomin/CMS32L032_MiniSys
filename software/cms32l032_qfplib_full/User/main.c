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

#include "qfplib-m0-full.h"

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

void qfplib_test(void) {
    printf("========== Qfplib-M0-full 功能测试 ==========\r\n");

    // -------------------- 单精度基本运算 --------------------
    float a = 3.1415926f, b = 2.7182818f;
    printf("\r\n[单精度基本运算]\r\n");
    printf("qfp_fadd(%f, %f) = %f\r\n", a, b, qfp_fadd(a, b));
    printf("qfp_fsub(%f, %f) = %f\r\n", a, b, qfp_fsub(a, b));
    printf("qfp_fmul(%f, %f) = %f\r\n", a, b, qfp_fmul(a, b));
    printf("qfp_fdiv(%f, %f) = %f\r\n", a, b, qfp_fdiv(a, b));
    printf("qfp_fcmp(%f, %f) = %d\r\n", a, b, qfp_fcmp(a, b));
    printf("qfp_fsqrt(%f)     = %f\r\n", 2.0f, qfp_fsqrt(2.0f));

    // -------------------- 单精度三角函数 --------------------
    float angle = 0.785398163f; // π/4 = 45°
    printf("\r\n[单精度三角函数 (弧度)]\r\n");
    printf("qfp_fsin(%f) = %f\r\n", angle, qfp_fsin(angle));
    printf("qfp_fcos(%f) = %f\r\n", angle, qfp_fcos(angle));
    printf("qfp_ftan(%f) = %f\r\n", angle, qfp_ftan(angle));
    printf("qfp_fatan2(%f, %f) = %f\r\n", 1.0f, 1.0f, qfp_fatan2(1.0f, 1.0f));

    // -------------------- 单精度指数对数 --------------------
    printf("\r\n[单精度指数/对数]\r\n");
    printf("qfp_fexp(%f) = %f\r\n", 1.0f, qfp_fexp(1.0f));
    printf("qfp_fln(%f)  = %f\r\n", 2.7182818f, qfp_fln(2.7182818f));

    // -------------------- 单精度 ? 整数/定点转换 --------------------
    float pi = 3.1415926f;
    i32   fixed32;
    ui32  ufixed32;
    printf("\r\n[单精度 → 整数/定点]\r\n");
    printf("qfp_float2int(%f)   = %d\r\n", pi, qfp_float2int(pi));
    printf("qfp_float2fix(%f,16)= %d (Q16.16)\r\n", pi, qfp_float2fix(pi, 16));
    printf("qfp_float2uint(%f)  = %u\r\n", pi, qfp_float2uint(pi));
    printf("qfp_float2ufix(%f,16)= %u (UQ16.16)\r\n", pi, qfp_float2ufix(pi, 16));

    printf("\r\n[整数/定点 → 单精度]\r\n");
    i32  int_val = 3141592;
    ui32 uint_val = 3141592;
    printf("qfp_int2float(%d)   = %f\r\n", int_val, qfp_int2float(int_val));
    fixed32 = qfp_float2fix(pi, 16);
    printf("qfp_fix2float(%d,16)= %f\r\n", fixed32, qfp_fix2float(fixed32, 16));
    printf("qfp_uint2float(%u)  = %f\r\n", uint_val, qfp_uint2float(uint_val));
    ufixed32 = qfp_float2ufix(pi, 16);
    printf("qfp_ufix2float(%u,16)= %f\r\n", ufixed32, qfp_ufix2float(ufixed32, 16));

    // 64 位整数/定点
    i64 big_int = 123456789012345LL;
    ui64 big_uint = 123456789012345ULL;
    printf("\r\n[单精度 ? 64位整数/定点]\r\n");
    printf("qfp_int642float(%lld)  = %f\r\n", big_int, qfp_int642float(big_int));
    printf("qfp_uint642float(%llu) = %f\r\n", big_uint, qfp_uint642float(big_uint));
    i64 fix64 = qfp_float2fix64(pi, 16);
    printf("qfp_float2fix64(%f,16)= %lld\r\n", pi, fix64);
    printf("qfp_fix642float(%lld,16)= %f\r\n", fix64, qfp_fix642float(fix64, 16));

    // 向零取整版本
    printf("\r\n[向零取整测试]\r\n");
    float neg = -3.14f;
    printf("qfp_float2int_z(%f) = %d\r\n", neg, qfp_float2int_z(neg));
    printf("qfp_float2int64_z(%f)= %lld\r\n", neg, qfp_float2int64_z(neg));

    // -------------------- 双精度部分 --------------------
    double da = 3.141592653589793, db = 2.718281828459045;
    printf("\r\n[双精度基本运算]\r\n");
    printf("qfp_dadd(%f, %f) = %f\r\n", da, db, qfp_dadd(da, db));
    printf("qfp_dsub(%f, %f) = %f\r\n", da, db, qfp_dsub(da, db));
    printf("qfp_dmul(%f, %f) = %f\r\n", da, db, qfp_dmul(da, db));
    printf("qfp_ddiv(%f, %f) = %f\r\n", da, db, qfp_ddiv(da, db));
    printf("qfp_dsqrt(%f)     = %f\r\n", 2.0, qfp_dsqrt(2.0));
    printf("qfp_dcmp(%f, %f) = %d\r\n", da, db, qfp_dcmp(da, db));

    double dang = 0.7853981633974483;
    printf("\r\n[双精度三角函数]\r\n");
    printf("qfp_dsin(%f) = %f\r\n", dang, qfp_dsin(dang));
    printf("qfp_dcos(%f) = %f\r\n", dang, qfp_dcos(dang));
    printf("qfp_dtan(%f) = %f\r\n", dang, qfp_dtan(dang));
    printf("qfp_datan2(%f, %f) = %f\r\n", 1.0, 1.0, qfp_datan2(1.0, 1.0));

    printf("\r\n[双精度指数/对数]\r\n");
    printf("qfp_dexp(%f) = %f\r\n", 1.0, qfp_dexp(1.0));
    printf("qfp_dln(%f)  = %f\r\n", 2.718281828459045, qfp_dln(2.718281828459045));

    printf("\r\n[双精度 ? 整数/定点]\r\n");
    printf("qfp_double2int(%f)   = %d\r\n", da, qfp_double2int(da));
    printf("qfp_double2fix(%f,16)= %d\r\n", da, qfp_double2fix(da, 16));
    printf("qfp_double2uint(%f)  = %u\r\n", da, qfp_double2uint(da));
    printf("qfp_int2double(%d)   = %f\r\n", 3141592, qfp_int2double(3141592));
    printf("qfp_double2float(%f) = %f\r\n", da, qfp_double2float(da));
    printf("qfp_float2double(%f) = %f\r\n", pi, qfp_float2double(pi));

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



//	/* 初始化I2C (快速模式 400Kbps) */
//	if (I2C_Init(I2C_SPEED_FAST) != I2C_OK) {
//		printf("I2C Init Failed\r\n");
//		while(1);
//	}

//	/* I2C设备扫描 */
//	I2C_Scan();

    qfplib_test();
    
    while(1)
    {


        LED_Flash(LED_USER, 5, 200);
    }
}
