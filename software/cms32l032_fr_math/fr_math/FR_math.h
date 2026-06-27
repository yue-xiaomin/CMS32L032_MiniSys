/**
 *	@FR_math.h - 固定基数数学例程的头文件定义
 *
 *	@copy 版权所有 (C) <2001-2026>  <M. A. Chatterjee>
 *  @author M A Chatterjee <deftio [at] deftio [dot] com>
 *
 *  本文件包含整数数学可设置固定小数点基数（radix）的例程，
 *  适用于不需要或不方便使用浮点数的系统。
 *
 *  @license:
 *	本软件按“原样”提供，不附有任何明示或暗示的担保。
 *	在任何情况下，作者均不对因使用本软件而产生的任何损害承担责任。
 *
 *	允许任何人将该软件用于任何目的，包括商业应用，并自由地修改和重新分发，
 *	但须遵守以下限制：
 *
 *	1. 不得歪曲本软件的来源；不得声称您编写了原始软件。
 *	   如果您在产品中使用本软件，文档中应提及原作者，但不是必须。
 *
 *	2. 修改后的源代码版本必须明确标记为修改版本，
 *	   不得歪曲为原始软件。
 *
 *	3. 不得删除或修改本版权声明。
 *
 */

#ifndef __FR_Math_h__
#define __FR_Math_h__

#define FR_MATH_VERSION     "2.0.8"
#define FR_MATH_VERSION_HEX  0x020008  /* 主版本号 << 16 | 次版本号 << 8 | 补丁号 */

#ifdef FR_CORE_ONLY
#define FR_NO_PRINT
#define FR_NO_WAVES
#endif

#ifdef FR_LEAN
#define FR_NO_WAVES
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __FR_Platform_Defs_H__
#include "FR_defs.h"
#endif

/* 关于宏参数括号的简要说明：
 * 宏在展开时对参数进行文本替换。例如：
 *   #define MACRO_X_SQUARED(x)  ((x)*(x))   // 每个 x 都有内层括号
 * 如果参数是像 3+4*5 这样的表达式，而宏体中没有额外的括号，可能会产生运算符优先级错误。
 * 因此，在宏体中将参数（以及容易出错的子表达式）用括号括起来。
 * 示例：MACRO_X_SQUARED_BAD(x)  (x*x)  ->  3+4*5*3+4*5  == 83 (错误)
 *       MACRO_X_SQUARED(x)  ((x)*(x))  ->  (3+4*5)*(3+4*5)  == 529 (正确)
 */

/* 整数和固定基数的绝对值 */
#define FR_ABS(x) (((x) < 0) ? (-(x)) : (x))

/* x 的符号位。不如“符号四重奏”优雅，但也可用 */
#define FR_SGN(x) ((x) >> ((((signed)sizeof(x)) << 3) - 1))

/*===============================================
 * 简单的定点数转换
 * r 是基数的精度（二进制位数），与整数互转（截断） */
#define I2FR(x, r) ((x) << (r))
#define FR2I(x, r) ((x) >> (r))

/*===============================================
 * 从整数 + 十进制小数部分构造一个固定基数数。
 * r  = 输出基数（小数位数）
 * i  = 整数部分（有符号）
 * f  = 小数部分的十进制数字，例如 "12.34" 时传入 f=34
 * d  = f 的十进制数字位数，例如 "12.34" 时传入 d=2
 *
 * FR_NUM(12, 34, 2, 10)  ≈ 12.34 in s.10  = (12<<10) + (34<<10)/100 = 12636
 * FR_NUM(-3, 5,  1, 16)  ≈ -3.5  in s.16  = (-3<<16) - (5<<16)/10
 *
 * 小数部分向零舍入。如需四舍五入，可在调用前加半个最低有效位（LSB）。
 * 小数部分的符号与 i 相同（当 i==0 时结果为正，符合 "+0.5" 的直观）。
 */
#define FR_NUM_POW10(d) (                                              \
    ((d) == 0) ? 1L :                                                  \
    ((d) == 1) ? 10L :                                                 \
    ((d) == 2) ? 100L :                                                \
    ((d) == 3) ? 1000L :                                               \
    ((d) == 4) ? 10000L :                                              \
    ((d) == 5) ? 100000L :                                             \
    ((d) == 6) ? 1000000L :                                            \
    ((d) == 7) ? 10000000L :                                           \
    ((d) == 8) ? 100000000L : 1000000000L)
