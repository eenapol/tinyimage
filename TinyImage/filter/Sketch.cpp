#include "filter/Sketch.h"
#include "filter/Grayscale.h"
#include "filter/GaussBlur.h"
#include "filter/Invert.h"
#include "base/BlendMode.h"



namespace TinyImage{

void	Sketch(TiBitmapData& bitmap)
{
	//�ҶȻ�ԭͼ
	GrayScale(bitmap);

	//�����ҶȻ����ԭͼ������
	TiBitmapData* clone = bitmap.Clone();
	Invert(*clone);

	//�Կ���ͼ����˹ģ��
	GaussianBlur(*clone,22);



	//��ɫ����
	BlendMode(bitmap,TINYIMAGE_CHANEL_RGB,*clone,TINYIMAGE_CHANEL_RGB,
			  TINYIMAGE_BLENDMODE_COLORDODGE,1.0);

	delete clone;
}

}