/**
 * @file    ColorType.h
 * @brief   ��ɫ����
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @since   2010-12
 * @website www.xiangwangfeng.com
 */


#pragma once
#include "GlobalData.h"

namespace TinyImage{

//�Ҷ�ת������
const double RGB_LUMINANCE_RED = 0.2126;
const double RGB_LUMINANCE_GREEN = 0.7152;
const double RGB_LUMINANCE_BLUE = 0.0722;

#define RGB_LUMINANCE(r,g,b) ((r) * RGB_LUMINANCE_RED   + \
	(g) * RGB_LUMINANCE_GREEN + \
	(b) * RGB_LUMINANCE_BLUE)





//RGBA
struct TinyRGBA {
public:
	TinyRGBA()
	{
		
	}
	//�õ��Ҷ�ֵ
	u8 getLuminance() const {
		u8 luminance = (u8)ROUND(RGB_LUMINANCE(m_red, m_green, m_blue));
		return CLAMP0255(luminance);
	}

	u8 m_blue;	//��ɫ
	u8 m_green;	//��ɫ
	u8 m_red;	//��ɫ
	u8 m_alpha;	//Alphaͨ��
};

//RGB
struct TinyRGB 
{
	public:
		TinyRGB(u8 red,u8 green,u8 blue)
		{
			m_blue = blue;
			m_green= green;
			m_red = red;
		}
		//�õ��Ҷ�ֵ	
		u8 getLuminance() const {
			u8 luminance = (u8)ROUND(RGB_LUMINANCE(m_red, m_green, m_blue));
			return CLAMP0255(luminance);
		}

		u8 m_blue;	/** �� */
		u8 m_green;	/** �� */
		u8 m_red;	/** �� */
};


//HSL
struct TinyHSL 
{
	int m_hue;				//ɫ��   [0,360]
	double m_saturation;	//���Ͷ� [0,1]
	double m_lightness;		//����   [0,1]
};

}