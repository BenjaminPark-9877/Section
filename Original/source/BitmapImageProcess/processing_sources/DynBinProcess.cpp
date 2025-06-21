/////** 
////*description   : ���� ����ȭ�� ó���ϴ� ��ü ���� �ҽ�����
////*               
////* 
////*/
#include "pch.h"
#include "DynBinProcess.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "BitmapImageProcessDoc.h"
#include "BitmapImageProcessView.h"

///**
//*description   : ������
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CDynBinProcess::CDynBinProcess::CDynBinProcess(void)
{
	m_nThresValueDisp = 0;
}

///**
//*description   : �Ҹ���
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CDynBinProcess::~CDynBinProcess(void)
{
	Clear();
}

///**
//*description   : ���� ����
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
void CDynBinProcess::Clear(void)
{
	m_bmpDynBinIn.Clear();
	m_bmpDynBinOut.Clear();
}

///**
//*description   : ��ȭ���� �ʱ�ȭ �� ó���� ����
//*@param input  : int nThresValueDisp
//*@param output : -
//*@return		 :  
//*/
bool  CDynBinProcess::OnInitDialog(int nThresValueDisp)
{

	SetThreshValueDisp(nThresValueDisp);

	return true;
}

///**
//*description   : �����Ҵ� ���� �ʱ�ȭ
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CDynBinProcess::Initialize(int nThresValueDisp /*=0*/ )
{
	SetThreshValueDisp(nThresValueDisp);
	Clear();
}

///**
//*description   : �̸� ��Ʈ�� �̹����� �����鼭 �ʱ�ȭ 
//*@param input  : const CBitmapNode& bitmapNode
//*@param output : -
//*@return		 : ���� ���� ����
//*/
bool CDynBinProcess::SetImage(const CUserBitmap& bitmapNode)
{
	if (bitmapNode.GetBitCount() != 24)
	{
		return false;
	}

	Clear();

	if (m_bmpDynBinIn.SetImage(bitmapNode) == false)
	{
		return false;
	}

	if (m_bmpDynBinOut.SetImage(bitmapNode) == false)
	{
		return false;
	}

	return true;
}

///**
//*description   :  
//*@param input  : int nThresValueDisp
//*@param output : -
//*@return		 : ���� ���� ����
//*/
bool CDynBinProcess::OnNMCustomdrawSldThreshhold(int nThresValueDisp)
{
	SetThreshValueDisp(nThresValueDisp);
	
	int height = m_bmpDynBinIn.GetMaximumHeight();
	int width = m_bmpDynBinIn.GetMaximumWidth();
	int bitcount = m_bmpDynBinIn.GetBitCount();
	int rwsize = m_bmpDynBinIn.GetRwSize();

	int index = 0;
	int index2 = 0;
	int i = 0;
	int j = 0;
	
	int LUT[256];
	for (i = 0; i < 256; i++) LUT[i] = i > m_nThresValueDisp ? (unsigned char)255 : 0;

	if (bitcount == 24)
	{
		for (i = 0; i < height; i++)
		{
			index = (height - i - 1) * rwsize;
			for (j = 0; j < width; j++)
			{
				index2 = index + 3 * j;
				m_bmpDynBinOut[index2] = LUT[(int)(m_bmpDynBinIn[index2])];
				m_bmpDynBinOut[index2 + 1] = LUT[(int)(m_bmpDynBinIn[index2 + 1])];
				m_bmpDynBinOut[index2 + 2] = LUT[(int)(m_bmpDynBinIn[index2 + 2])];
			}
		}
	}
	else if (m_bmpDynBinIn.GetBitCount() == 8)
	{
		for (i = 0; i < height; i++)
		{
			index = (height - i - 1) * rwsize;
			for (j = 0; j < width; j++)
			{
				index2 = index + j;
				m_bmpDynBinOut[index2] = LUT[(int)(m_bmpDynBinIn[index2])];
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

///**
//*description   :  
//*@param input  : const CPaintDC& dcView
//*@param input  : const CRect& rect
//*@param output : -
//*@return		 : ���� ���� ����
//*/
bool CDynBinProcess::OnPaint(const CPaintDC& dcView, const CRect& rect)
{
	StretchDIBits(dcView.m_hDC, rect.left, rect.top, rect.right, rect.bottom, 0, 0,
		m_bmpDynBinOut.GetMaximumWidth(), m_bmpDynBinOut.GetMaximumHeight(),
		m_bmpDynBinOut.c_arr_const(), m_bmpDynBinOut.GetBitmapInfo(), BI_RGB, SRCCOPY);

	return true;
}

///**
//*description   : �̸� ��Ʈ�� �̹����� �����鼭 �ʱ�ȭ 
//*@param input  : 
//*@param output : CBitmapNode& bitmapNode
//*@return		 : ���� ���� ����
//*/
bool CDynBinProcess::GetImage(CUserBitmap& bitmapNode) const
{
	if (m_bmpDynBinOut.c_arr_const() == NULL)
	{
		return false;
	}

	if (bitmapNode.SetImage(m_bmpDynBinOut) == false)
	{
		return false;
	}

	return true;
}