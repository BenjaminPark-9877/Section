/////** 
////*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü ���� �������
////*               
////* 
////*/
#ifndef _BITMAPINFO_H_
#define _BITMAPINFO_H_
#pragma once

#ifndef _BASICBONE_H_
#include "basicbone.h"
#endif //_BASICBONE_H_

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif //_USERMACHRO_H_

/////** 
////*description   :  
////*@parent class : -
////*/
class CBitmapInfo :  private CBasicBone
{
//// ��� ���� ���� �κ�
public:

protected:
	BITMAPINFO* m_pBmpInfo;			// ��Ʈ�� �̹��� ȭ�� ��¿� ��� ���� 

private:

//// ��� �Լ� ���� �κ�
public:

	///**
	//*description   : ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapInfo(void);

	///**
	//*description   : �Ҹ���
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	~CBitmapInfo(void);

	///**
	//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapInfo(const CBitmapInfo& rhs);

	///**
	//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapInfo(const BITMAPINFO& rhs);

	///**
	//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapInfo(const BITMAPINFOHEADER& rhs);

	///**
	//*description   : �̵� ������ ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapInfo( CBitmapInfo&& rhs ) noexcept;

	///**
	//*description   : �̵� ���� ������ ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapInfo& operator=( CBitmapInfo&& rhs) noexcept;

	///**
	//*description   :���� ����Ǵ� ��ü �� ���� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapInfo& operator=(const CBitmapInfo& rhs);

	///**
	//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapInfo& operator=(const BITMAPINFO& rhs);

	///**
	//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapInfo& operator=( BITMAPINFOHEADER& rhs);

	///**
	//*description   : �������� ���� Ȯ��
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline const bool operator==(const CBitmapInfo& rhs) const { return isEqual(rhs);}

	///**
	//*description   : �ٸ��� ���� Ȯ��
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline const bool operator!=(const CBitmapInfo& rhs) const { return !(isEqual(rhs)); }

	///**
	//*description   : �������� ���� Ȯ��
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const bool operator==(const BITMAPINFO& rhs) const { return isEqual(rhs); }

	///**
	//*description   : �ٸ��� ���� Ȯ��
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline const bool operator!=(const BITMAPINFO& rhs) const { return !(isEqual(rhs)); }

	///**
	//*description   : �������� ���� Ȯ��
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const bool operator==( const BITMAPINFOHEADER& rhs) const { return isEqual(rhs); }

	///**
	//*description   : �ٸ��� ���� Ȯ��
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline const bool operator!=(const BITMAPINFOHEADER& rhs) const { return !(isEqual(rhs)); }

	///**
	//*description   : �������� ���� Ȯ��
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const bool isEqual(const CBitmapInfo& rhs) const;

	///**
	//*description   : �������� ���� Ȯ��
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const bool isEqual(const BITMAPINFO& rhs) const;

	///**
	//*description   : �������� ���� Ȯ��
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const bool isEqual( const BITMAPINFOHEADER& rhs) const;

	///**
	//*description   : ��ü �޸� ���� �� ���� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline void Clear(void) { if (m_pBmpInfo != NULL) { free(m_pBmpInfo); m_pBmpInfo = NULL; } }

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
	//*@param output : -
	//*@return		 : 
	//*/
	inline bool GetBitmapInfo(BITMAPINFO& rhs) const { return  GetBitmapInfo(&rhs); }

	///**
	//*description   : 
	//*@param input  : -
	//*@param output : -
	//*@return		 : 
    //*/
	bool GetBitmapInfo(BITMAPINFO* rhs) const;

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 : const BITMAPINFOHEADER*
	//*/
	inline BITMAPINFOHEADER* GetBimapInfoHeader(void) const { return ((m_pBmpInfo != NULL) ? &(m_pBmpInfo->bmiHeader) : NULL); }

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 : 
	//*/
	inline bool GetBimapInfoHeader(BITMAPINFOHEADER& rhs) const { return GetBimapInfoHeader(&rhs); }

