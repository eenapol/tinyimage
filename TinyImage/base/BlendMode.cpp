#include "base/BlendMode.h"
#include <cmath>

namespace TinyImage{

void	BlendMode(TiBitmapData& srcBitmap,TINYIMAGE_CHANNEL srcChannel,
				  TiBitmapData& blendBitmap,TINYIMAGE_CHANNEL blendChannel,
				  TINYIMAGE_BLENDMODE mode,double opacity)
{
	int width		= srcBitmap.GetWidth();
	int height		= srcBitmap.GetHeight();
	int bpp			= srcBitmap.GetBpp();
	int blendWidth	= blendBitmap.GetWidth();
	int blendHeight	= blendBitmap.GetHeight();
	int blendBpp	= blendBitmap.GetBpp();

	TINYIMAGE_ASSERT_VOID(width == blendWidth);
	TINYIMAGE_ASSERT_VOID(height == blendHeight);
	TINYIMAGE_ASSERT_VOID(bpp == blendBpp);
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	//����Lookup Table
	u8 lookupTable[256][256];
	GenerateLookupTable(lookupTable,mode,opacity);

	//���е���
	AdjustBlendModeCurve(srcBitmap,srcChannel,blendBitmap,blendChannel,lookupTable);
}


void	GenerateLookupTable(u8 (&lookup)[256][256],TINYIMAGE_BLENDMODE mode,double opacity)
{
	//��ʼ��LookupTableĬ��ֵ
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0 ; j < 256; j++)
		{
			lookup[i][j] = (u8)i;
		}
	}

	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	switch(mode)
	{
	case TINYIMAGE_BLENDMODE_DARKEN:
		GLT_Darken(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_LIGHTEN:
		GLT_Lighten(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_MULTIPLY:
		GLT_Multiply(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_SCREEN:
		GLT_Screen(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_COLORDODGE:
		GLT_ColorDodge(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_COLORBURN:
		GLT_ColorBurn(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_LINEARDODGE:
		GLT_LinearDodge(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_LINEARBURN:
		GLT_LinearBurn(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_OVERLAY:
		GLT_Overlay(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_HARDLIGHT:
		GLT_HardLight(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_SOFTLIGHT:
		GLT_SoftLight(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_VIVIDLIGHT:
		GLT_VividLight(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_LINEARLIGHT:
		GLT_LinearLight(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_PINLIGHT:
		GLT_PinLight(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_HARDMIX:
		GLT_HardMix(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_ADD:
		GLT_Add(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_SUB:
		GLT_Sub(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_DIFFERENCE:
		GLT_Difference(lookup,opacity);
		break;
	case TINYIMAGE_BLENDMODE_EXCLUSION:
		GLT_Exclusion(lookup,opacity);
		break;
	default:
		assert(false);
		break;
	}

}

int		ConvertRGBIndex(TINYIMAGE_CHANNEL channel)
{
	int rgbIndex = 0;
	switch(channel)
	{
	case TINYIMAGE_CHANEL_R:
		rgbIndex = TiRed;
		break;
	case TINYIMAGE_CHANEL_G:
		rgbIndex = TiGreen;
		break;
	case TINYIMAGE_CHANEL_B:
		rgbIndex = TiBlue;
		break;
	default:
		assert(false);
		break;
	}

	return rgbIndex;
}

void	AdjustBlendModeCurve(TiBitmapData& srcBitmap,TINYIMAGE_CHANNEL srcChannel,
							 TiBitmapData& blendBitmap,TINYIMAGE_CHANNEL blendChannel,
							u8 (&lookup)[256][256])
{

	int width		= srcBitmap.GetWidth();
	int height		= srcBitmap.GetHeight();
	int bpp			= srcBitmap.GetBpp();
	u8* srcBmp		= srcBitmap.GetBmpData();
	int stride		= srcBitmap.GetStride();
	int blendWidth	= blendBitmap.GetWidth();
	int blendHeight	= blendBitmap.GetHeight();
	int blendBpp	= blendBitmap.GetBpp();
	u8*	blendBmp	= blendBitmap.GetBmpData();
	int offset	= stride - width * bpp;

	TINYIMAGE_ASSERT_VOID(width == blendWidth);
	TINYIMAGE_ASSERT_VOID(height == blendHeight);
	TINYIMAGE_ASSERT_VOID(bpp == blendBpp);


	if (srcChannel == TINYIMAGE_CHANEL_RGB ||blendChannel == TINYIMAGE_CHANEL_RGB)
	{
		if (srcChannel == TINYIMAGE_CHANEL_RGB && blendChannel == TINYIMAGE_CHANEL_RGB)	//�����������ȫͨ��
		{
			for (int i = 0; i < height; i ++)
			{
				for (int j = 0; j < width; j++)
				{
					srcBmp[TiRed] = lookup[srcBmp[TiRed]][blendBmp[TiRed]];
					srcBmp[TiGreen] = lookup[srcBmp[TiGreen]][blendBmp[TiGreen]];
					srcBmp[TiBlue] = lookup[srcBmp[TiBlue]][blendBmp[TiBlue]];
					srcBmp	+= bpp;
					blendBmp+= bpp;
				}
				srcBmp  += offset;
				blendBmp+= offset;
			}
		}
		else if (srcChannel == TINYIMAGE_CHANEL_RGB)	//���ֻ�е�ͼ��ȫͨ��
		{
			int blendPixel	= ConvertRGBIndex(blendChannel);

			for (int i = 0; i < height; i ++)
			{
				for (int j = 0; j < width; j++)
				{
					srcBmp[TiRed]	= lookup[srcBmp[TiRed]][blendBmp[blendPixel]];
					srcBmp[TiGreen] = lookup[srcBmp[TiGreen]][blendBmp[blendPixel]];
					srcBmp[TiBlue]	= lookup[srcBmp[TiBlue]][blendBmp[blendPixel]];

					srcBmp	+= bpp;
					blendBmp+= bpp;
				}
				srcBmp  += offset;
				blendBmp+= offset;
			}
			
		}
		else	//���ֻ���ϲ�ͼ����ȫͨ��
		{
			int srcPixel	= ConvertRGBIndex(srcChannel);

			for (int i = 0; i < height; i ++)
			{
				for (int j = 0; j < width; j++)
				{
					srcBmp[TiRed]	= lookup[srcBmp[srcPixel]][blendBmp[TiRed]];
					srcBmp[TiGreen] = lookup[srcBmp[srcPixel]][blendBmp[TiGreen]];
					srcBmp[TiBlue]	= lookup[srcBmp[srcPixel]][blendBmp[TiBlue]];

					srcBmp	+= bpp;
					blendBmp+= bpp;
				}
				srcBmp  += offset;
				blendBmp+= offset;
			}

		}
	}
	else//����������ǵ�ͨ�� 
	{
		int srcPixel	= ConvertRGBIndex(srcChannel);
		int blendPixel	= ConvertRGBIndex(blendChannel);
		
		for (int i = 0; i < height; i ++)
			{
				for (int j = 0; j < width; j++)
				{
					srcBmp[srcPixel]	= lookup[srcBmp[srcPixel]][blendBmp[blendPixel]];
				
					srcBmp	+= bpp;
					blendBmp+= bpp;
				}
				srcBmp  += offset;
				blendBmp+= offset;
			}
	}

}


//�䰵
void	GLT_Darken(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + MIN(i,j) * opacity);
		}
	}
}

//����
void	GLT_Lighten(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + MAX(i,j) * opacity);
		}
	}
}

//��Ƭ����
void	GLT_Multiply(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + i * j / 255 * opacity);
		}
	}
}

//��ɫ
void	GLT_Screen(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + (255 - (255 - i) * (255 - j) / 255) * opacity);
		}
	}
}

//ɫ�ʼ���
void	GLT_ColorDodge(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 255; j++)
		{
			lookup[i][j] = (u8)(i * (1-opacity) + MIN( i * 255 / (255 - j),255) * opacity);
		}
	}
	double mixColor = 255 * opacity;
	for (int i = 0; i < 256; i++)
	{
		lookup[i][255] = (u8)(i * (1-opacity) + mixColor);
	}
}

//ɫ�ʼ���
void	GLT_ColorBurn(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + CLAMP0255(255 - 255.0 * (255- i) / j) * opacity);
		}
	}
}

