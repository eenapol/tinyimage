/**
 * @file    ColorBalance.h
 * @brief   ɫ��ƽ��
 * @author  xiangwangfeng <xiangwangfeng@gmail.com>
 * @since   2011-1
 * @website www.xiangwangfeng.com
 */


#pragma once
#include "global/BitmapData.h"

namespace TinyImage{

//��������
void BalanceColor(TiBitmapData& bitmap,int cyan, int magenta, int yellow,
		TINYIMAGE_TRANSFERMODE mode,bool preserveLuminosity);

//˽�з���
void InitTransferArray();//��ʼ��ת��������

}