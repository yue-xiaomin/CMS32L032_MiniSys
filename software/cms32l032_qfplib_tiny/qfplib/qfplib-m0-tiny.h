// Copyright 2015 Mark Owen
// http://www.quinapalus.com
// E-mail: qfp@quinapalus.com
//
// Thanks to Bill Westfield
//
// This file is free software: you can redistribute it and/or modify
// it under the terms of version 2 of the GNU General Public License
// as published by the Free Software Foundation.
//
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this file.  If not, see <http://www.gnu.org/licenses/> or
// write to the Free Software Foundation, Inc., 51 Franklin Street,
// Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef _QFPLIB_H_
#define _QFPLIB_H_

#ifdef __cplusplus
  extern "C" {
#endif

// ==================== 基本算术运算 ====================
extern float qfp_fadd(float x, float y);         // 单精度加法：x + y
extern float qfp_fsub(float x, float y);         // 单精度减法：x - y
extern float qfp_fmul(float x, float y);         // 单精度乘法：x * y
extern float qfp_fdiv(float x, float y);         // 单精度除法：x / y
extern float qfp_fdiv_fast(float x, float y);    // 快速单精度除法（精度略低，速度更快）

// ==================== 浮点 → 整数/定点（向零取整） ====================
extern int   qfp_float2int(float x);             // 单精度浮点数 → 32位有符号整数（截断）
extern int   qfp_float2fix(float x, int y);      // 单精度浮点数 → Qy 格式有符号定点数（y = 小数位数）
extern unsigned int qfp_float2uint(float x);     // 单精度浮点数 → 32位无符号整数（截断）
extern unsigned int qfp_float2ufix(float x, int y); // 单精度浮点数 → Qy 格式无符号定点数

// ==================== 整数/定点 → 浮点 ====================
extern float qfp_int2float(int x);               // 32位有符号整数 → 单精度浮点数
extern float qfp_fix2float(int x, int y);        // 有符号 Qy 定点数 → 单精度浮点数
extern float qfp_uint2float(unsigned int x);     // 32位无符号整数 → 单精度浮点数
extern float qfp_ufix2float(unsigned int x, int y); // 无符号 Qy 定点数 → 单精度浮点数

// ==================== 浮点数比较 ====================
extern int qfp_fcmp(float x, float y);           // 比较两个单精度浮点数：
                                                 // 返回值 -1 (x < y), 0 (x == y), 1 (x > y)

// ==================== 三角函数 ====================
extern float qfp_fcos(float x);                  // 单精度余弦：cos(x)，x为弧度
extern float qfp_fsin(float x);                  // 单精度正弦：sin(x)
extern float qfp_ftan(float x);                  // 单精度正切：tan(x)
extern float qfp_fatan2(float y, float x);       // 单精度反正切：atan2(y, x)，返回 (-π, π] 弧度

// ==================== 指数与对数 ====================
extern float qfp_fexp(float x);                  // 单精度指数：e^x
extern float qfp_fln(float x);                   // 单精度自然对数：ln(x)，x > 0

// ==================== 平方根 ====================
extern float qfp_fsqrt(float x);                 // 单精度平方根：√x
extern float qfp_fsqrt_fast(float x);            // 快速单精度平方根（精度略低，速度更快）

#ifdef __cplusplus
  } // extern "C"
#endif
#endif