#define FR_NUM(i, f, d, r) (                                           \
    ((s32)(i) << (r)) +                                                \
    (((i) < 0)                                                         \
        ? -((s32)(((s32)(f) << (r)) / FR_NUM_POW10(d)))                \
        :  ((s32)(((s32)(f) << (r)) / FR_NUM_POW10(d)))))

/*
FR_INT(x, r) 将基数 r 的固定点数 x 转换为整数
*/
#define FR_INT(x, r) (((x) < 0) ? -((-(x)) >> (r)) : ((x) >> (r)))

/* 改变基数 (x, 当前基数, 新基数)
 * 将数字从当前基数（可以是 0 或整数）转换到新基数
 * 当处理混合基数的数字时很有用。这是一个宏，原地修改 x。
 */
#define FR_CHRDX(x, r_cur, r_new) (((r_cur) - (r_new)) >= 0 ? ((x) >> ((r_cur) - (r_new))) : ((x) << ((r_new) - (r_cur))))

/* 仅返回 x 的小数部分 */
#define FR_FRAC(x, r) ((FR_ABS(x)) & (((1 << (r)) - 1)))

/* 返回 x 的小数部分，并缩放基数 */
#define FR_FRACS(x, xr, nr) (FR_CHRDX(FR_FRAC((x), (xr)), (xr), (nr)))

/******************************************************
  定点数加减：将第二个数转换到第一个数的基数后相加/减。
  如果 yr < xr，溢出风险增加。
  注意：对于两个变量 i (基数 ir) 和 j (基数 jr)，
       FR_ADD(i,ir,j,jr) == FR_ADD(j,jr,i,ir) 不一定成立。
*/
#define FR_ADD(x, xr, y, yr) ((x) += FR_CHRDX(y, yr, xr))
#define FR_SUB(x, xr, y, yr) ((x) -= FR_CHRDX(y, yr, xr))

/* 定点数除法（四舍五入到最近整数）：
 * 返回 (x 基数 xr) / (y 基数 yr) 的结果，结果基数为 xr。
 * 使用 64 位中间值，确保 Q16.16 范围正确。
 * 截断前加入一半除数，使误差 ≤ 0.5 LSB。 */
static inline s32 FR_div_rnd(s64 num, s32 den) {
    if ((num ^ den) >= 0)                   /* 同号：商为正 */
        return (s32)((num + den / 2) / den);
    else                                     /* 异号：商为负 */
        return (s32)((num - den / 2) / den);
}
#define FR_DIV(x, xr, y, yr) FR_div_rnd((s64)(x) << (yr), (s32)(y))

/* FR_DIV_TRUNC: 截断除法（旧 FR_DIV 的行为）。
 * 当调用者知道商是精确的或可接受截断时使用。 */
#define FR_DIV_TRUNC(x, xr, y, yr) ((s32)(((s64)(x) << (yr)) / (s32)(y)))

/* FR_DIV32: 仅 32 位的除法。要求 |x| < 2^(31-yr) 以避免中间结果 (x << yr) 溢出。
 * 建议使用 FR_DIV 进行全范围除法。 */
#define FR_DIV32(x, xr, y, yr) (((s32)(x) << (yr)) / (s32)(y))

/* 取余：两个操作数应具有相同的基数 */
#define FR_MOD(x, y) ((x) % (y))

/* 最小值、最大值、钳位 */
#define FR_MIN(a, b)         (((a) < (b)) ? (a) : (b))
#define FR_MAX(a, b)         (((a) > (b)) ? (a) : (b))
#define FR_CLAMP(x, lo, hi)  (FR_MIN(FR_MAX((x), (lo)), (hi)))

/* 检查 x 是否为 2 的幂 */
#define FR_ISPOW2(x) (!((x) & ((x) - 1)))

/* 在当前基数下的 floor 和 ceil（保持基数不变）
 * 即低位 bits 清为 0
 */
#define FR_FLOOR(x, r) ((x) & (~((1 << r) - 1)))
#define FR_CEIL(x, r) (FR_FLOOR(x, r) + ((FR_FRAC(x, r) ? (1 << r) : 0)))

/*******************************************************
  在两个定点值之间插值，支持任意基数。
  delta 为分数，精度 prec 为 delta 的二进制小数位数。
  如果 delta 不在 [0,1] 范围内，则进行外推，但要注意可能的溢出。
  x0, x1 和 delta 的基数可以不同。
*/
#define FR_INTERP(x0, x1, delta, prec) ((x0) + ((((x1) - (x0)) * (delta)) >> (prec)))

