#include "pch.h"
#include "BitmapFileHeader.h"

///**
//*description   : CBasicBone Ŭ������ ������
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CBitmapFileHeader::CBitmapFileHeader(void) 
{
	m_pDibHf = NULL;
}

///**
//*description   : CBasicBone Ŭ������ �Ҹ���           
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CBitmapFileHeader::~CBitmapFileHeader(void)
{
	Clear();
}

///**
//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CBitmapFileHeader::CBitmapFileHeader(const CBitmapFileHeader& rhs)
{
	m_pDibHf = NULL;
	Set(rhs);
}

///**
//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CBitmapFileHeader::CBitmapFileHeader(const BITMAPFILEHEADER& rhs)
{
	m_pDibHf = NULL;
	Set(rhs);
}

///**
//*description   : �̵� ������
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CBitmapFileHeader::CBitmapFileHeader(CBitmapFileHeader&& rhs) noexcept
{
	m_pDibHf = NULL;
	m_pDibHf = rhs.m_pDibHf;
	rhs.m_pDibHf = NULL;
}

///**
//*description   : �̵� ���� ������
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CBitmapFileHeader& CBitmapFileHeader::operator=(CBitmapFileHeader&& rhs) noexcept
{
	if (this != &rhs)
	{
		m_pDibHf = rhs.m_pDibHf;
		rhs.m_pDibHf = NULL;
	}
	return *this;
}

///**
//*description   :���� ����Ǵ� ��ü �� ���� ������
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CBitmapFileHeader& CBitmapFileHeader::operator=(const CBitmapFileHeader& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Set(rhs);

	return *this;
}

///**
//*description   : ���� ����Ǵ� ��ü �� ���� ������ 
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
CBitmapFileHeader& CBitmapFileHeader::operator=(const BITMAPFILEHEADER& rhs)
{
	if (this->m_pDibHf == &rhs)
	{
		return *this;
	}

	Set(rhs);

	return *this;
}

///**
//*description   : �������� ���� ������ ������
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
const bool CBitmapFileHeader::isEqual(const CBitmapFileHeader& rhs) const
{
	if (rhs.GetBitmapFileHeader() == NULL)
	{
		return false;
	}

	if (m_pDibHf == NULL)
	{
		return false;
	}

	if (isEqual( *rhs.GetBitmapFileHeader() ) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

///**
//*description   : �������� ���� ������ ������
//*@param input  : -
//*@param output : -
//*@return		 : -
//*/
const bool CBitmapFileHeader::isEqual(const BITMAPFILEHEADER& rhs) const
{
	if (m_pDibHf == NULL)
	{
		return false;
	}

	if (m_pDibHf != &rhs)
	{
		return false;
	}

	return true;
}

///**
//*description   : �޸� �Ҵ�
//*@param input  : -
//*@param output : -
//*@return		 : ���� ���� ���� (true : �������, false : ���� ����)
//*/
bool CBitmapFileHeader::Initialize(void)
{
	Clear();

	m_pDibHf = new BITMAPFILEHEADER;

	if (m_pDibHf == NULL)
	{
		return false;
	}

	memset(m_pDibHf, 0, sizeof(BITMAPFILEHEADER));

	return true;
}

///**
//*description   :  
//*@param input  : const BITMAPFILEHEADER* pDibHf
//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
//*/
bool CBitmapFileHeader::Set(const BITMAPFILEHEADER* pDibHf)
{
	if (pDibHf == NULL)
	{
		return false;
	}

	if (Initialize() == false)
	{
		return false;
	}

	if (m_pDibHf == NULL)
	{
		return false;
	}

	memcpy(m_pDibHf, pDibHf, sizeof(BITMAPFILEHEADER));

	return true;
}

///**
//*description   :  
//*@param input  : const CBitmapFileHeader* pDibHf
//*@return		 : ���� ���� ����( TRUE : ���� ����, FALSE : ���� �߻� ) 
//*/
bool CBitmapFileHeader::Set(const CBitmapFileHeader* pBmpFileHead)
{
	if (pBmpFileHead == NULL)
	{
		return false;
	}

	if (this == pBmpFileHead)
	{
		return false;
	}

	if (Initialize() == false)
	{
		return false;
	}

	if (m_pDibHf == NULL)
	{
		return false;
	}

	memcpy(m_pDibHf, pBmpFileHead->m_pDibHf, sizeof(BITMAPFILEHEADER));

	return true;
}
///**
//*description   : 
//*@param input  : -
//*@return		 : 
//*/
bool CBitmapFileHeader::GetBitmapFileHeader(BITMAPFILEHEADER* pDibHf) const
{
	if (m_pDibHf == NULL)
	{
		return false;
	}

	if (pDibHf == NULL)
	{
		return false;
	}

	memcpy(pDibHf, m_pDibHf, sizeof(BITMAPFILEHEADER));

	return true;
}
