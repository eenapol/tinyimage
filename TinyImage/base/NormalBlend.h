/**
 * @file    NormalBlend.h
 * @brief   �ں�......
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @since   2010-12
 * @website www.xiangwangfeng.com
 */


#pragma once
#include "GlobalData.h"
#include "global/BitmapData.h"

namespace TinyImage{

struct TinyRGBA;
struct TinyRGB;

u8		FastScaleByteByByte(u8 a, u8 b);
void	Blend(const TinyRGB* bgColor,u8 bgColorAlpha, const TinyRGBA* fgColor, TinyRGB* dstColor, u8 coverAlpha);//�ں�
void	BlendLayerMask(TiBitmapData& bitmap, TinyRGBA *mask,int maskX, int maskY,  int maskWidth, int maskHeight, u8 maskAlpha ); //��ͨ�ں��ɲ�

}