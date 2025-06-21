/////** 
////*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü ���� �������
////*               
////* 
////*/
#ifndef _BITMAPNODE_H_
#define _BITMAPNODE_H_
#pragma once

#include <winnt.h>
#include <wingdi.h>
#include <vcruntime_string.h>
#include <windef.h>
#include <tchar.h>
#include <afx.h>

#ifndef _BASICBONE_H_
#include "basicbone.h"
#endif //_BASICBONE_H_

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif //_USERMACHRO_H_

///** 
//*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü 
//*@parent class : private CBasicBone : ���� ������, ���� ������ ȣ�� ������
//*/
class CBitmapNode : private CBasicBone
{
//// ��� ���� ���� �κ�
public:

protected:
	BITMAPINFO*			m_pBmpInfo;			// ��Ʈ�� �̹��� ȭ�� ��¿� ��� ���� 
	BITMAPINFOHEADER*	m_pDibHi;			// ���Ͽ��� �о�� ��� ���� 
	BITMAPFILEHEADER*	m_pDibHf;			// ��Ʈ�� ���� ��� ����
	unsigned char*		m_pUcBmpImage;		// �о�� ��Ʈ�� ���� ����

private:

//// ��� �Լ� ���� �κ�
public:

	///**
	//*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü �� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapNode(void);

	///**
	//*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü �� �Ҹ���
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	~CBitmapNode(void);

	///**
	//*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü �� ���� ������ 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapNode(const CBitmapNode& rhs);

	///**
	//*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü �� ���� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapNode& operator = (const CBitmapNode& rhs);

	///**
	//*description   : ��ü �޸� ���� �� ���� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void Clear(void);

	///**
	//*description   : ��ü �ʱ�ȭ �� �迭 �κ� ������ �޸� �Ҵ�
	//*@param input  : -
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool Initialize(void);

	///**
	//*description   : ��ü �ʱ�ȭ �� ������ ũ���� �迭�� ���� �޸� �Ҵ�
	//*@param input  : const size_t& szTotalSize
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool Initialize(const size_t& szTotalSize);

	///**
	//*description   : BITMAPINFO �׸� �޾ƿ�
	//*@param input  : -
	//*@param output : BITMAPINFO& bmpInfo
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool GetBitmapInfo(BITMAPINFO& bmpInfo) const;

	///**
	//*description   : BITMAPINFO �׸� �޾ƿ� (R-Value��)
	//*@param input  : -
	//*@param output : -
	//*@return		 : BITMAPINFO ������
	//*/
	inline BITMAPINFO* GetBitmapInfo(void) const { return ((m_pBmpInfo != NULL) ? m_pBmpInfo : NULL); }

	///**
	//*description   :  
	//*@param input  : -
	//*@param output : BITMAPFILEHEADER& bmpFileHead
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool GetBitmapFileHeader(BITMAPFILEHEADER& bmpFileHead) const;

	///**
	//*description   :  
	//*@param input  : -
	//*@param output : BITMAPINFOHEADER& bmpInfoHead
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool GetBitmapInfoHeader(BITMAPINFOHEADER& bmpInfoHead) const;

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 : const BITMAPINFOHEADER*
	//*/
	inline BITMAPINFOHEADER* GetBimapInfoHeader(void) const { return ((m_pDibHi != NULL) ? m_pDibHi : NULL); }

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 : const BITMAPFILEHEADER*
	//*/
	inline BITMAPFILEHEADER* GetBimapFileHeader(void) const { return ((m_pDibHf != NULL) ? m_pDibHf : NULL); }

	//*description   : c ������ �迭�� �ǵ�����
	//*@param input  :   
	//*@return		 : c ������ �迭 �ּ�
	//*/
	unsigned char* c_arr(void) const { return ((m_pUcBmpImage != NULL) ? m_pUcBmpImage : NULL); }

	///**
	//*description   : ÷�� ������ ������(�̸� ���� ������ Ȯ�� �ʿ�)
	//*@param input  : size_t nPos : ��ġ
	//*@return		 : �ش� ��ġ�� ��
	//*/
	inline unsigned char& operator[](const size_t& nPos) { return  m_pUcBmpImage[nPos]; }

	///**
	//*description   : ÷�� ������ ������ const type
	//*@param input  : size_t nPos : ��ġ
	//*@return		 : �ش� ��ġ�� ��
	//*/
	inline const unsigned char operator[](const size_t& nPos) const { return (((m_pUcBmpImage != NULL)) ? m_pUcBmpImage[nPos] : 0); }

	///**
	//*description   : �̹��� ���� �޾ƿ´�.
	//*@param input  : -
	//*@return		 : �̹��� ��
	//*/
	inline const int GetMaximumWidth(void) const { return (((m_pBmpInfo != NULL) ) ? (m_pBmpInfo->bmiHeader.biWidth) : INVALID_IMAGE_SIZE); }

	///**
	//*description   : �̹��� ���̸� �޾ƿ´�.
	//*@param input  : -
	//*@return		 : �̹��� ����
	//*/
	inline const int GetMaximumHeight(void) const { return (((m_pBmpInfo != NULL)) ? (m_pBmpInfo->bmiHeader.biHeight) : INVALID_IMAGE_SIZE); }

	///**
	//*description   : �̹��� ���� �ȼ� ���� ����Ѵ�.
	//*@param input  : -
	//*@return		 : �̹��� ���� �ȼ� ��
	//*/
	inline const int GetRwSize(void) const { return (((m_pBmpInfo != NULL) ) ? (WIDTHBYTES((m_pBmpInfo->bmiHeader.biBitCount * m_pBmpInfo->bmiHeader.biWidth))) : INVALID_IMAGE_SIZE); }

