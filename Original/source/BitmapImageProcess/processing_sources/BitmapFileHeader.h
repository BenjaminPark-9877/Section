/////** 
////*description   : ��Ʈ�� ������ ���� ����Ǵ� ��ü ���� �������
////*               
////* 
////*/
#ifndef _BITMAPFILEHEADER_H_
#define _BITMAPFILEHEADER_H_
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
class CBitmapFileHeader :   private CBasicBone
{
//// ��� ���� ���� �κ�
public:

protected:
	
	BITMAPFILEHEADER* m_pDibHf;			// ��Ʈ�� ���� ��� ����

private:

//// ��� �Լ� ���� �κ�
public:

	///**
	//*description   : CBasicBone Ŭ������ ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapFileHeader(void);

	///**
	//*description   : CBasicBone Ŭ������ �Ҹ���           
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	~CBitmapFileHeader(void);

	///**
	//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapFileHeader(const CBitmapFileHeader& rhs);

	///**
	//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapFileHeader(const BITMAPFILEHEADER& rhs);

	///**
	//*description   : �̵� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapFileHeader(CBitmapFileHeader&& rhs) noexcept;

	///**
	//*description   : �̵� ���� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapFileHeader& operator=(CBitmapFileHeader&& rhs) noexcept;

	///**
	//*description   :���� ����Ǵ� ��ü �� ���� ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapFileHeader& operator=(const CBitmapFileHeader& rhs);

	///**
	//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	CBitmapFileHeader& operator=(const BITMAPFILEHEADER& rhs);

	///**
	//*description   : �������� ���� ������ ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const bool isEqual(const CBitmapFileHeader& rhs) const;

	///**
	//*description   : �������� ���� ������ ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const bool isEqual(const BITMAPFILEHEADER& rhs) const;

	///**
	//*description   : �������� ���� ������ ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const bool operator==(const CBitmapFileHeader& rhs) const { return isEqual(rhs); }

	///**
	//*description   : �������� ���� ������ ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	const bool operator==(const BITMAPFILEHEADER& rhs) const { return isEqual(rhs); }

	///**
	//*description   : �ٸ��� ���� ������ ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline const bool operator!=(const CBitmapFileHeader& rhs) const { return !(isEqual(rhs)); }

	///**
	//*description   : �ٸ��� ���� ������ ������
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline const bool operator!=(const BITMAPFILEHEADER& rhs) const { return !(isEqual(rhs)); }

	///**
	//*description   : ��ü �޸� ���� �� ���� ����
	//*@param input  : -
	//*@param output : -
	//*@return		 : -
	//*/
	inline void Clear(void) { if (m_pDibHf != NULL) { delete m_pDibHf; m_pDibHf = NULL; } }

	///**
	//*description   : �޸� �Ҵ�
	//*@param input  : -
	//*@param output : -
	//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
	//*/
	bool Initialize(void);

	///**
	//*description   :  
	//*@param input  : const BITMAPFILEHEADER& rhs
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	inline bool Set(const BITMAPFILEHEADER& rhs) { return Set(&rhs); }

	///**
	//*description   :  
	//*@param input  : const CBitmapFileHeader& rhs
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	inline bool Set(const CBitmapFileHeader& rhs) { return Set(&rhs); }

	///**
	//*description   :  
	//*@param input  : const BITMAPFILEHEADER* pDibHf
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	bool Set(const BITMAPFILEHEADER* pDibHf);

	///**
	//*description   :  
	//*@param input  : const CBitmapFileHeader* pBmpFileHead
	//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
	//*/
	bool Set(const CBitmapFileHeader* pBmpFileHead);

	///**
	//*description   : 
	//*@param input  : -
	//*@return		 : 
	//*/
	inline const BITMAPFILEHEADER* GetBitmapFileHeader(void) const { return  (m_pDibHf != NULL) ? m_pDibHf : NULL; }

	///**
	//*description   : 
	//*@param input  : -
	//*@return		 : 
	//*/
	bool GetBitmapFileHeader(BITMAPFILEHEADER* pDibHf) const;

	///**
	//*description   : 
	//*@param input  : -
	//*@return		 : 
	//*/
	inline bool GetBitmapFileHeader(BITMAPFILEHEADER& dibHf) const { return GetBitmapFileHeader(&dibHf); }

	///**
	//*description   : 
	//*@param input  : -
	//*@return		 : 
	//*/
	inline const CBitmapFileHeader* Get(void) const { return (m_pDibHf != NULL) ?  this : NULL; }

protected:

private:

};

#endif //_BITMAPFILEHEADER_H_