/******************************************************
  FR_INTERPI 与 FR_INTERP 类似，但确保 delta 在 [0,1) 范围内（即 0 到 (1<<prec)-1）。
  注意：delta 应为非负。
*/
#define FR_INTERPI(x0, x1, delta, prec) ((x0) + ((((x1) - (x0)) * ((delta) & ((1 << (prec)) - 1))) >> (prec)))

/******************************************************
  转换为 double，仅供调试。在许多嵌入式系统上无法编译。
  这是一个宏，除非实际在代码中调用，否则不会编译。
*/
#define FR2D(x, r) ((double)(((double)(x)) / ((double)(1 << (r)))))
#define D2FR(d, r) ((s32)(d * (1 << r)))

/******************************************************
  有用的常数

  FR_kXXXX   — “k” 表示常量，方便阅读宏时使用
  FR_krXXX   — “r” 表示倒数，例如 1/XXX
  这些常量在代码空间中仅在真正使用时才占用空间。
  这里通过将自然十进制值乘以 (1<<FR_kPREC) 计算得到。
 */
#define FR_kPREC (16)         /* 下面常量的精度（二进制位数） */
#define FR_kE (178145)        /* 2.718281828459 */
#define FR_krE (24109)        /* 0.367879441171 */
#define FR_kPI (205887)       /* 3.141592653589 */
#define FR_krPI (20861)       /* 0.318309886183 */
#define FR_kDEG2RAD (1144)    /* 0.017453292519 */
#define FR_kRAD2DEG (3754936) /* 57.295779513082 */

#define FR_kQ2RAD (102944) /* 1.570796326794 */
#define FR_kRAD2Q (41722)  /* 0.636619772367 */

/* log2 到 ln 的转换（参见宏） */
#define FR_kLOG2E (94548)  /* 1.442695040890 */
#define FR_krLOG2E (45426) /* 0.693147180560 */

/* log2 到 log10 的转换（参见宏） */
#define FR_kLOG2_10 (217706) /* 3.32192809489 */
#define FR_krLOG2_10 (19728) /* 0.30102999566 */

/* 高精度缩放常数，基数为 28。
 * 用于 FR_EXP、FR_ln、FR_log10 的基数转换。
 * 基数 28 提供了约 9 位十进制精度，远超 Q16.16 的约 4.8 位。
 */
#define FR_kLOG2E_28    (387270501)   /* log2(e)   = 1.4426950408889634  */
#define FR_krLOG2E_28   (186065279)   /* ln(2)     = 0.6931471805599453  */
#define FR_kLOG2_10_28  (891723283)   /* log2(10)  = 3.3219280948873622  */
#define FR_krLOG2_10_28  (80807124)   /* log10(2)  = 0.3010299956639812  */

/* 将定点值 x（任意基数）乘以基数 28 的常数 k。
 * 结果保持 x 的基数。使用 64 位中间值。
 * 四舍五入到最近（移位前加 0.5 LSB）。
 */
#define FR_MULK28(x, k) ((s32)((((int64_t)(x) * (int64_t)(k)) + (1 << 27)) >> 28))

// 常见平方根
#define FR_kSQRT2 (92682)   /* 1.414213562373 */
#define FR_krSQRT2 (46341)  /* 0.707106781186 */
#define FR_kSQRT3 (113512)  /* 1.732050807568 */
#define FR_krSQRT3 (37837)  /* 0.577350269189 */
#define FR_kSQRT5 (146543)  /* 2.236067977599 */
#define FR_krSQRT5 (29309)  /* 0.447213595499 */
#define FR_kSQRT10 (207243) /* 3.162277660168 */
#define FR_krSQRT10 (20724) /* 0.316227766016 */

  /*===============================================
   * 算术运算
   */
  s32 FR_FixMuls(s32 x, s32 y);   // 有符号乘法，四舍五入，不饱和
  s32 FR_FixMulSat(s32 x, s32 y); // 有符号乘法，四舍五入，饱和
  s32 FR_FixAddSat(s32 x, s32 y); // 有符号加法，饱和

/*================================================
 * 三角函数表相关常数定义
 *
 * FR_TRIG_PREC     — 内部表精度（u0.15，正弦表）
 * FR_TRIG_OUT_PREC — sin/cos/tan 的输出精度（自 v2.0.1 起为 s15.16）
 * FR_TRIG_ONE      — 输出格式下精确的 1.0（1 << 16 = 65536）
 *
 * sin/cos 返回基数 16 的 s32（s15.16）。这与 libfixmath Q16.16 精度匹配，
 * 并允许在极点处精确表示 1.0。
 * tan 返回基数 16 的 s32（s15.16），在 ±FR_TRIG_MAXVAL 处饱和。
 */
