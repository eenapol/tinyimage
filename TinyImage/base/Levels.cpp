#include "base/Levels.h"
#include "base/Curve.h"
#include <cmath>


namespace TinyImage{


void	AdjustLevels(TiBitmapData& bitmap,int blackThreshold,int whiteThreshold,double gamma,TINYIMAGE_CHANNEL channel)
{
	TINYIMAGE_ASSERT_VOID(blackThreshold>= 0 && whiteThreshold>blackThreshold && whiteThreshold<=255);
	TINYIMAGE_ASSERT_VOID(gamma >= 0.0 && gamma <= 10.0);

	u8 lookup[256] = {0};
	//С�ںڳ���ֵ�����0 
	for (int i = 0; i < blackThreshold; i ++)
	{
		lookup[i] = 0;
	}
	//�м䲿����gammaУ��
	double ig = (gamma == 0.0) ? 0.0 : 1 / gamma;
	double threshold = (double)(whiteThreshold - blackThreshold);
	for (int i = blackThreshold; i < whiteThreshold; i++)
	{
		lookup[i] = (u8)CLAMP0255( pow((i-blackThreshold)/threshold,ig)*255);
	}
	//���ڰ׳���ֵ����Ϊ255
	for (int i = whiteThreshold; i < 256; i++)
	{
		lookup[i] = 255;
	}
	AdjustCurve(bitmap,lookup,channel);
}

}