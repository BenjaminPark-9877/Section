/////** 
////*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü ���� �������
////*              : vector class ���� data() �޼ҵ� ���� �ȵȴٸ� ������� "  #define _NOT_APPLYED_VEDCTOR_DATA_ " ���� �ϰ� �� ��
////*              : �ٸ� �׷� ���, �߰� �ڵ� �м� �� �������� ���ؼ� ���� Ȯ���ϸ鼭 ����
////* 
////*/
#ifndef _USERBITMAP_H_
#define _USERBITMAP_H_
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

#ifndef _BITMAPINFO_H_
#include "BitmapInfo.h"
#endif //_BITMAPINFO_H_

#ifndef _BITMAPFILEHEADER_H_
#include "BitmapFileHeader.h"
#endif //_BITMAPFILEHEADER_H_

#include<vector>

using namespace std;

///** 
//*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü 
//*@parent class : private CBasicBone : ���� ������, ���� ������ ȣ�� ������
//*/
class CUserBitmap : private CBasicBone
{
//// ��� ���� ���� �κ�
public:

protected:

	CBitmapInfo					m_BmpInfo;			// ��Ʈ�� �̹��� ȭ�� ��¿� ��� ���� 
	
	CBitmapFileHeader			m_DibHf;			// ��Ʈ�� ���� ��� ����

	unsigned char*				m_pUcBmpImage;		// �о�� ��Ʈ�� ���� ����

#ifndef _NOT_APPLYED_VECTOR_DATA_	
	vector<unsigned char>		m_vecBmpImage;		// ���� �������� ����� ��Ʈ�� ���� ���� �κ� 
#endif //_NOT_APPLYED_VECTOR_DATA_	

private:

//// ��� �Լ� ���� �κ�
public:

	///**
	//*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü �� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CUserBitmap();

	///**
	//*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü �� �Ҹ���
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	~CUserBitmap();

	///**
	//*description   : BITMAPINFO �׸� �޾ƿ� (R-Value��)
	//*@param input  : -
	//*@param output : -
	//*@return		 : BITMAPINFO ������
	//*/
	inline BITMAPINFO* GetBitmapInfo(void) const { return m_BmpInfo.GetBitmapInfo(); }

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 : const BITMAPINFOHEADER*
	//*/
	inline const BITMAPINFOHEADER* GetBimapInfoHeader(void) const { return m_BmpInfo.GetBimapInfoHeader(); }

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 :
	//*/
	bool GetBimapInfoHeader(BITMAPINFOHEADER& rhs) const { return m_BmpInfo.GetBimapInfoHeader(rhs); }

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 : 
	//*/
	bool GetBimapInfoHeader(BITMAPINFOHEADER* rhs) const { return m_BmpInfo.GetBimapInfoHeader(rhs); }

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 : const BITMAPFILEHEADER*
	//*/
	inline const BITMAPFILEHEADER* GetBimapFileHeader(void) const { return m_DibHf.GetBitmapFileHeader(); }

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 :  
	//*/
	bool GetBimapFileHeader(BITMAPFILEHEADER* rhs) const { return m_DibHf.GetBitmapFileHeader(rhs); }

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 :  
	//*/
	bool GetBimapFileHeader(BITMAPFILEHEADER& rhs) const { return m_DibHf.GetBitmapFileHeader(rhs); }

	///**
	//*description   : �̹��� ���� �޾ƿ´�.
	//*@param input  : -
	//*@return		 : �̹��� ��
	//*/
	inline const int GetMaximumWidth(void) const { return m_BmpInfo.GetMaximumWidth(); }

	///**
	//*description   : �̹��� ���̸� �޾ƿ´�.
	//*@param input  : -
	//*@return		 : �̹��� ����
	//*/
	inline const int GetMaximumHeight(void) const { return m_BmpInfo.GetMaximumHeight(); }

	///**
	//*description   : �̹��� ���� �ȼ� ���� ����Ѵ�.
	//*@param input  : -
	//*@return		 : �̹��� ���� �ȼ� ��
	//*/
	inline const int GetRwSize(void) const { return m_BmpInfo.GetRwSize(); }

	///**
	//*description   : ���� ��Ʈ ���� �޾ƿ´�.
	//*@param input  : -
	//*@return		 : ���� ��Ʈ
	//*/
	inline const int GetBitCount(void) const { return m_BmpInfo.GetBitCount(); }

	///**
	//*description   : ������ ����� �迭�� �� ũ�⸦ ����Ѵ�.
	//*@param input  : -
	//*@return		 : ���� ��Ʈ
	//*/
	inline const int GetTotalSize(void) const { return m_BmpInfo.GetTotalSize(); }

protected:

	///**
	//*description   : BITMAPINFO �׸� ����
	//*@param input  : const BITMAPINFO& bmpInfo
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	inline bool SetBitmapInfo(const BITMAPINFO& bmpInfo) { return m_BmpInfo.Set(bmpInfo); }