//���Լ���
void	GLT_LinearDodge(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + MIN( i + j, 255) * opacity);
		}
	}
}

//���Լ���
void	GLT_LinearBurn(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) +  MAX(i + j - 255,0) * opacity);
		}
	}
}

//����
void	GLT_Overlay(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	//С�ڵ��� 1/2
	for (int i = 0; i <= 128; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + 2 * i * j / 255.0 * opacity );
		}
	}
	
	//����1/2
	for (int i = 129; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + ( 255 - CLAMP0255(2 * (255 - i) * (255 - j) / 255 ))* opacity );
		}
	}


}

//ǿ��
void	GLT_HardLight(u8 (&lookup)[256][256],double opacity)
{
	
	for (int i = 0; i < 256; i++)
	{
		//С�ڵ��� 1/2
		for (int j = 0; j <= 128; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + 2 * i * j / 255.0 * opacity );
		}

		//����1/2
		for (int j = 129; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + ( 255 - 2 * (255 - i) * (255 - j) / 255 )* opacity );
		}
	}


}

//���
void	GLT_SoftLight(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		//С�ڵ��� 1/2
		for (int j = 0; j <= 128; j++)
		{
			double result = i + (2 * j / 255.0 - 1) * (i / 255.0 - i * i / 65025.0) * 255.0;
			lookup[i][j] = (u8)( i * (1-opacity) + result * opacity );
		}

		//����1/2
		for (int j = 129; j < 256; j++)
		{
			double result = i + ( 2 * j / 255.0 - 1) * (sqrt(i / 255.0) - i / 255.0) * 255.0;
			lookup[i][j] = (u8)( i * (1-opacity) + result * opacity );
		}
	}
}

