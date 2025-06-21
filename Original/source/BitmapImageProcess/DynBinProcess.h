/////** 
////*description   : ���� ����ȭ�� ó���ϴ� ��ü ���� �������
////*               
////* 
////*/
#ifndef _DYNBINPROCESS_H_
#define _DYNBINPROCESS_H_

#pragma once
#include <winnt.h>
#include <wingdi.h>
#include <vcruntime_string.h>
#include <windef.h>
#include <tchar.h>
#include <afx.h>

#include "BlobColoring.h"
#include "ColorConv.h"

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

///** 
//*description   : ���� ����ȭ ó���ϴ� ��ü
//*@parent class : private CBasicBone : ���� ������, ���� ������ ȣ�� ������
//*/
class CDynBinProcess : private CBasicBone
{
	//// ��� ���� ���� �κ�
public:

protected:
	int				m_nThresValueDisp;
	CUserBitmap		m_bmpDynBinIn;
	CUserBitmap		m_bmpDynBinOut;

private:

	///// ��� �Լ� ���� �κ�
public:
	///**
	//*description   : ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CDynBinProcess(void);

	///**
	//*description   : �Ҹ���
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	~CDynBinProcess(void);

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline void SetThreshValueDisp(const int nThresValueDisp) { m_nThresValueDisp = nThresValueDisp; }

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline const int GetThreshValueDisp(void) const { return m_nThresValueDisp; }

	///**
	//*description   : ���� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void Clear(void);

	///**
	//*description   : ��ȭ���� �ʱ�ȭ �� ó���� ����
	//*@param input  : int nThresValueDisp
	//*@param output : -
	//*@return		 :  
	//*/
	bool OnInitDialog(int nThresValueDisp);

	///**
	//*description   :  
	//*@param input  : int nThresValueDisp
	//*@param output : -
	//*@return		 : ���� ���� ����
	//*/
	bool OnNMCustomdrawSldThreshhold(int nThresValueDisp);

	///**
	//*description   :  
	//*@param input  : const CPaintDC& dcView
	//*@param input  : const CRect& rect
	//*@param output : -
	//*@return		 : ���� ���� ����
	//*/
	bool OnPaint(const CPaintDC& dcView, const CRect& rect);

	///**
	//*description   : �̸� ��Ʈ�� �̹����� �����鼭 �ʱ�ȭ 
	//*@param input  : 
	//*@param output : CUserBitmap& bitmapNode
	//*@return		 : ���� ���� ����
	//*/
	bool GetImage(CUserBitmap& bitmapNode ) const;

	///**
	//*description   : �̸� ��Ʈ�� �̹����� �����鼭 �ʱ�ȭ 
	//*@param input  : const CUserBitmap& bitmapNode
	//*@param output : -
	//*@return		 : ���� ���� ����
	//*/
	bool SetImage(const CUserBitmap& bitmapNode);

protected:

	///**
	//*description   : �ʱ�ȭ
	//*@param input  : int nThresValueDisp
	//*@param output : -
	//*@return		 :  
	//*/
	void Initialize(int nThresValueDisp = 0);

private:

};
#endif //_DYNBINPROCESS_H_
