/**
 * @file    Curve.h
 * @brief   ���ߵ���
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @since   2010-12
 * @website www.xiangwangfeng.com
 */

#pragma once
#include "GlobalData.h"
#include "global/BitmapData.h"

namespace TinyImage{


void	AdjustCurve(TiBitmapData& bitmap,u8 (&lookup)[256],TINYIMAGE_CHANNEL channel);						//��LookupTable���ߵ���
void	AdjustCurve(TiBitmapData& bitmap,u8 (&r_lookup)[256],u8 (&g_lookup)[256],u8 (&b_lookup)[256]);//��ͨ�����ߵ���
void	PreserveLuminosityAdjustCurve(TiBitmapData& bitmap,u8 (&r_lookup)[256],u8 (&g_lookup)[256],u8 (&b_lookup)[256]);//��֤���ص����Ȳ�������ߵ���

}