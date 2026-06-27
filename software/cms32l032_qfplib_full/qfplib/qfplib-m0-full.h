#ifndef __QFPLIB_M0_FULL_H__
#define __QFPLIB_M0_FULL_H__

/*
Copyright 2019-2024 Mark Owen
http://www.quinapalus.com
E-mail: qfp@quinapalus.com

This file is free software: you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License
as published by the Free Software Foundation.

This file is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this file.  If not, see <http://www.gnu.org/licenses/> or
write to the Free Software Foundation, Inc., 51 Franklin Street,
Fifth Floor, Boston, MA  02110-1301, USA.
*/

typedef unsigned           int ui32;
typedef                    int i32;
typedef unsigned long long int ui64;
typedef          long long int i64;

// ==================== 单精度浮点 (float) ====================

extern float  qfp_fadd          (float x, float y);   // 单精度加法：x + y
extern float  qfp_fsub          (float x, float y);   // 单精度减法：x - y
extern float  qfp_fmul          (float x, float y);   // 单精度乘法：x * y
extern float  qfp_fdiv          (float x, float y);   // 单精度除法：x / y
extern int    qfp_fcmp          (float x, float y);   // 单精度比较：返回 -1 (x<y), 0 (x==y), 1 (x>y)

extern float  qfp_fsqrt         (float x);            // 单精度平方根：√x

extern i32    qfp_float2int     (float x);            // 将单精度浮点数转换为 32 位整数（截断）
extern i32    qfp_float2fix     (float x, int f);     // 将单精度浮点数转换为 Qf 定点数（f 表示小数位数，截断）
extern ui32   qfp_float2uint    (float x);            // 将单精度浮点数转换为 32 位无符号整数（截断）
extern ui32   qfp_float2ufix    (float x, int f);     // 将单精度浮点数转换为无符号 Qf 定点数（截断）

extern float  qfp_int2float     (i32 x);              // 将 32 位有符号整数转换为单精度浮点数
extern float  qfp_fix2float     (i32 x, int f);       // 将 Qf 定点数（有符号）转换为单精度浮点数
extern float  qfp_uint2float    (ui32 x);             // 将 32 位无符号整数转换为单精度浮点数
extern float  qfp_ufix2float    (ui32 x, int f);      // 将无符号 Qf 定点数转换为单精度浮点数

extern float  qfp_int642float   (i64 x);              // 将 64 位有符号整数转换为单精度浮点数
extern float  qfp_fix642float   (i64 x, int f);       // 将 64 位 Qf 定点数转换为单精度浮点数
extern float  qfp_uint642float  (ui64 x);             // 将 64 位无符号整数转换为单精度浮点数
extern float  qfp_ufix642float  (ui64 x, int f);      // 将 64 位无符号 Qf 定点数转换为单精度浮点数

extern float  qfp_fcos          (float x);            // 单精度余弦：cos(x)，x 单位为弧度
extern float  qfp_fsin          (float x);            // 单精度正弦：sin(x)
extern float  qfp_ftan          (float x);            // 单精度正切：tan(x)
extern float  qfp_fatan2        (float y, float x);   // 单精度反正切：atan2(y, x)，返回 (-π, π] 弧度
extern float  qfp_fexp          (float x);            // 单精度指数：e^x
extern float  qfp_fln           (float x);            // 单精度自然对数：ln(x)

// ==================== 双精度浮点 (double) ====================

extern double qfp_dadd          (double x, double y); // 双精度加法
extern double qfp_dsub          (double x, double y); // 双精度减法
extern double qfp_dmul          (double x, double y); // 双精度乘法
extern double qfp_ddiv          (double x, double y); // 双精度除法
extern double qfp_dsqrt         (double x);           // 双精度平方根
extern double qfp_dcos          (double x);           // 双精度余弦
extern double qfp_dsin          (double x);           // 双精度正弦
extern double qfp_dtan          (double x);           // 双精度正切
extern double qfp_datan2        (double y, double x); // 双精度反正切
extern double qfp_dexp          (double x);           // 双精度指数
extern double qfp_dln           (double x);           // 双精度自然对数
extern int    qfp_dcmp          (double x, double y); // 双精度比较：返回 -1/0/1

// ==================== 单精度浮点 → 64位整数/定点 ====================

extern i64    qfp_float2int64   (float x);            // 单精度 → 64 位有符号整数（截断）
extern i64    qfp_float2fix64   (float x, int f);     // 单精度 → 有符号 64 位 Qf 定点数（截断）
extern ui64   qfp_float2uint64  (float x);            // 单精度 → 64 位无符号整数（截断）
extern ui64   qfp_float2ufix64  (float x, int f);     // 单精度 → 无符号 64 位 Qf 定点数（截断）

extern i32    qfp_float2int_z   (float x);            // 单精度 → 32 位整数，向零取整（与 trunc 相同）
extern i64    qfp_float2int64_z (float x);            // 单精度 → 64 位整数，向零取整

// ==================== 双精度浮点 → 整数/定点 ====================

extern i32    qfp_double2int    (double x);           // 双精度 → 32 位有符号整数（截断）
extern i32    qfp_double2fix    (double x, int f);    // 双精度 → 有符号 32 位 Qf 定点数（截断）
extern ui32   qfp_double2uint   (double x);           // 双精度 → 32 位无符号整数（截断）
extern ui32   qfp_double2ufix   (double x, int f);    // 双精度 → 无符号 32 位 Qf 定点数（截断）
extern i64    qfp_double2int64  (double x);           // 双精度 → 64 位有符号整数（截断）
extern i64    qfp_double2fix64  (double x, int f);    // 双精度 → 有符号 64 位 Qf 定点数（截断）
extern ui64   qfp_double2uint64 (double x);           // 双精度 → 64 位无符号整数（截断）
extern ui64   qfp_double2ufix64 (double x, int f);    // 双精度 → 无符号 64 位 Qf 定点数（截断）
extern i32    qfp_double2int_z  (double x);           // 双精度 → 32 位整数，向零取整
extern i64    qfp_double2int64_z(double x);           // 双精度 → 64 位整数，向零取整

// ==================== 整数/定点 → 双精度浮点 ====================

extern double qfp_int2double    (i32  x);             // 32 位有符号整数 → 双精度浮点数
extern double qfp_fix2double    (i32  x, int f);      // 有符号 32 位 Qf 定点数 → 双精度浮点数
extern double qfp_uint2double   (ui32 x);             // 32 位无符号整数 → 双精度浮点数
extern double qfp_ufix2double   (ui32 x, int f);      // 无符号 32 位 Qf 定点数 → 双精度浮点数
extern double qfp_int642double  (i64  x);             // 64 位有符号整数 → 双精度浮点数
extern double qfp_fix642double  (i64  x, int f);      // 有符号 64 位 Qf 定点数 → 双精度浮点数
extern double qfp_uint642double (ui64 x);             // 64 位无符号整数 → 双精度浮点数
extern double qfp_ufix642double (ui64 x, int f);      // 无符号 64 位 Qf 定点数 → 双精度浮点数

// ==================== 精度转换 ====================

extern float  qfp_double2float  (double x);           // 双精度浮点数 → 单精度浮点数（舍入）
extern double qfp_float2double  (float x);            // 单精度浮点数 → 双精度浮点数（精确转换）

#endif
