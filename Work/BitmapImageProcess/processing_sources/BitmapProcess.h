/////** 
////*description   : ��Ʈ�� ������ ó���ϴ� ��ü ���� �������
////*               
////* 
////*/
#pragma once

#ifndef _BASICBONE_H_
#include "basicbone.h"
#endif //_BASICBONE_H_

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif //_USERMACHRO_H_

#ifndef _USER_RGBQUAD_H_
#include "UserRGBQuad.h"
#endif //_USER_RGBQUAD_H_

#ifndef _USERBITMAP_H_
#include "UserBitmap.h"
#endif //_USERBITMAP_H_ 

#include "ColorConv.h"
#include "BlobColoring.h"
#include "RGBToHSI.h"
#include "RGBToGray.h"
#include "ColorEmbossing.h"
#include "RGBSharpening.h"
#include "ChannelsplitRgb.h"
#include "ActBlobcoloring.h"
#include "BitmapIO.h"
#include "BitmapClipBoard.h"
#include "CDLG_DYNBIN.h"
#include "SobelImage.h"

///** 
//*description   : ��Ʈ�� ������ ó���ϴ� ��ü
//*@parent class : private CBasicBone : ���� ������, ���� ������ ȣ�� ������
//*/
class CBitmapProcess :  private CBasicBone
{
//// ��� ���� ���� �κ�
public:

	CUserRGBQuad	m_cuserRGBQuad;

	CUserBitmap		m_cbmpNodeIn;

protected:

private:

//// ��� �Լ� ���� �κ�
public:

	///**
	//*description   : ��Ʈ�� ������ ó���ϴ� ��ü�� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapProcess(void);

	///**
	//*description   : ��Ʈ�� ������ ó���ϴ� ��ü�� �Ҹ���
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	~CBitmapProcess(void);

	///**
	//*description   : ��Ʈ�� �̹��� ó�� ��� ��ü ���� �����Ҵ� �޸� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void Clear(void);

	///**
	//*description   : ��Ʈ�� �̹��� ó�� ��� ��ü ���� ���� �ʱ�ȭ
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void Initialize(void);

	///**
	//*description   : ���ο� User Image ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : ������ ���࿩��(true:������,false:������)
	//*/
	bool NewDocument(void);

	///**
	//*description   : ���Ϸκ��� ��Ʈ�� �о��
	//*@param input  : LPCTSTR lpszPathName					���� ��θ�
	//*@param input  :  
	//*@param output :  
	//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
	//*/
	bool OpenImageFromFile(LPCTSTR lpszPathName);

	///**
	//*description   : ��Ʈ���� ���Ϸ� ����
	//*@param input  : LPCTSTR lpszPathName	���� ��θ�
	//*@param input  : SmallUserBitmap& smallUserBitmap
	//*@param input  : RGBQUAD*	palRGB
	//*@param output : -
	//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
	//*/
	bool SaveImageToFile(LPCTSTR lpszPathName);

	//*description   : 
	//*@param input  : int nFlag
	//*@param output : -
	//*@return		 : 
	//*/
	const size_t GetImageWidth(void) const;

	//*description   : 
	//*@param input  : int nFlag
	//*@param output : -
	//*@return		 :  
	//*/
	const size_t GetImageHeight(void) const;

	//*description   : 
	//*@param input  : int nFlag
	//*@param output : -
	//*@return		 :  
	//*/
	const int GetImageBitCount(void) const;

	//*description   : 
	//*@param input  : int nFlag
	//*@param output : -
	//*@return		 :  
	//*/
	const int GetImageRwSize(void) const;

	//*description   : User Image�� ������ ������ ȭ�� ���
	//*@param input  : CDC* pDC					����� DC ������
	//*@param output : -
	//*@return		 : ������ ���࿩��(true:������,false:������)
	//*/
	bool DrawImage(CDC* pDC);

	//*description   : 
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void GetImageSize(CSize& csSizeImage) const;

	//*description   : Ŭ������� �����ϱ�
	//*@param input  : -
	//*@param output : -
	//*@return		 :  
	//*/
	void  CopyClipboard(void);

	//*description   : 
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void ChannelsplitRgb(void);

	//*description   : 
	//*@param input  :  
	//*@param input  :   
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void RGB2HSI(void);

	//*description   : 
	//*@param input  :  
	//*@param input  :   
	//*@param input  :
	//*@param input  : 
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void RGB2Gray(void);

	//*description   : 
	//*@param input  :  
	//*@param input  :  
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void ColorEmbossing(void);

	//*description   : 
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param input  :
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void RGBShapening(void);

	//*description   : 
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param input  :
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	void Blobcoloring(CClientDC* pDc);

	//*description   : 
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param input  :
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	bool OnImgDynbinSet(CDLG_DYNBIN* pDlg);

	//*description   : 
	//*@param input  :  
	//*@param input  :  
	//*@param input  : 
	//*@param input  :
	//*@param input  : 
	//*@param output : -
	//*@return		 :  
	//*/
	bool OnImgDynbinGet(CDLG_DYNBIN* pDlg);

	//*description   :  
	//*@param input  : -
	//*@param output : -
	//*@return		 :  
	//*/
	void OnRgbSobel(void);

protected:
	
private:


};