#define FR_TRIG_PREC     (15)
#define FR_TRIG_OUT_PREC (16)
#define FR_TRIG_MASK     ((1 << (FR_TRIG_PREC)) - 1)
#define FR_TRIG_ONE      (1L << FR_TRIG_OUT_PREC)         /* 65536 = 1.0 */
#define FR_TRIG_MAXVAL   ((s32)0x7fffffff)                 /* tan 饱和最大值 */
#define FR_TRIG_MINVAL   (-FR_TRIG_MAXVAL)                 /* tan 饱和最小值 */

/* 仅使用移位缩放的宏。适用于乘法性能较差的平台。
 * 当需要缩放一个使用了大量位的数字且没有更大寄存器的时也很有用。
 * 例如，假设你需要将一个大 32 位数 z=0xa4239323 从度转为弧度。
 * 理想情况下应乘以 0.017453，但直接乘法容易溢出。
 * 下面的宏 FR_RAD2DEG 不需要累加器富裕位，因此没有精度损失的风险。
 * 另一个好处是某些低端微控制器（8051, 68xx, MSP430 low end, PIC-8 系列）没有乘法器。
 * 因此，程序员可以通过这些宏比较用移位还是缩放乘法来获得更好的性能或精度。
 * 效果因架构、编译器等因素而异。
 */

/* 乘以 10 的缩放 */
#define FR_SMUL10(x) (((x) << 3) + (((x) << 1)))
#define FR_SDIV10(x) (((x) >> 3) - ((x) >> 5) + ((x) >> 7) - ((x) >> 9) + ((x) >> 11))

/* 乘以 1/log2(e) ≈ 0.693147180560，用于将 log2() 转换为 ln() */
#define FR_SrLOG2E(x) (((x) >> 1) + ((x) >> 2) - ((x) >> 3) + ((x) >> 4) + ((x) >> 7) - ((x) >> 9) - ((x) >> 12) + ((x) >> 15))

/* 乘以 log2(e) ≈ 1.442695040889，用于将 pow2() 转换为 exp() */
#define FR_SLOG2E(x) ((x) + ((x) >> 1) - ((x) >> 4) + ((x) >> 8) + ((x) >> 10) + ((x) >> 12) + ((x) >> 14))

/* 乘以 1/log2(10) ≈ 0.30102999566，用于将 log2() 转换为 log10 */
#define FR_SrLOG2_10(x) (((x) >> 2) + ((x) >> 4) - ((x) >> 6) + ((x) >> 7) - ((x) >> 8) + ((x) >> 12))

/* 乘以 log2(10) ≈ 3.32192809489，用于将 pow2() 转换为 pow10 */
#define FR_SLOG2_10(x) (((x) << 1) + (x) + ((x) >> 2) + ((x) >> 4) + ((x) >> 7) + ((x) >> 10) + ((x) >> 11) + ((x) >> 13))

/* 仅用移位的角度转换宏
 *
 * 全部以移位形式表示的常量乘法器 — 无乘法、无除法、无 64 位中间值、无累加器。
 * 适用于任何基数：如果输入是以基数 8 表示的度，输出就是以基数 8 表示的所需单位。
 * 调用者根据需要移位。
 *
 * 角度单位：
 *   度（degrees）   = 每圈 360
 *   弧度（radians） = 每圈 2*pi
 *   BAM            = 每圈 65536（二进制角度度量，u16）
 *   象限           = 每圈 4（= BAM >> 14）
 *
 * 副作用注意：x 在宏中可能被多次引用 — 不要传递带有副作用的表达式。
 */

/* FR_DEG2RAD(x): 乘以 pi/180 ≈ 0.017453（5 项，~17 位精度） */
#define FR_DEG2RAD(x) (((x) >> 6) + ((x) >> 9) - ((x) >> 13) - ((x) >> 19) - ((x) >> 20))

/* FR_RAD2DEG(x): 乘以 180/pi ≈ 57.29578（7 项，~19 位精度） */
#define FR_RAD2DEG(x) (((x) << 6) - ((x) << 3) + (x) + ((x) >> 2) + (((x) >> 4) - ((x) >> 6)) - ((x) >> 10))

/* FR_DEG2BAM(x): 乘以 65536/360 ≈ 182.0449（7 项，~18 位精度）。
 * 当 |x| > ~256 度（s15.16 下）时，中间项 (x<<7) 会溢出 s32，
 * 但结果截断为 u16 BAM 时溢出是安全的（二进制补码回绕保持取模正确性）。
 * 如需全精度 s32 BAM（用于亚 BAM 插值），请使用 fr_deg_to_bam()。 */