//����
void	GLT_VividLight(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		//С�ڵ��� 1/2
		for (int j = 0; j <= 128; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) + ( 255 - CLAMP0255(255.0* (1 - i / 255.0) /  (2 * j / 255.0)) ) * opacity );
		}

		//����1/2
		for (int j = 129; j < 255; j++)
		{
			
			lookup[i][j] = (u8)( i * (1-opacity) + CLAMP0255( 255 * i / (510 - 2 * j)) * opacity );
		}

		//����ֵ����
		lookup[i][255] = (u8)( i * (1-opacity) + 255 * opacity );
	}
}

//���Թ�
void	GLT_LinearLight(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) +  CLAMP0255( i + 2 * j - 255 ) * opacity);
		}
	}
}

//���
void	GLT_PinLight(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int result;
			if (i < 2 * j - 255)
			{
				result = 2 * j - 255;
			}
			else if (i > 2 * j - 255 && i < 2 * j)
			{
				result = i;
			}
			else
			{
				result = 2 * j;
			}

			lookup[i][j] = (u8)( i * (1-opacity) +  result * opacity);
		}
	}
}

//ʵ���
void	GLT_HardMix(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int result;
			if (i + j < 255)
			{
				result = 0;
			}
			else
			{
				result = 255;
			}

			lookup[i][j] = (u8)( i * (1-opacity) +  result * opacity);
		}
	}
}

//���
void	GLT_Add(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) +  MIN(i + j, 255) * opacity);
		}
	}
}

//���
void	GLT_Sub(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) +  MAX(0,j - i) * opacity);
		}
	}
}

//���
void	GLT_Difference(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) +  abs(i - j) * opacity);
		}
	}
}

//�ų�
void	GLT_Exclusion(u8 (&lookup)[256][256],double opacity)
{
	TINYIMAGE_ASSERT_VOID(opacity >= 0 && opacity <= 1.0);

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			lookup[i][j] = (u8)( i * (1-opacity) +  ( i + j -  2 * i * j / 255)* opacity);
		}
	}
}



}