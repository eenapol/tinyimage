#include "base/Brightness.h"
#include "base/BlendMode.h"
#include "filter/GaussBlur.h"
#include "filter/SoftGlow.h"

namespace TinyImage{

void	SoftGlow(TiBitmapData& bitmap)
{
	TiBitmapData* clone = bitmap.Clone();

	//��˹ģ��
	GaussianBlur(*clone,5);
	
	//�ײ�ͼ�������������
	AdjustBrightness(bitmap,0.05);

	//����ͼ������ɫ���
	BlendMode(bitmap,TINYIMAGE_CHANEL_RGB,*clone,TINYIMAGE_CHANEL_RGB,
			   TINYIMAGE_BLENDMODE_SCREEN,1);

	delete clone;
}

}