#define FR_DEG2BAM(x) (((x)<<7)+((x)<<6)-((x)<<3)-((x)<<1)+((x)>>5)+((x)>>6)-((x)>>9))

/* FR_BAM2DEG(x): 乘以 360/65536 = 0.00549316（4 项，精确） */
#define FR_BAM2DEG(x) (((x)>>8)+((x)>>9)-((x)>>12)-((x)>>13))

/* FR_RAD2BAM(x): 乘以 65536/(2*pi) ≈ 10430.378（7 项，~21 位精度）。
 * 警告：当 |x| > ~4 rad（s15.16 下）时，x<<13 项会溢出 s32。
 * 如需安全的任意基数转换，请使用 fr_rad_to_bam() 函数。
 * #define FR_RAD2BAM(x) (((x)<<13)+((x)<<11)+((x)<<7)+((x)<<6)-((x)<<1)+((x)>>1)-((x)>>3)) */
#define FR_RAD2BAM(x) (((x)<<13)+((x)<<11)+((x)<<7)+((x)<<6)-((x)<<1)+((x)>>1)-((x)>>3)+((x)>>8)-((x)>>11)-((x)>>14))
/* ── 防溢出的弧度/度到 BAM 转换函数 ─────────────
 *
 * 这些函数替代 FR_RAD2BAM / FR_DEG2BAM 宏，适用于需要在任意基数下处理全范围 ±2*pi 或 ±360° 的调用者。
 *
 * 策略：将输入归一化到基数 16，有条件地缩放到安全区域，
 *       应用全精度仅移位乘法，然后提取 u16 BAM。没有因减半/四分而损失精度。
 *
 * fr_rad_to_bam: 归一到 [-pi, pi]，重排序项，支持 ±2*pi。
 * fr_deg_to_bam: 归一到 [-90, 90) + 象限偏移，支持 ±360°。
 */

/* 任意基数的圆周率常数：FR_PI(r) = round(pi * 2^r)，等等。
 * 当 r 是编译时常量时，编译器会在编译时计算。
 * 最大安全基数：FR_PI r<=29, FR_TWO_PI r<=28, FR_HALF_PI r<=30。 */
#define FR_PI(r)             ((s32)(3.14159265358979323846  * (1LL << (r)) + 0.5))
#define FR_TWO_PI(r)         ((s32)(6.28318530717958647692  * (1LL << (r)) + 0.5))
#define FR_HALF_PI(r)        ((s32)(1.57079632679489661923  * (1LL << (r)) + 0.5))
#define FR_THREE_HALF_PI(r)  ((s32)(4.71238898038468985769  * (1LL << (r)) + 0.5))

/* 基数 16 下的便捷别名 */
#define FR_PI_R16       FR_PI(16)
#define FR_TWO_PI_R16   FR_TWO_PI(16)

/* 基数 16 下的角度常数（精确 — 无截断） */
#define FR_D90_R16      ((s32)90  << 16)
#define FR_D180_R16     ((s32)180 << 16)
#define FR_D360_R16     ((s32)360 << 16)

  u16 fr_rad_to_bam(s32 rad, u16 radix);
#ifndef FR_LEAN
  u16 fr_deg_to_bam(s32 deg, u16 radix);
#endif

/* FR_BAM2RAD(x): 乘以 2*pi/65536 ≈ 0.0000959（5 项，~18 位精度） */
#define FR_BAM2RAD(x) (((x)>>13)-((x)>>15)+((x)>>18)+((x)>>21)+((x)>>25))

/* 遗留象限宏（象限 = BAM >> 14） */
#define FR_RAD2Q(x) (((x) >> 1) + ((x) >> 3) + ((x) >> 7) + ((x) >> 8) - ((x) >> 14))
#define FR_Q2RAD(x) ((x) + ((x) >> 1) + ((x) >> 4) + ((x) >> 7) + ((x) >> 11))
#define FR_DEG2Q(x) (((x) >> 6) - ((x) >> 8) - ((x) >> 11) - ((x) >> 13))
#define FR_Q2DEG(x) (((x) << 6) + ((x) << 4) + ((x) << 3) + ((x) << 1))

/*===============================================
 * BAM（二进制角度度量）— 内部角度表示
 *
 * 一圈 = 2^16 BAM 单位。因此：
 *   0       = 0 度     = 0 rad
 *   16384   = 90 度    = pi/2 rad   (FR_BAM_QUADRANT)
 *   32768   = 180 度   = pi rad
 *   49152   = 270 度   = 3pi/2 rad
 *   65536   = 0 （自动回绕，因为 BAM 是 u16）
 *
 * BAM 是定点三角函数天然适合的表示，因为：
 *   - 高 2 位直接选择象限（无需 % 360 取模）。
 *   - 次高 7 位直接索引 128 项的象限表。
 *   - 低 7 位提供线性插值精度。
 */
