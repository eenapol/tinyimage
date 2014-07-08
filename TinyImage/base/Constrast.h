/**
 * @file    Constrast.h
 * @brief   �Աȶȵ���
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @since   2010-12
 * @website www.xiangwangfeng.com
 */

#pragma once
#include "global/BitmapData.h"
namespace TinyImage{

//�Աȶȵ���
void	AdjustContrast(TiBitmapData& bitmap,double level);	

//ʹ����ֵ���е���
void	AdjustContrastUsingConstThreshold(TiBitmapData& bitmap,double level);

//ʹ��ƽ��ֵ���е���
void	AdjustContrastUsingAverageThreshold(TiBitmapData& bitmap,double level);

}