	///**
	//*description   :  
	//*@param input  :   
	//*@return		 : 
	//*/
	bool GetBimapInfoHeader(BITMAPINFOHEADER* rhs) const;

	///**
	//*description   : �̹��� ���� �޾ƿ´�.
	//*@param input  : -
	//*@return		 : �̹��� ��
	//*/
	inline const unsigned long GetMaximumWidth(void) const { return (((m_pBmpInfo != NULL)) ? (m_pBmpInfo->bmiHeader.biWidth) : INVALID_IMAGE_SIZE); }

	///**
	//*description   : �̹��� ���̸� �޾ƿ´�.
	//*@param input  : -
	//*@return		 : �̹��� ����
	//*/
	inline const unsigned long GetMaximumHeight(void) const { return (((m_pBmpInfo != NULL)) ? (m_pBmpInfo->bmiHeader.biHeight) : INVALID_IMAGE_SIZE); }

	///**
	//*description   : �̹��� ���� �ȼ� ���� ����Ѵ�.
	//*@param input  : -
	//*@return		 : �̹��� ���� �ȼ� ��
	//*/
	inline const unsigned long GetRwSize(void) const { return (((m_pBmpInfo != NULL)) ? (WIDTHBYTES((m_pBmpInfo->bmiHeader.biBitCount * m_pBmpInfo->bmiHeader.biWidth))) : INVALID_IMAGE_SIZE); }

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
	inline const unsigned long GetTotalSize(void) const { return  (((m_pBmpInfo != NULL)) ? (m_pBmpInfo->bmiHeader.biSizeImage) : INVALID_IMAGE_SIZE); }

	///**
	//*description   : 
	//*@param input  : -
	//*@return		 : 
	//*/
	inline const CBitmapInfo* Get(void) const { return (m_pBmpInfo != NULL) ? this : NULL; }

	///**
	//*description   : BITMAPINFO �ʱ�ȭ �� �޸� �Ҵ�
	//*@param input  : -
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	inline bool Initialize(const CBitmapInfo* pBmpInfo) { return Set(pBmpInfo); }
	
	///**
	//*description   : BITMAPINFO �ʱ�ȭ �� �޸� �Ҵ�
	//*@param input  : -
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	inline bool Initialize(const BITMAPINFO* pBmpInfo) { return Set(pBmpInfo); }

	///**
	//*description   : BITMAPINFO �ʱ�ȭ �� �޸� �Ҵ�
	//*@param input  : -
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	inline bool Initialize(const BITMAPINFOHEADER* pBmpInfoHead) { return Set(pBmpInfoHead); }

	///**
	//*description   : BITMAPINFO �׸� ����(�����ͷ� �޾ƿ� ���)
	//*@param input  : const CBitmapInfo& rhs
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	inline  bool Set(const CBitmapInfo& rhs) { return Set(&rhs); }

	///**
	//*description   : BITMAPINFO �׸� ����(�����ͷ� �޾ƿ� ���)
	//*@param input  : const BITMAPINFO& rhs
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	inline bool Set(const BITMAPINFO& rhs) { return Set(&rhs); }

	///**
	//*description   :  
	//*@param input  : const BITMAPINFOHEADER& rhs
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	inline bool Set(const BITMAPINFOHEADER& rhs) { return Set(&rhs); }

	///**
	//*description   : BITMAPINFO �׸� ����(�����ͷ� �޾ƿ� ���)
	//*@param input  : const CBitmapInfo* bmpInfo
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool Set(const CBitmapInfo* pBmpInfo);

	///**
	//*description   : BITMAPINFO �׸� ����(�����ͷ� �޾ƿ� ���)
	//*@param input  : const BITMAPINFO* bmpInfo
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool Set(const BITMAPINFO* pBmpInfo);

	///**
	//*description   :  
	//*@param input  : const BITMAPINFOHEADER* pBmpInfoHead
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	bool Set(const BITMAPINFOHEADER* pBmpInfoHead);

protected:

	///**
	//*description   : �޸� �Ҵ�
	//*@param input  : -
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool Initialize(void);

private:
};

#endif //_BITMAPINFO_H_