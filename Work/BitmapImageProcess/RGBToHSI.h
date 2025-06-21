/////** 
////*description   : ��Ʈ�� ���� �޾Ƽ� RGB To HSI �۾� ���� Ŭ���� ���� ��� ����
////*               
////* 
////*/
#ifndef _RGBTOHSI_H_
#define _RGBTOHSI_H_

#pragma once

#include "BitmapAction.h"

///** 
//*description   : ��Ʈ�� ���� �޾Ƽ� RGB To HSI �۾� ���� Ŭ����
//*@parent class : public CBitmapAction  
//*/
class CRGBToHSI : public CBitmapAction
{
	//// ��� ���� ���� �κ�
public:

protected:

private:

	//// ��� �Լ� ���� �κ�
public:

	//*description   : RGB -> HSI �������� ��ȯ �� ���� (�����ε�: ���� ����)
	inline void Process(const CUserBitmap& pCbmpElementsIn) { Process(&pCbmpElementsIn); }

	//*description   : RGB -> HSI �������� ��ȯ �� ����
	void Process(const CUserBitmap* pCbmpElementsIn);

protected:

	//*description   : RGB �̹����κ��� HSI ��ȯ
	bool RGB2HSI(const unsigned char* InImg, unsigned char* OutImg, int height, int width);

	//*description   : �ϳ��� ���� ä�ξ� ���� ���
	bool SpiltOneColorImage(const CUserBitmap& bitmapNode, int nType = THREE_COLOR_TYPE);

private:

};

#endif //_RGBTOHSI_H_