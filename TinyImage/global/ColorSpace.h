/**
 * @file    ColorSpace.h
 * @brief   ɫ�ʿռ�
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @since   2010-12
 * @website www.xiangwangfeng.com
 */
#pragma once

namespace TinyImage{

struct TinyRGBA;
struct TinyRGB;
struct TinyHSL;
/************************************************************************/
/*                   ��ɫ�ռ�ת������                                   */
/************************************************************************/

//RGBתHSL
void Rgb2Hsl(const TinyRGB *rgb, TinyHSL *hsl);

//HSLת��RGB
void Hsl2Rgb(const TinyHSL *hsl, TinyRGB *rgb);

//RGBתHSL��ֻ��ȡL
int Rgb2Hsl_L(u8 red,u8 green,u8 blue);


//RGBתHSL int(���������һ����������)
void Rgb2Hsl_Int (int& red, int& green,int& blue);

//HSLתRGB int
void Hsl2Rgb_Int (int& hue,int& saturation,int& lightness);

}