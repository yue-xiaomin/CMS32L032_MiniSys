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

#include "FR_math.h"


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

// 工作基数：Q16.16
#define RADIX 16

// 辅助函数：将定点数转换为双精度浮点数（仅用于打印，不参与计算）
static double fixed_to_double(s32 x, int radix) {
    return (double)x / (1 << radix);
}

// 打印定点数（原始值 + 浮点近似）
static void print_fixed(const char* name, s32 value, int radix) {
    printf("%s = %ld (0x%08lX) => %f\r\n", name, (long)value, (unsigned long)value,
           fixed_to_double(value, radix));
}

void fr_math_test(void) {
    printf("========== FR_Math 2.0.8 功能测试 (Radix=%d) ==========\r\n", RADIX);

    // ==================== 1. 定点数创建与转换 ====================
    printf("\r\n[1. 定点数创建与转换]\r\n");
    s32 pi   = FR_NUM(3, 14159, 5, RADIX);      // 3.14159
    s32 half = FR_NUM(0, 5, 1, RADIX);          // 0.5
    s32 neg  = FR_NUM(-2, 75, 2, RADIX);        // -2.75
    s32 two  = I2FR(2, RADIX);                  // 整数 2 转定点
    s32 pi2  = FR_numstr("3.14159", RADIX);     // 字符串解析

    print_fixed("pi (FR_NUM)", pi, RADIX);
    print_fixed("half", half, RADIX);
    print_fixed("neg", neg, RADIX);
    print_fixed("two (I2FR)", two, RADIX);
    print_fixed("pi2 (FR_numstr)", pi2, RADIX);

    // 提取整数部分
    int int_part = FR2I(pi, RADIX);
    printf("FR2I(pi) = %d\r\n", int_part);

    // ==================== 2. 基本算术运算 ====================
    printf("\r\n[2. 基本算术运算]\r\n");
    s32 a = FR_NUM(1, 2, 1, RADIX);   // 1.2
    s32 b = FR_NUM(3, 4, 1, RADIX);   // 3.4
    s32 c = a;                         // 拷贝一份用于 FR_ADD/SUB（宏会修改第一个参数）

    // FR_ADD/FR_SUB 会修改第一个参数，所以先用副本
    s32 sum = c;
    FR_ADD(sum, RADIX, b, RADIX);
    s32 diff = a;
    FR_SUB(diff, RADIX, b, RADIX);
    s32 prod = FR_FixMuls(a, b);       // 乘法（带舍入）
    s32 quot = FR_DIV(a, RADIX, b, RADIX); // 除法（返回新值，不修改参数）

    print_fixed("a = 1.2", a, RADIX);
    print_fixed("b = 3.4", b, RADIX);
    print_fixed("a + b", sum, RADIX);
    print_fixed("a - b", diff, RADIX);
    print_fixed("a * b (FR_FixMuls)", prod, RADIX);
    print_fixed("a / b (FR_DIV)", quot, RADIX);

    // 绝对值
    s32 abs_neg = FR_ABS(neg);
    print_fixed("abs(neg)", abs_neg, RADIX);

    // 饱和加法
    s32 sat_sum = FR_FixAddSat(0x7FFFFFFF, 1);
    printf("FR_FixAddSat(0x7FFFFFFF, 1) = %ld (saturated)\r\n", (long)sat_sum);

    // ==================== 3. 数学函数 ====================
    printf("\r\n[3. 数学函数]\r\n");
    s32 sqrt2 = FR_sqrt(two, RADIX);          // √2
    print_fixed("sqrt(2)", sqrt2, RADIX);

    // atan2(1,1) = π/4 弧度，输出基数 RADIX
    s32 atan2_val = FR_atan2(I2FR(1,RADIX), I2FR(1,RADIX), RADIX);
    print_fixed("atan2(1,1) rad", atan2_val, RADIX);

    // log2(1000)
    s32 log2_1000 = FR_log2(I2FR(1000, RADIX), RADIX, RADIX);
    print_fixed("log2(1000)", log2_1000, RADIX);

    // exp(1) = e
    s32 exp1 = FR_EXP(I2FR(1, RADIX), RADIX);
    print_fixed("exp(1)", exp1, RADIX);

    // 幂运算 2^3 = 8
    s32 pow2_3 = FR_pow2(I2FR(3, RADIX), RADIX);
    print_fixed("pow2(3)", pow2_3, RADIX);

    // ==================== 4. 三角函数（角度制） ====================
    printf("\r\n[4. 三角函数 (角度制)]\r\n");
    s32 deg45 = I2FR(45, RADIX);
    s32 cos45 = fr_cos_deg(deg45, RADIX);
    s32 sin30 = fr_sin_deg(I2FR(30, RADIX), RADIX);
    s32 tan45 = fr_tan_deg(I2FR(45, RADIX), RADIX);

    print_fixed("cos(45°)", cos45, RADIX);
    print_fixed("sin(30°)", sin30, RADIX);
    print_fixed("tan(45°)", tan45, RADIX);

    // 整数角度宏
    s32 cosI45 = FR_CosI(45);
    s32 sinI30 = FR_SinI(30);
    printf("FR_CosI(45) = %ld (0x%08lX) => %f\r\n", (long)cosI45, (unsigned long)cosI45,
           fixed_to_double(cosI45, FR_TRIG_OUT_PREC));
    printf("FR_SinI(30) = %ld (0x%08lX) => %f\r\n", (long)sinI30, (unsigned long)sinI30,
           fixed_to_double(sinI30, FR_TRIG_OUT_PREC));

    // ==================== 5. 三角函数（弧度制） ====================
    printf("\r\n[5. 三角函数 (弧度制)]\r\n");
    // π/4 ≈ 0.785398163
    s32 rad45 = FR_numstr("0.785398", RADIX);
    s32 sin_rad = fr_sin(rad45, RADIX);
    s32 cos_rad = fr_cos(rad45, RADIX);
    s32 tan_rad = fr_tan(rad45, RADIX);

    print_fixed("sin(π/4) rad", sin_rad, RADIX);
    print_fixed("cos(π/4) rad", cos_rad, RADIX);
    print_fixed("tan(π/4) rad", tan_rad, RADIX);

    // ==================== 6. BAM 角度三角函数 ====================
    printf("\r\n[6. BAM 角度三角函数]\r\n");
    u16 bam_90 = FR_BAM_QUADRANT;   // 16384 = 90°
    s32 sin_bam = fr_sin_bam(bam_90);
    s32 cos_bam = fr_cos_bam(0);
    printf("sin_bam(90°) = %ld (0x%08lX) => %f\r\n", (long)sin_bam, (unsigned long)sin_bam,
           fixed_to_double(sin_bam, FR_TRIG_OUT_PREC));
    printf("cos_bam(0°)   = %ld (0x%08lX) => %f\r\n", (long)cos_bam, (unsigned long)cos_bam,
           fixed_to_double(cos_bam, FR_TRIG_OUT_PREC));

    // ==================== 7. 波形发生器 ====================
#ifndef FR_NO_WAVES
    printf("\r\n[7. 波形发生器]\r\n");
    u16 phase = 0;
    s16 tri0 = fr_wave_tri(phase);
    s16 tri16384 = fr_wave_tri(FR_BAM_QUADRANT);
    s16 tri32768 = fr_wave_tri(FR_BAM_HALF);
    printf("triangle wave at 0:    %d\r\n", tri0);
    printf("triangle wave at 90°:  %d\r\n", tri16384);
    printf("triangle wave at 180°: %d\r\n", tri32768);

    // 噪声示例
    u32 noise_state = 123456789;
    s16 noise = fr_wave_noise(&noise_state);
    printf("noise sample: %d\r\n", noise);
#else
    printf("\r\n[7. 波形发生器] 未启用 (FR_NO_WAVES 定义)\r\n");
#endif

    // ==================== 8. 字符串格式化与解析 ====================
#ifndef FR_NO_PRINT
    printf("\r\n[8. 字符串格式化与解析]\r\n");
    // 注意：FR_printNumF 需要提供一个字符输出函数，这里简单用 putchar 包装
    // 为简化，直接调用 FR_numstr 解析和 FR2D 显示
    s32 parsed = FR_numstr("2.71828", RADIX);
    print_fixed("FR_numstr(\"2.71828\")", parsed, RADIX);
#else
    printf("\r\n[8. 字符串处理] 未启用 (FR_NO_PRINT 定义)\r\n");
#endif

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

    fr_math_test();
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