#define FR_BAM_BITS         (16)
#define FR_BAM_FULL         (1L << FR_BAM_BITS)         /* 65536 */
#define FR_BAM_QUADRANT     (FR_BAM_FULL >> 2)          /* 16384 */
#define FR_BAM_HALF         (FR_BAM_FULL >> 1)          /* 32768 */

/*===============================================
 * 基于弧度或 BAM 的三角函数（推荐）
 *
 * 所有 sin/cos 函数返回 s32，基数 16（s15.16）。
 * 1.0 精确表示为 FR_TRIG_ONE（65536）。
 * 极点（0, 90, 180, 270 度）产生精确的 ±FR_TRIG_ONE 或 0。
 *
 *   fr_cos_bam(bam)         — BAM 角度的余弦，返回 s15.16
 *   fr_sin_bam(bam)         — BAM 角度的正弦，返回 s15.16
 *   fr_cos(rad, radix)      — 给定基数的弧度的余弦，返回 s15.16
 *   fr_sin(rad, radix)      — 给定基数的弧度的正弦，返回 s15.16
 *   fr_tan(rad, radix)      — 给定基数的弧度的正切，返回 s15.16
 *   fr_cos_deg(deg, radix)  — 给定基数的度数的余弦，返回 s15.16
 *   fr_sin_deg(deg, radix)  — 给定基数的度数的正弦，返回 s15.16
 *   fr_tan_deg(deg, radix)  — 给定基数的度数的正切，返回 s15.16
 *
 * 所有这些都通过 129 项象限表和线性插值实现。
 * 最坏误差：s15.16 下约 2 LSB（绝对误差 ~3e-5），四个特殊角度除外（精确）。
 *
 * 弧度和度数的包装函数（fr_sin, fr_cos, fr_tan 等）先进行范围归约，
 * 转换为 u16 BAM，然后调用 BAM 原生函数。在零点交叉处（sin≈0, cos≈0, tan≈0）
 * 使用小角度近似 sin(δ)≈δ 以避免 BAM 量化误差。
 */
  s32 fr_cos_bam(u16 bam);
  s32 fr_sin_bam(u16 bam);
#ifndef FR_LEAN
  s32 fr_tan_bam(u16 bam);
#endif
  s32 fr_cos(s32 rad, u16 radix);
  s32 fr_sin(s32 rad, u16 radix);
  s32 fr_tan(s32 rad, u16 radix);

/* 整数度数 -> BAM，使用除法（所有 45 度的倍数时精确） */
#define FR_DEG2BAM_I(deg) ((u16)((((s32)(deg) << 16) + ((deg) >= 0 ? 180 : -180)) / 360))

/* 遗留单参数整数度宏 — 改用 FR_CosI / FR_SinI */
/* #define fr_cos_deg(deg)  fr_cos_bam(FR_DEG2BAM_I(deg)) — 已移除，名称被两参数函数占用 */
/* #define fr_sin_deg(deg)  fr_sin_bam(FR_DEG2BAM_I(deg)) — 已移除，名称被两参数函数占用 */

#ifndef FR_LEAN
/*===============================================
 * 角度输入的三角函数 API
 *
 *   FR_CosI(deg)              — 整数度数的余弦，返回 s15.16
 *   FR_SinI(deg)              — 整数度数的正弦，返回 s15.16
 *   FR_TanI(deg)              — 整数度数的正切，返回 s15.16
 *   fr_cos_deg(deg, radix)    — 固定基数的度数的余弦，返回 s15.16
 *   fr_sin_deg(deg, radix)    — 固定基数的度数的正弦，返回 s15.16
 *   fr_tan_deg(deg, radix)    — 固定基数的度数的正切，返回 s15.16
 */
#define FR_CosI(deg)  fr_cos_bam(FR_DEG2BAM_I(deg))
#define FR_SinI(deg)  fr_sin_bam(FR_DEG2BAM_I(deg))

  s32 fr_cos_deg(s32 deg, u16 radix);
  s32 fr_sin_deg(s32 deg, u16 radix);
  s32 FR_TanI(s32 deg);
  s32 fr_tan_deg(s32 deg, u16 radix);

  /* 遗留宏 — 新代码请使用 fr_sin_deg/fr_cos_deg/fr_tan_deg */
  #define FR_Sin  fr_sin_deg
  #define FR_Cos  fr_cos_deg
  #define FR_Tan  fr_tan_deg
