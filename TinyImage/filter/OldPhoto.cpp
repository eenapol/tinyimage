#include "filter/Grayscale.h"
#include "base/ColorBalance.h"


namespace TinyImage{

void	OldPhoto(TiBitmapData& bitmap)
{
	//�ҶȻ�
	GrayScale(bitmap);

	//��Ӻ�ɫͨ�� ������ɫͨ�� ʹ��ͼƬ����
	BalanceColor(bitmap,34,0,-87,TINYIMAGE_TRANSFERMODE_MIDTONES,false);
	
}

}