	///**
	//*description   : ���� ��Ʈ ���� �޾ƿ´�.
	//*@param input  : -
	//*@return		 : ���� ��Ʈ
	//*/
	inline const int GetBitCount(void) const { return  (((m_pBmpInfo != NULL)) ? (m_pBmpInfo->bmiHeader.biBitCount) : INVALID_BIT_COUNT); }

	///**
	//*description   : ������ ����� �迭�� �� ũ�⸦ ����Ѵ�.
	//*@param input  : -
	//*@return		 : ���� ��Ʈ
	//*/
	inline const int GetTotalSize(void) const { return  (((m_pBmpInfo != NULL)) ? (m_pBmpInfo->bmiHeader.biSizeImage) : INVALID_IMAGE_SIZE); }

	///**
	//*description   : 
	//*@param input  : unsigned char*	pUcBmpImage
	//*@param input  : BITMAPINFO*		pBmpInfo
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool SetImage(unsigned char* pUcBmpImage, BITMAPINFO* pBmpInfo);

	///**
	//*description   :  
	//*@param input  : unsigned char*		pUcBmpImage
	//*@param input  : BITMAPINFOHEADER*	pDibHi
	//*@param input  : BITMAPFILEHEADER*	pDibHf
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool SetImage(unsigned char* pUcBmpImage, BITMAPINFOHEADER* pDibHi, BITMAPFILEHEADER* pDibHf);

	///**
	//*description   :  
	//*@param input  : unsigned char*		pUcBmpImage
	//*@param input  : BITMAPINFO*			pBmpInfo  
	//*@param input  : BITMAPINFOHEADER*	pDibHi
	//*@param input  : BITMAPFILEHEADER*	pDibHf
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool SetImage(unsigned char* pUcBmpImage, BITMAPINFO* pBmpInfo, BITMAPINFOHEADER* pDibHi, BITMAPFILEHEADER* pDibHf);

	///**
	//*description   :  
	//*@param input  : const CBitmapNode& rhs
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool SetImage(const CBitmapNode& rhs);

	///**
	//*description   : 
	//*@param output  : unsigned char*	pUcBmpImage
	//*@param output  : BITMAPINFO*		pBmpInfo
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	const bool GetImage(unsigned char* pUcBmpImage, BITMAPINFO* pBmpInfo) const;

	///**
	//*description   :  
	//*@param output  : unsigned char*		pUcBmpImage
	//*@param output  : BITMAPINFOHEADER*	pDibHi
	//*@param output  : BITMAPFILEHEADER*	pDibHf
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	const bool GetImage(unsigned char* pUcBmpImage, BITMAPINFOHEADER* pDibHi, BITMAPFILEHEADER* pDibHf) const;

#ifdef DEBUG
	///**
	//*description   : ��ü ���� ������� �� ���â�� �����ֱ�(������)
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void TraceElements(void);
#endif DEBUG

protected:

	///**
	//*description   : BITMAPINFO �ʱ�ȭ �� �޸� �Ҵ�
	//*@param input  : -
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool InitializeBitmapInfo(void);

	///**
	//*description   : BITMAPINFO �޸� ���� �� ���� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void ClearBitmapInfo(void);

	///**
	//*description   : BITMAPINFOHEADER �ʱ�ȭ
	//*@param input  : -
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool InitializeBitmapInfoHeader(void);

	///**
	//*description   : BITMAPINFOHEADER �޸� ���� �� ���� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void ClearBitmapInfoHeader(void);

	///**
	//*description   : ��Ʈ�� ���� ��� ���� �ʱ�ȭ
	//*@param input  : -
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool InitializeBitmapFileHeader(void);

	///**
	//*description   : ��Ʈ�� ���� ��� �޸� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void ClearBitmapFileHeader(void);

	///**
	//*description   :
	//*@param input  : const size_t& size (�Ҵ� ���� �迭�� ũ��)
	//*@param output : 
	//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
	//*/
	bool InitializeBitmapArray(const size_t& size);

	///**
	//*description   : ��Ʈ�� ���� �迭 �޸� ���� �� ���� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void ClearBitmapArray(void);

	///**
	//*description   : BITMAPINFO �׸� ����
	//*@param input  : const BITMAPINFO& bmpInfo
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool SetBitmapInfo(const BITMAPINFO& bmpInfo);

	///**
	//*description   : BITMAPINFO �׸� ����(�����ͷ� �޾ƿ� ���)
	//*@param input  : const BITMAPINFO* bmpInfo
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool SetBitmapInfo(const BITMAPINFO* pBmpInfo);

	///**
	//*description   :  
	//*@param input  : const BITMAPINFOHEADER& bmpInfoHead
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	bool SetBitmapInfoHeader(const BITMAPINFOHEADER& bmpInfoHead);

	///**
	//*description   :  
	//*@param input  : const BITMAPINFOHEADER* pBmpInfoHead
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	bool SetBitmapInfoHeader(const BITMAPINFOHEADER* pBmpInfoHead);

	///**
	//*description   :  
	//*@param input  : const BITMAPFILEHEADER& bmpFileHead
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	bool SetBitmapFileHeader(const BITMAPFILEHEADER& bmpFileHead);

	///**
	//*description   :  
	//*@param input  : const BITMAPFILEHEADER* pBmpFileHead
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	bool SetBitmapFileHeader(const BITMAPFILEHEADER* pBmpFileHead);

private:

};
#endif //_BITMAPNODE_H_

