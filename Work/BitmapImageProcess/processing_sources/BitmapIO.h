/////** 
////*description   : 
////* 
////*/
#ifndef _BITMAPIO_H_
#define _BITMAPIO_H_
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
class CBitmapIO : private CBasicBone
{
//// ��� ���� ���� �κ�
public:

protected:

private:

//// ��� �Լ� ���� �κ�
public:

	///**
	//*description   : ���Ϸκ��� ��Ʈ�� �о��
	//*@param input  : LPCTSTR lpszPathName					���� ��θ�
	//*@param input  :  
	//*@param output :  
	//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
	//*/
	bool Open(LPCTSTR lpszPathName, CUserBitmap& bmpNode, RGBQUAD* palRGB = NULL);

	///**
	//*description   : ��Ʈ���� ���Ϸ� ����
	//*@param input  : LPCTSTR lpszPathName	���� ��θ�
	//*@param input  : SmallUserBitmap& smallUserBitmap
	//*@param input  : RGBQUAD*	palRGB
	//*@param output : -
	//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
	//*/
	bool Save(LPCTSTR lpszPathName, CUserBitmap& bmpNode, RGBQUAD* palRGB = NULL);

protected:

	///**
	//*description   : Ȯ���� �ٿ���
	//*@param input  : CString lpszPathName	���� ��θ�
	//*@param input  : 
	//*@param input  : 
	//*@param output : -
	//*@return		 : ��θ�
	//*/
	CString AddExtendString(CString lpszPathName);

private:

};
#endif //_BITMAPIO_H_