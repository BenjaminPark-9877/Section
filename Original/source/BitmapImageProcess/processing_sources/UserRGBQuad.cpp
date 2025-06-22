/////** 
////*description   : RGBQUAD �� ���� ��ü ���� �ҽ� ���� 
////*               
////* 
////*/
#include "pch.h"
#include "UserRGBQuad.h"

///**
//*description   :  RGBQUAD �� ���� ��ü�� ������
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CUserRGBQuad::CUserRGBQuad(void)
{
	Initialize();
}

///**
//*description   : RGBQUAD �� ���� ��ü�� �Ҹ���
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CUserRGBQuad::~CUserRGBQuad(void)
{
	Clear();
}

///**
//*description   :  RGBQUAD �� ���� ��ü �ʱ�ȭ
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
void CUserRGBQuad::Initialize(void)
{
	Clear();

	RGBQUAD rgbElement;
	memset(&rgbElement, 0, sizeof(RGBQUAD));

	for(int i=0; i<MAXIMUM_PIXEL_VALUE; i++) 
	{
		rgbElement.rgbBlue		= i;
		rgbElement.rgbGreen		= i;
		rgbElement.rgbRed	    = i;
		rgbElement.rgbReserved	= 0;

		m_vecPalRGB.push_back(rgbElement);
	}
}

///**
//*description   : RGBQUAD �� �Ҵ��ϱ�
//*@param input  : LPSTR pDIB
//*@param output : -
//*@return		 : ���� ���� ����(true : ���� ����, false : ���� �߻�)
//*/
bool CUserRGBQuad::Set(LPSTR pDIB)
{
	if (pDIB == NULL)
	{
		return false;
	}
	
	Clear();

	memcpy(m_vecPalRGB.data(), pDIB, sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE);

	return true;
}

///**
//*description   : RGBQUAD �� �Ҵ��ϱ�
//*@param input  : const CUserRGBQuad& rhs
//*@param output : -
//*@return		 : ���� ���� ����(true : ���� ����, false : ���� �߻�)
//*/
bool CUserRGBQuad::Set(const CUserRGBQuad& rhs)
{
	if (this == &rhs)
	{
		return false;
	}

	if (rhs.m_vecPalRGB.empty() == true)
	{
		return false;
	}

	Clear();

	for (int i = 0; i < MAXIMUM_PIXEL_VALUE; i++)
	{
		m_vecPalRGB.push_back(rhs.m_vecPalRGB[i]);
	}

	return true;
}

///**
//*description   : RGBQUAD �� �޾ƿ���(�Լ� ���ڵ����� ���� ���)
//*@param input  : - 
//*@param output : CUserRGBQuad& rhs
//*@return		 : ���� ���� ����(true : ���� ����, false : ���� �߻�)
//*/
bool CUserRGBQuad::Get(CUserRGBQuad& rhs)
{
	if (this == &rhs)
	{
		return false;
	}

	if (m_vecPalRGB.empty() == true)
	{
		return false;
	}

	rhs.Clear();

	for (int i = 0; i < MAXIMUM_PIXEL_VALUE; i++)
	{
		rhs.m_vecPalRGB.push_back(m_vecPalRGB[i]);
	}

	return true;
}

///**
//*description   : RGBQUAD �� �޾ƿ���
//*@param input  : LPSTR pDIB
//*@param output : -
//*@return		 : ���� ���� ����(true : ���� ����, false : ���� �߻�)
//*/
bool  CUserRGBQuad::Get(LPSTR pDIB)
{
	if (pDIB == NULL)
	{
		return false;
	}

	memcpy(pDIB, m_vecPalRGB.data(), sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE);

	return true;
}


///**
//*description   : ÷�� ������ ������ ( L-value ���� )
//*@param input  : const size_t& nPos	: ��ġ
//*@return		 : �ش� ��ġ�� ��
//*/
RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos) 
{ 
	if (nPos <= 0)
	{
		return m_vecPalRGB[0];
	}

	if (nPos >= m_vecPalRGB.size() )
	{
		return m_vecPalRGB[(m_vecPalRGB.size() - 1)];
	}

	return m_vecPalRGB[nPos];
}

///**
//*description   : ÷�� ������ ������ const type ( R-value ���� )
//*@param input  : const size_t& nPos : ��ġ
//*@return		 : �ش� ��ġ�� ��
//*/
const RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos) const
{
	if (nPos <= 0)
	{
		return m_vecPalRGB[0];
	}

	if (nPos >= m_vecPalRGB.size())
	{
		return m_vecPalRGB[(m_vecPalRGB.size() - 1)];
	}

	return m_vecPalRGB[nPos];
}