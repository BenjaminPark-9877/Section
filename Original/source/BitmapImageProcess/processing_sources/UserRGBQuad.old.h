/////** 
////*description   : RGBQUAD �� ���� ��ü ���� ��� ���� 
////*               
////* 
////*/
#ifndef _USER_RGBQUAD_H_
#define _USER_RGBQUAD_H_
#pragma once

#include <wingdi.h>
#include <vcruntime_string.h>

#ifndef _BASICBONE_H_
#include "basicbone.h"
#endif //_BASICBONE_H_

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif //_USERMACHRO_H_

///** 
//*description   : RGBQUAD �� ���� ��ü 
//*@parent class : private CBasicBone : ���� ������, ���� ������ ȣ�� ������
//*/
class CUserRGBQuad :private CBasicBone
{
//// ��� ���� ���� �κ�
public:
	RGBQUAD		m_PalRGB[MAXIMUM_PIXEL_VALUE];

private:

//// ��� �Լ� ���� �κ�
public:

	///**
	//*description   :  RGBQUAD �� ���� ��ü�� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CUserRGBQuad(void);

	///**
	//*description   : RGBQUAD �� ���� ��ü�� �Ҹ���
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	~CUserRGBQuad(void);

	///**
	//*description   :  RGBQUAD �� ���� ��ü �ʱ�ȭ
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void Initialize(void);

	///**
	//*description   : c ������ �迭�� �ǵ�����
	//*@param input  :   
	//*@return		 : c ������ �迭 �ּ�
	//*/
	RGBQUAD* c_arr(void) { return m_PalRGB; }

	///**
	//*description   : ÷�� ������ ������ ( L-value ���� )
	//*@param input  : const size_t& nPos	: ��ġ
	//*@return		 : �ش� ��ġ�� ��
	//*/
	RGBQUAD& operator[](const size_t& nPos);

	///**
	//*description   : ÷�� ������ ������ const type ( R-value ���� )
	//*@param input  : const size_t& nPos : ��ġ
	//*@return		 : �ش� ��ġ�� ��
	//*/
	const RGBQUAD& operator[](const size_t& nPos) const;

private:

};
#endif //_USER_RGBQUAD_H_