	///**
	//*description   : BITMAPINFO �׸� ����(�����ͷ� �޾ƿ� ���)
	//*@param input  : const BITMAPINFO* bmpInfo
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	inline bool SetBitmapInfo(const BITMAPINFO* pBmpInfo) { return m_BmpInfo.Set(pBmpInfo); }

	///**
	//*description   :  
	//*@param input  : const BITMAPINFOHEADER& bmpInfoHead
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	inline bool SetBitmapInfoHeader(const BITMAPINFOHEADER& bmpInfoHead) { return m_BmpInfo.Set(bmpInfoHead); }

	///**
	//*description   :  
	//*@param input  : const BITMAPINFOHEADER* pBmpInfoHead
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	inline bool SetBitmapInfoHeader(const BITMAPINFOHEADER* pBmpInfoHead) { return m_BmpInfo.Set(pBmpInfoHead); }

	///**
	//*description   :  
	//*@param input  : const BITMAPFILEHEADER& bmpFileHead
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	inline bool SetBitmapFileHeader(const BITMAPFILEHEADER& bmpFileHead) { return m_DibHf.Set(bmpFileHead); }

	///**
	//*description   :  
	//*@param input  : const BITMAPFILEHEADER* pBmpFileHead
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	inline bool SetBitmapFileHeader(const BITMAPFILEHEADER* pBmpFileHead) { return m_DibHf.Set(pBmpFileHead); }

private:

// ���� vector class ���� data() �޼ҵ� ���� ���ο� ���� ���� ��� ������
// vector class ���� data() �޼ҵ� ���� �ȵȴٸ� ������� "  #define _NOT_APPLYED_VEDCTOR_DATA_ " ���� �ϰ� �� ��
// �׷��� �ʴٸ� "  #define _NOT_APPLYED_VEDCTOR_DATA_ " �������� �ʱ�
#ifdef _NOT_APPLYED_VECTOR_DATA_	

public:
	///**
	//*description   : ��ü �޸� ���� �� ���� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void Clear(void);

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
	//*@param input  : const CBitmapNode& rhs
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool SetImage(const CUserBitmap& rhs);

protected:

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
	inline void ClearBitmapArray(void) { if (m_pUcBmpImage != NULL) { delete[] m_pUcBmpImage; m_pUcBmpImage = NULL; } }

private:

#else //_NOT_APPLYED_VEDCTOR_DATA_

public:
	///**
	//*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü�� ���� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CUserBitmap(const CUserBitmap& rhs);

	///**
	//*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü�� ���� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CUserBitmap& operator=(const CUserBitmap& rhs);

	///**
	//*description   : ��ü �޸� ���� �� ���� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	void Clear(void);

	//*description   : c ������ �迭�� �ǵ�����
	// 	               �迭 ������ �ٲپ�� �ϴ� ��� �ܿ��� c_arr_const()�� ����ϱ�
	//				   ���� Dangling Reference �߻� �ϴ��� Ȯ�� �� ����� �ϱ�
	//*@param input  :   
	//*@param output : 
	//*@return		 : c ������ �迭 �ּ�
	//*/
	unsigned char* c_arr(void);

	//*description   : c ������ �迭�� �ǵ����� (�����)
	//*@param input  :   
	//*@param output : 
	//*@return		 : c ������ �迭 �ּ�
	//*/
	inline const unsigned char* c_arr_const(void) const { return m_vecBmpImage.data(); }

	///**
	//*description   : ÷�� ������ ������(�̸� ���� ������ Ȯ�� �ʿ�)
	//*@param input  : size_t nPos : ��ġ
	//*@return		 : �ش� ��ġ�� ��
	//*/
	inline unsigned char& operator[](const size_t& nPos) { return  m_vecBmpImage[nPos]; }

	///**
	//*description   : ÷�� ������ ������ const type
	//*@param input  : size_t nPos : ��ġ
	//*@return		 : �ش� ��ġ�� ��
	//*/
	inline const unsigned char operator[](const size_t& nPos) const { return (((m_vecBmpImage.empty() == false)) ? m_vecBmpImage[nPos] : 0); }

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
	//*@param input  : const CBitmapNode& rhs
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool SetImage(const CUserBitmap& rhs);

protected:

	///**
	//*description   :  
	//*@param input  : size_t szSize
	//*@return		 : 
	//*/
	inline void PushBitmapImageVector(const unsigned char* pUcBmpImage, const size_t& szSize) { m_vecBmpImage.clear(); for (int i = 0; i < ((GetRwSize() * GetMaximumHeight())); i++) { m_vecBmpImage.push_back(pUcBmpImage[i]); } }

private:

#endif //_NOT_APPLYED_VEDCTOR_DATA_	

};
#endif //_USERBITMAP_H_
