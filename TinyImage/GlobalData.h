/**
 * @file    GlobalData.h
 * @brief   ��������
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @since   2010-12
 * @website www.xiangwangfeng.com
 */


#pragma once
#include <cassert>


namespace TinyImage
{

typedef unsigned char u8;
typedef unsigned int   u32;

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#define ROUND(x) ((int) ((x) + 0.5))

#ifndef CLAMP
#define CLAMP(x,l,u) ((x)<(l)?(l):((x)>(u)?(u):(x)))
#endif

#define CLAMP0255(x) ((x)<(0)?(0):((x)>(255)?(255):(x)))
#define TINYIMAGE_ASSERT_VOID(p)  {assert(p);if(!(p)) {return;}}
#define TINYIMAGE_ASSERT_NULL(p)  {assert(p);if(!(p)) {return 0;}}
#define SQR(x) ((x)*(x))
#define TINYIMAGE_PI 3.1415926535897932384626433832795
#define TINYIMAGE_2PI   (2.0*TINYIMAGE_PI)

//RGBͨ��
enum TINYIMAGE_CHANNEL
{
	TINYIMAGE_CHANEL_RGB,	
	TINYIMAGE_CHANEL_R,
	TINYIMAGE_CHANEL_G,
	TINYIMAGE_CHANEL_B,
};

//����������
enum TINYIMAGE_TRANSFERMODE
{
	TINYIMAGE_TRANSFERMODE_SHADOWS,		//��Ӱ
	TINYIMAGE_TRANSFERMODE_MIDTONES,	//�м��
	TINYIMAGE_TRANSFERMODE_HIGHLIGHTS,	//�߹�
};

//ɫ�ʷ�Χ
enum TINYIMAGE_HUERANGE
{
	TINYIMAGE_HUERANGE_ALLHUES,		//ȫͼ
	TINYIMAGE_HUERANGE_RED,			//��
	TINYIMAGE_HUERANGE_YELLOW,		//��
	TINYIMAGE_HUERANGE_GREEN,		//��
	TINYIMAGE_HUERANGE_CYAN,		//��
	TINYIMAGE_HUERANGE_BLUE,		//��
	TINYIMAGE_HUERANGE_MAGENTA,		//���
};

enum TINYIMAGE_BLENDMODE
{
	TINYIMAGE_BLENDMODE_DARKEN,			//�䰵
	TINYIMAGE_BLENDMODE_LIGHTEN,		//����
	TINYIMAGE_BLENDMODE_MULTIPLY,		//��Ƭ����
	TINYIMAGE_BLENDMODE_SCREEN,			//��ɫ
	TINYIMAGE_BLENDMODE_COLORDODGE,		//��ɫ����
	TINYIMAGE_BLENDMODE_COLORBURN,		//��ɫ����
	TINYIMAGE_BLENDMODE_LINEARDODGE,	//���Լ���
	TINYIMAGE_BLENDMODE_LINEARBURN,		//���Լ���
	TINYIMAGE_BLENDMODE_OVERLAY,		//����
	TINYIMAGE_BLENDMODE_SOFTLIGHT,		//���
	TINYIMAGE_BLENDMODE_HARDLIGHT,		//ǿ��
	TINYIMAGE_BLENDMODE_VIVIDLIGHT,		//����
	TINYIMAGE_BLENDMODE_LINEARLIGHT,	//���Թ�
	TINYIMAGE_BLENDMODE_PINLIGHT,		//���
	TINYIMAGE_BLENDMODE_HARDMIX,		//ʵɫ���
	TINYIMAGE_BLENDMODE_ADD,			//���
	TINYIMAGE_BLENDMODE_SUB,			//���
	TINYIMAGE_BLENDMODE_DIFFERENCE,		//��ֵ
	TINYIMAGE_BLENDMODE_EXCLUSION,		//�ų�
};

const int TiRGBBpp		= 3;
const int TiRGBABpp		= 4;
const int TiBlue		= 0;
const int TiGreen		= 1;
const int TiRed			= 2;
const int TiAlpha		= 3;
const double TIEPSILON	= 0.000001;

}

