#include "filter/Lomo.h"
#include "base/NormalBlend.h"
#include "base/ColorBalance.h"
#include "base/Levels.h"
#include <cmath>
namespace TinyImage{


void DarkenCorner(TiBitmapData& bitmap, double brightRatio, u8 maskAlpha) 
{
	TINYIMAGE_ASSERT_VOID(brightRatio <= 1.0 && brightRatio >= 0.0);

	int width	= bitmap.GetWidth();
	int height	= bitmap.GetHeight();
	u8* bmpData = bitmap.GetBmpData();
	int stride	= bitmap.GetStride();
	int bpp		= bitmap.GetBpp();

	//������Բ
	int halfWidth			= width / 2;
	int halfHeight			= height/ 2;
	double effectWidth		= halfWidth * brightRatio; 
	double effectHeight		= halfHeight * brightRatio;
	int maxHalfWidthHeight	= (halfWidth > halfHeight) ? halfWidth : halfHeight;

	bool round		= (halfWidth == halfHeight);	
	bool focusOnX	= (halfWidth > halfHeight);
	double focus	= round ? 0.0 : sqrt(fabs(((effectWidth) * (effectWidth) - (effectHeight) * (effectHeight))));
	double f1X		= focusOnX ? focus : 0.0;
	double f1Y		= focusOnX ? 0.0 : focus;
	double f2X		= focusOnX ? -focus : 0.0;
	double f2Y		= focusOnX ? 0.0 : -focus;
	double mindist	= MAX(effectWidth, effectHeight) * 2; // ��Բ���Ͼ��룬�õ�����Ϊ255
	double maxdist = sqrt((halfWidth - f1X) * (halfWidth  -1 - f1X) + (halfHeight -1 - f1Y) * (halfHeight -1 - f1Y))
					+ sqrt((halfWidth - f2X) * (halfWidth -1 - f2X) + (halfHeight -1 - f2Y) * (halfHeight -1 - f2Y)); //�Խǵ���Բ�ľ���
	assert(mindist == effectWidth * 2 || mindist == effectHeight * 2 );

	double	effectHeightSQR = SQR(effectHeight);
	double	effectWidthSQR  = SQR(effectWidth);
	double	effectAreaSQR   = SQR(effectHeight * effectWidth);
	double* lookupSQR = new double[maxHalfWidthHeight];		//����ƽ������LookupTable
	for (int i = 0; i < maxHalfWidthHeight; i ++)
	{
		lookupSQR[i] = (double(i))*i;
	}

	//�����Ŀ��ɲ�
	TinyRGBA* lefttopMask		= new TinyRGBA[halfWidth * halfHeight];
	TinyRGBA* leftbottomMask	= new TinyRGBA[halfWidth * halfHeight];
	TinyRGBA* righttopMask		= new TinyRGBA[halfWidth * halfHeight];
	TinyRGBA* rightbottomMask	= new TinyRGBA[halfWidth * halfHeight];

	TinyRGBA* dot = rightbottomMask;
	for (int j = 0; j < halfHeight; ++j) 
	{
		for (int i = 0; i < halfWidth; ++i) 
		{
			if (lookupSQR[i] * effectHeightSQR + lookupSQR[j] * effectWidthSQR < effectAreaSQR) 
			{
				// ��Բ��
				dot->m_alpha = 0;
				dot->m_blue = dot->m_red = dot->m_green = 0;
			} 
			else 
			{
				// ��Բ�⣬���㵽����������
				double dist = sqrt((i - f1X) * (i - f1X) + (j - f1Y) * (j - f1Y)) + sqrt((i - f2X) * (i - f2X) + (j - f2Y) * (j - f2Y));
				dist = MAX(dist, mindist);
				dist = MIN(dist, maxdist);
				assert(dist >= mindist && dist <= maxdist);
				double fact = (dist - mindist) / (maxdist - mindist);
				dot->m_alpha = (u8)(255 * fact * fact);
				dot->m_blue = dot->m_red = dot->m_green = 0;
			}
			int xOffset = halfWidth-1-i;
			int yOffset =  halfWidth*(halfHeight - 1 - j);

			lefttopMask[xOffset + yOffset]			= *dot;
			leftbottomMask[xOffset +j*(halfWidth)]	= *dot;
			righttopMask[yOffset + i]				= *dot;
			
			dot++;

		}
	}
	
	BlendLayerMask(bitmap, lefttopMask, 0, 0,halfWidth, halfHeight, maskAlpha);
	BlendLayerMask(bitmap, righttopMask, halfWidth, 0, halfWidth, halfHeight,maskAlpha);
	BlendLayerMask(bitmap, leftbottomMask, 0, halfHeight,halfWidth, halfHeight,maskAlpha);
	BlendLayerMask(bitmap, rightbottomMask, halfWidth, halfHeight,halfWidth, halfHeight, maskAlpha);

	delete [] lefttopMask;
	delete [] leftbottomMask;
	delete [] righttopMask;
	delete [] rightbottomMask;
	delete [] lookupSQR;
}

void	Lomo(TiBitmapData& bitmap)
{

	//����ɫ��ƽ�⣬����ͼƬ����Ʊ���
	BalanceColor(bitmap,-80,0,-60,TINYIMAGE_TRANSFERMODE_MIDTONES,true);
	
	//����ɫ�ף�ʹ��ͼƬ�䰵
	AdjustLevels(bitmap,27,255,0.96,TINYIMAGE_CHANEL_RGB);

	//��Ӱ���
	DarkenCorner(bitmap);

}

}