#endif /* FR_LEAN */

  /* 反三角函数 — 输出弧度，基数由调用者指定（s32）。
   * FR_atan2 返回基数 16（s15.16）的弧度。
   * 值域：acos [0, pi], asin [-pi/2, pi/2],
   *       atan [-pi/2, pi/2], atan2 [-pi, pi]。
   */
  s32 FR_acos(s32 input, u16 radix, u16 out_radix);
  s32 FR_asin(s32 input, u16 radix, u16 out_radix);
  s32 FR_atan(s32 input, u16 radix, u16 out_radix);
  s32 FR_atan2(s32 y, s32 x, u16 out_radix);

/* 对数 */
#define FR_LOG2MIN (-(32767 << 16)) /* 当结果为负无穷时返回该值 */

  s32 FR_log2(s32 input, u16 radix, u16 output_radix);
  s32 FR_ln(s32 input, u16 radix, u16 output_radix);
#ifndef FR_LEAN
  s32 FR_log10(s32 input, u16 radix, u16 output_radix);
#endif

  /* 幂运算 */
  s32 FR_pow2(s32 input, u16 radix);
#define FR_EXP(input, radix)   (FR_pow2(FR_MULK28((input), FR_kLOG2E_28), (radix)))
#define FR_POW10(input, radix) (FR_pow2(FR_MULK28((input), FR_kLOG2_10_28), (radix)))

/* 仅用移位的基数转换变体（无乘法）。
 * 精度较低（Q16.16 下约 5-10 LSB），但不需要乘法指令。
 * 适用于 32x32->64 乘法昂贵的平台。
 */
#define FR_EXP_FAST(input, radix)   (FR_pow2(FR_SLOG2E(input), radix))
#define FR_POW10_FAST(input, radix) (FR_pow2(FR_SLOG2_10(input), radix))

/*===============================================
 * 格式化输出和字符串解析
 *
 * 定义 FR_NO_PRINT 后再包含本头文件，可以排除所有打印/格式化函数。
 * 对于不需要人可读输出的目标（如无头传感器节点、纯 DSP 固件），这可以节省约 1.7 KB 的 ROM。
 *
 *   #define FR_NO_PRINT
 *   #include "FR_math.h"
 */
#ifndef FR_NO_PRINT

  /* 打印函数族 */
  int FR_printNumF(int (*f)(char), s32 n, int radix, int pad, int prec); /* 将定点数打印为浮点数，例如 "-12.34" */
  int FR_printNumD(int (*f)(char), int n, int pad);                      /* 打印带可选填充的十进制数，例如 " 12" */
  int FR_printNumH(int (*f)(char), int n, int showPrefix);               /* 将数打印为十六进制，例如 "0x12ab" */

  /* 字符串到定点数解析器（FR_printNumF 的逆操作） */
  s32 FR_numstr(const char *s, u16 radix);

#endif /* FR_NO_PRINT */

/*===============================================
 * 平方根和斜边
 *
 * 两者都接受给定基数的输入，返回相同基数的结果。
 * 算法：在 64 位累加器上按位逐位求平方根（无除法，最多 32 次迭代）。
 * 四舍五入到最近值。
 *
 * 定义域错误标记：input < 0（sqrt）返回 FR_DOMAIN_ERROR。
 * 调用者可通过检查 `result == FR_DOMAIN_ERROR` 来检测域错误。
 */
  s32 FR_sqrt(s32 input, u16 radix);
#ifndef FR_LEAN
  s32 FR_hypot(s32 x, s32 y, u16 radix);
#endif

  /* 快速近似幅度 — 仅用移位，无乘法，无 64 位。
   * 基于分段线性近似 sqrt(x*x + y*y)。
   * 参见美国专利 6,567,777 B1（Chatterjee，已过期）。
   *
   *   FR_hypot_fast8(x, y)  8 段，峰值误差约 0.10%
   *
   * 输入为原始有符号整数（或任何基数的定点数 — 结果与输入基数相同，如同 FR_hypot）。
   * 不需要基数参数，因为算法是尺度不变的。
   */
  s32 FR_hypot_fast8(s32 x, s32 y);

/*===============================================
 * 波形发生器和 ADSR 包络
 *
 * 定义 FR_NO_WAVES 后包含本头文件，可以排除所有波形发生器（方波、脉宽波、三角波、锯齿波、噪声）和 ADSR 包络。
 * 对于只需要数学/三角函数而不做音频合成的目标，这可以节省约 400 B 的 ROM。
 *
 *   #define FR_NO_WAVES
 *   #include "FR_math.h"
 */
