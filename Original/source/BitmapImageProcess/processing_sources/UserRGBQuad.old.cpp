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
#ifdef DEBUG
	TRACE("CUserRGBQuad::CUserRGBQuad(void)  \n");
#endif //DEBUG

	Initialize();

#ifdef DEBUG
	TRACE("CUserRGBQuad::CUserRGBQuad(void)  \n");
#endif //DEBUG
}

///**
//*description   : RGBQUAD �� ���� ��ü�� �Ҹ���
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CUserRGBQuad::~CUserRGBQuad(void)
{
#ifdef DEBUG
	TRACE("CUserRGBQuad::~CUserRGBQuad(void)  \n");
#endif //DEBUG


#ifdef DEBUG
	TRACE("CUserRGBQuad::~CUserRGBQuad(void)  \n");
#endif //DEBUG
}

///**
//*description   :  RGBQUAD �� ���� ��ü �ʱ�ȭ
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
void CUserRGBQuad::Initialize(void)
{
#ifdef DEBUG
	TRACE("void CUserRGBQuad::Initialize(void)  \n");
#endif //DEBUG

	memset(m_PalRGB,0,MAXIMUM_PIXEL_VALUE*sizeof(RGBQUAD));

	for(int i=0; i<MAXIMUM_PIXEL_VALUE; i++) 
	{
		m_PalRGB[i].rgbBlue     = i;
		m_PalRGB[i].rgbGreen    = i;
		m_PalRGB[i].rgbRed	    = i;
		m_PalRGB[i].rgbReserved = 0;
	}

#ifdef DEBUG
	TRACE("void CUserRGBQuad::Initialize(void)  \n");
#endif //DEBUG
}

///**
//*description   : ÷�� ������ ������ ( L-value ���� )
//*@param input  : const size_t& nPos	: ��ġ
//*@return		 : �ش� ��ġ�� ��
//*/
RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos) 
{ 
#ifdef DEBUG
	TRACE("RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos)  \n");
#endif //DEBUG

	if (nPos <= 0)
	{
#ifdef DEBUG
		TRACE("if (nPos <= 0) at RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos)  \n");
#endif //DEBUG
		return m_PalRGB[0];
	}

	if (nPos >= MAXIMUM_PIXEL_VALUE)
	{
#ifdef DEBUG
		TRACE("if (nPos >= MAXIMUM_PIXEL_VALUE) at RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos)  \n");
#endif //DEBUG
		return m_PalRGB[(MAXIMUM_PIXEL_VALUE-1)];
	}

#ifdef DEBUG
	TRACE("RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos)  \n");
#endif //DEBUG
	return m_PalRGB[nPos]; 
}

///**
//*description   : ÷�� ������ ������ const type ( R-value ���� )
//*@param input  : const size_t& nPos : ��ġ
//*@return		 : �ش� ��ġ�� ��
//*/
const RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos) const
{
#ifdef DEBUG
	TRACE("const RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos) const  \n");
#endif //DEBUG

	if (nPos <= 0)
	{
#ifdef DEBUG
		TRACE("if (nPos <= 0) at const RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos) const  \n");
#endif //DEBUG
		return m_PalRGB[0];
	}

	if (nPos >= MAXIMUM_PIXEL_VALUE)
	{
#ifdef DEBUG
		TRACE("if (nPos >= MAXIMUM_PIXEL_VALUE) at const RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos) const  \n");
#endif //DEBUG
		return m_PalRGB[(MAXIMUM_PIXEL_VALUE - 1)];
	}

#ifdef DEBUG
	TRACE("const RGBQUAD& CUserRGBQuad::operator[](const size_t& nPos) const  \n");
#endif //DEBUG
	return m_PalRGB[nPos];
}