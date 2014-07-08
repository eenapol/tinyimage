/**
 * @file    BlendMode.h
 * @brief   ͼ����
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @since   2011-02
 * @website www.xiangwangfeng.com
 */

#pragma once
#include "GlobalData.h"
#include "global/BitmapData.h"

namespace TinyImage{

//ͼ����
void	BlendMode(TiBitmapData& srcBitmap,TINYIMAGE_CHANNEL srcChannel,
				  TiBitmapData& blendBitmap,TINYIMAGE_CHANNEL blendChannel,
				  TINYIMAGE_BLENDMODE mode,double opacity);

//����LookupTable
void	GenerateLookupTable(u8 (&lookup)[256][256],TINYIMAGE_BLENDMODE mode,double opacity);

//������ߵ���
void	AdjustBlendModeCurve(TiBitmapData& srcBitmap,TINYIMAGE_CHANNEL srcChannel,
							 TiBitmapData& blendBitmap,TINYIMAGE_CHANNEL blendChannel,
							 u8 (&lookup)[256][256]);
//int��Channelת��
int		ConvertRGBIndex(TINYIMAGE_CHANNEL channel);	

//GLT = Generate Lookup Table
//���ɸ���ͼ������Ҫ��Lookup Table
void	GLT_Darken(u8 (&lookup)[256][256],double opacity);			//�䰵
void	GLT_Lighten(u8 (&lookup)[256][256],double opacity);			//����
void	GLT_Multiply(u8 (&lookup)[256][256],double opacity);		//��Ƭ����
void	GLT_Screen(u8 (&lookup)[256][256],double opacity);			//��ɫ
void	GLT_ColorDodge(u8 (&lookup)[256][256],double opacity);		//ɫ�ʼ���
void	GLT_ColorBurn(u8 (&lookup)[256][256],double opacity);		//ɫ�ʼ���
void	GLT_LinearDodge(u8 (&lookup)[256][256],double opacity);		//���Լ���
void	GLT_LinearBurn(u8 (&lookup)[256][256],double opacity);		//���Լ���
void	GLT_Overlay(u8 (&lookup)[256][256],double opacity);			//����
void	GLT_HardLight(u8 (&lookup)[256][256],double opacity);		//ǿ��
void	GLT_SoftLight(u8 (&lookup)[256][256],double opacity);		//���
void	GLT_VividLight(u8 (&lookup)[256][256],double opacity);		//����
void	GLT_LinearLight(u8 (&lookup)[256][256],double opacity);		//���Թ�
void	GLT_PinLight(u8 (&lookup)[256][256],double opacity);		//���
void	GLT_HardMix(u8 (&lookup)[256][256],double opacity);			//ʵɫ���
void	GLT_Add(u8 (&lookup)[256][256],double opacity);				//���
void	GLT_Sub(u8 (&lookup)[256][256],double opacity);				//���
void	GLT_Difference(u8 (&lookup)[256][256],double opacity);		//��ֵ
void	GLT_Exclusion(u8 (&lookup)[256][256],double opacity);		//�ų�

}