#ifndef FR_NO_WAVES

/*===============================================
 * 波形发生器 — 合成风格的固定形状波形。
 *
 * 所有函数接受 u16 BAM 相位（范围 [0, 65535]，代表一个完整周期），返回 s16，范围为 s0.15 即 [-32767, +32767]。
 * 使用下面的 FR_HZ2BAM_INC 宏计算目标频率的每样本相位增量。
 *
 *   fr_wave_sqr(phase)              50% 占空比方波
 *   fr_wave_pwm(phase, duty)        可变脉宽脉冲波
 *   fr_wave_tri(phase)              对称三角波
 *   fr_wave_saw(phase)              上升锯齿波
 *   fr_wave_tri_morph(phase, brk)   变对称三角波（可渐变为锯齿）
 *   fr_wave_noise(state*)           LFSR 伪随机噪声
 *
 * fr_wave_tri_morph 返回 [0, 32767]（单极性）— 如需双极性，调用者可以重新偏置。
 * 其他波形为双极性 [-32767, +32767]。
 */
  s16 fr_wave_sqr(u16 phase);
  s16 fr_wave_pwm(u16 phase, u16 duty);
  s16 fr_wave_tri(u16 phase);
  s16 fr_wave_saw(u16 phase);
  s16 fr_wave_tri_morph(u16 phase, u16 break_point);
  s16 fr_wave_noise(u32 *state);

/* FR_HZ2BAM_INC(hz, sample_rate)
 * 给定目标频率（Hz）和采样率（Hz），计算每样本的 BAM 相位增量。
 * 结果是一个 u16，每次采样加到运行相位上（因为 u16 自动回绕，相位自然模 2^16）。
 *
 *   u16 phase = 0;
 *   u16 inc   = FR_HZ2BAM_INC(440, 48000);
 *   for (...) { sample = fr_sin_bam(phase); phase += inc; }
 *
 * 范围：频率必须小于 sample_rate / 2（奈奎斯特频率）才能产生有效音调；更高频率会产生混叠。
 * 宏不强制这一点。
 *
 * 副作用：hz 和 sample_rate 各被求值一次。
 */
#define FR_HZ2BAM_INC(hz, sample_rate)  ((u16)(((u32)(hz) * 65536UL) / (u32)(sample_rate)))

/*===============================================
 * ADSR 包络发生器
 *
 * 线性分段 Attack-Decay-Sustain-Release 包络。由调用者分配结构体，无动态内存分配，无全局状态。
 * 内部电平以 s1.30 存储，因此即使是很长的包络（例如 48 kHz 下 48000 样本的起音）每样本增量也非零。
 * 输出为 s0.15，范围 [0, 32767]。
 *
 * 生命周期：
 *   fr_adsr_t env;
 *   fr_adsr_init(&env, atk_samples, dec_samples, sustain_s015, rel_samples);
 *   fr_adsr_trigger(&env);                 // 按键按下
 *   for (...) sample = fr_adsr_step(&env); // 每音频样本
 *   fr_adsr_release(&env);                 // 按键释放
 *   for (...) sample = fr_adsr_step(&env); // 直到 env.state == FR_ADSR_IDLE
 */
#define FR_ADSR_IDLE     (0)
#define FR_ADSR_ATTACK   (1)
#define FR_ADSR_DECAY    (2)
#define FR_ADSR_SUSTAIN  (3)
#define FR_ADSR_RELEASE  (4)

typedef struct fr_adsr_s {
    u8  state;        /* FR_ADSR_* 状态码 */
    s32 level;        /* 当前包络电平，s1.30 */
    s32 sustain;      /* 保持电平，s1.30 */
    s32 attack_inc;   /* 起音阶段每样本增量 */
    s32 decay_dec;    /* 衰减阶段每样本减量 */
    s32 release_dec;  /* 释放阶段每样本减量 */
} fr_adsr_t;

  void fr_adsr_init(fr_adsr_t *env,
                    u32 attack_samples,
                    u32 decay_samples,
                    s16 sustain_level_s015,
                    u32 release_samples);
  void fr_adsr_trigger(fr_adsr_t *env);
  void fr_adsr_release(fr_adsr_t *env);
  s16  fr_adsr_step(fr_adsr_t *env);

#endif /* FR_NO_WAVES */

#ifdef __cplusplus

} // extern "C"
#endif

#endif /* __FR_Math_h__ */
