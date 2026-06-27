// Copyright 2015 Mark Owen
// http://www.quinapalus.com
// E-mail: qfp@quinapalus.com
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

#ifndef _QFPIO_H_
#define _QFPIO_H_

#ifdef __cplusplus
  extern "C" {
#endif

/**
 * @brief 将单精度浮点数转换为格式化字符串
 * @param f   [IN] 要转换的浮点数
 * @param s   [OUT] 存放转换后字符串的缓冲区指针
 * @param fmt [IN] 格式化参数，用于控制输出格式
 * 
 * @note 常见fmt取值：
 *       - 0     ： 自动格式，去除末尾多余的0（例如将 3.140000 输出为 3.14）
 *       - 1~6   ： 强制保留指定位数的小数，超出四舍五入；未达到则补零（例如 fmt=3 输出 3.140）
 *       - 7~... ： 可能用于启用科学计数法或其他特殊格式
 */
extern void qfp_float2str(float f, char *s, unsigned int fmt);

/**
 * @brief 从字符串中解析出单精度浮点数，通常配合串口接收指令使用
 * @param f       [OUT] 指向存储解析结果浮点数的指针
 * @param p       [IN]  指向待解析的字符串
 * @param endptr  [OUT] 可选参数，用于返回第一个无法解析的字符的地址
 * 
 * @return 成功时返回 0，失败时可能返回非 0
 * 
 * @note 具体行为需结合 qfpio.s 的实现确认，端指针功能可以帮助进行复杂的自定义解析
 */
extern int qfp_str2float(float *f, char *p, char **endptr);

#ifdef __cplusplus
  } // extern "C"
#endif
#endif
