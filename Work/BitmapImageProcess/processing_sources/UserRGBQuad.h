/////** 
////*description   : RGBQUAD �� ���� ��ü ���� ��� ���� 
////*               
////* 
////*/
#ifndef _USER_RGBQUAD_H_
#define _USER_RGBQUAD_H_
#pragma once

#ifndef _BASICBONE_H_
#include "basicbone.h"
#endif //_BASICBONE_H_

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif //_USERMACHRO_H_

using namespace std;

///** 
//*description   : RGBQUAD �� ���� ��ü 
//*@parent class : private CBasicBone : ���� ������, ���� ������ ȣ�� ������
//*/
class CUserRGBQuad :private CBasicBone
{
//// ��� ���� ���� �κ�
public:

protected:
	//RGBQUAD		m_PalRGB[MAXIMUM_PIXEL_VALUE];
	vector<RGBQUAD>		m_vecPalRGB;

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
	//*description   : RGBQUAD ���� ������� Ȯ���ϴ� �Լ�
	//*@param input  : -
	//*@param output : -
	//*@return		 : ����ִ��� ���� Ȯ�� �� ( true : �������, false : ���� ���� )
	//*/
	inline bool IsEmpty(void) { return m_vecPalRGB.empty(); }

	///**
	//*description   :  RGBQUAD �� ���� ��ü �ʱ�ȭ
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void Initialize(void);

	///**
	//*description   : ��ü �޸� ���� �� ���� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline void Clear(void) { m_vecPalRGB.clear(); }

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

	///**
	//*description   : RGBQUAD �� �Ҵ��ϱ�
	//*@param input  : LPSTR* pDIB
	//*@param output : -
	//*@return		 : ���� ���� ����(true : ���� ����, false : ���� �߻�)
	//*/
	bool Set(LPSTR pDIB);

	///**
	//*description   : RGBQUAD �� �Ҵ��ϱ�
	//*@param input  : const CUserRGBQuad& rhs
	//*@param output : -
	//*@return		 : ���� ���� ����(true : ���� ����, false : ���� �߻�)
	//*/
	bool Set(const CUserRGBQuad& rhs);

	///**
	//*description   : RGBQUAD �� �޾ƿ���(�Լ� ���ڵ����� ���� ���)
	//*@param input  :   
	//*@return		 : c ������ �迭 �ּ�
	//*/
	inline RGBQUAD* Get(void) { return m_vecPalRGB.data(); }

	///**
	//*description   : RGBQUAD �� �޾ƿ���(�Լ� ���ڵ����� ���� ���)
	//*@param input  : - 
	//*@param output : CUserRGBQuad& rhs
	//*@return		 : ���� ���� ����(true : ���� ����, false : ���� �߻�)
	//*/
	bool Get(CUserRGBQuad& rhs);

	///**
	//*description   : RGBQUAD �� �޾ƿ���
	//*@param input  : LPSTR* pDIB
	//*@param output : -
	//*@return		 : ���� ���� ����(true : ���� ����, false : ���� �߻�)
	//*/
	bool Get(LPSTR pDIB);

private:

};
#endif //_USER_RGBQUAD_H_