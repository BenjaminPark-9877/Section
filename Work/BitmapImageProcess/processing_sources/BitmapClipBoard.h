#pragma once

#include <winnt.h>

#ifndef _BASICBONE_H_
#include "basicbone.h"
#endif //_BASICBONE_H_

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif //_USERMACHRO_H_

#ifndef _USER_RGBQUAD_H_
#include "UserRGBQuad.h"
#endif //_USER_RGBQUAD_H_

#ifndef _BITMAPFILEHEADER_H_
#include "BitmapFileHeader.h"
#endif //_BITMAPFILEHEADER_H_

#ifndef _USERBITMAP_H_
#include "UserBitmap.h"
#endif //_USERBITMAP_H_

///** 
//*description   :  
//*@parent class : private CBasicBone : ���� ������, ���� ������ ȣ�� ������
//*/
class CBitmapClipBoard : private CBasicBone
{
//// ��� ���� ���� �κ�
public:

protected:

private:

//// ��� �Լ� ���� �κ�
public:

	///**
	//*description   : ���ο� User Image ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : ������ ���࿩��(true:������,false:������)
	//*/
	bool NewDocument(CUserBitmap& cbmpNodeIn, CUserRGBQuad&	cUserRGBQuad);

	//*description   : Ŭ������� �����ϱ�(nFlag�� �⺻������ FLAG_SELECT_INPUT ��, �Է� ���� �̹����� ������)
	//*@param input  : unsigned char	*m_CpyImg
	//*@param input  : int				height
	//*@param input  : int				width
	//*@param input  : int				biBitCount 
	//*@param input  : int				nFlag
	//*@param output : -
	//*@return		 :  
	//*/
	void CopyClipboard(const CUserBitmap& cbmpNodeIn, CUserRGBQuad& cUserRGBQuad);

protected:

	///**
	//*description   : ��Ʈ�� ���� ä���
	//*@param input  : LPSTR pDIB 
	//*@param output : CBitmapNode& bmpNode
	//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
	//*/
	bool OpenImageFromClipBoard(LPSTR pDIB, CUserBitmap& bmpNode);

	//*description   : Ŭ������� �����ϱ�(nFlag�� �⺻������ FLAG_SELECT_INPUT ��, �Է� ���� �̹����� ������)
	//*@param input  : unsigned char	*m_CpyImg
	//*@param input  : int				height
	//*@param input  : int				width
	//*@param input  : int				biBitCount 
	//*@param input  : int				nFlag
	//*@param output : -
	//*@return		 :  
	//*/
	void CopyClipboard(const unsigned char* m_CpyImg, int height, int width, int biBitCount, const BITMAPINFOHEADER& dibHi, CUserRGBQuad& cUserRGBQuad);

private:

};

