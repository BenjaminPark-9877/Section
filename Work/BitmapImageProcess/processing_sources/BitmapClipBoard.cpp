/////** 
////*description   : ��Ʈ�� ������ ó���ϴ� ��ü ���� �ҽ� ����
////*               
////* 
////*/

#include "pch.h"
#include "BitmapClipBoard.h"

///**
//*description   : ���ο� User Image ������
//*@param input  : -
//*@param output : -
//*@return		 : ������ ���࿩��(true:������,false:������)
//*/
bool CBitmapClipBoard::NewDocument(CUserBitmap& cbmpNodeIn, CUserRGBQuad& cUserRGBQuad)
{
	::OpenClipboard(NULL);

	if (!IsClipboardFormatAvailable(CF_DIB))
	{
		return false;
	}

	HGLOBAL m_hImage = NULL;

	m_hImage = ::GetClipboardData(CF_DIB);

	::CloseClipboard();

	if (m_hImage == NULL)
	{
		return false;
	}

	LPSTR pDIB = NULL;
	pDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hImage);

	if (pDIB == NULL)
	{
		return false;
	}

	if (OpenImageFromClipBoard(pDIB, cbmpNodeIn) == false)
	{
		return false;
	}

	if (cbmpNodeIn.GetBitCount() == 8)
	{
		cUserRGBQuad.Set((LPSTR)(pDIB + sizeof(BITMAPINFOHEADER)));
	}

	return true;
}

//*description   : Ŭ������� �����ϱ�(nFlag�� �⺻������ FLAG_SELECT_INPUT ��, �Է� ���� �̹����� ������)
//*@param input  : unsigned char	*m_CpyImg
//*@param output : -
//*@return		 :  
//*/
void CBitmapClipBoard::CopyClipboard(const CUserBitmap& cbmpNodeIn, CUserRGBQuad& cUserRGBQuad)
{
	CopyClipboard(cbmpNodeIn.c_arr_const(), cbmpNodeIn.GetMaximumHeight(), cbmpNodeIn.GetMaximumWidth(), cbmpNodeIn.GetBitCount(), *cbmpNodeIn.GetBimapInfoHeader(), cUserRGBQuad);
}

//*description   : Ŭ������� �����ϱ�(nFlag�� �⺻������ FLAG_SELECT_INPUT ��, �Է� ���� �̹����� ������)
//*@param input  : unsigned char	*m_CpyImg
//*@param input  : int				height
//*@param input  : int				width
//*@param input  : int				biBitCount 
//*@param input  : int				nFlag
//*@param output : -
//*@return		 :  
//*/
void CBitmapClipBoard::CopyClipboard(const unsigned char* m_CpyImg, int height, int width, int biBitCount, const BITMAPINFOHEADER& dibHi, CUserRGBQuad& cUserRGBQuad)
{
	if (m_CpyImg == NULL)
	{
		return;
	}

	if (height <= 0)
	{
		return;
	}

	if (width <= 0)
	{
		return;
	}

	if (biBitCount != 8 && biBitCount != 24)
	{
		return;
	}

	// Ŭ�����忡 �����ϱ� ���� ������ ���̸� ����
	int rwsize = WIDTHBYTES(biBitCount * width);
	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE + rwsize * height * sizeof(unsigned char); //

	// �޸� �Ҵ�(������常 ���ܽ�Ų ����)
	HGLOBAL m_hImage = NULL;
	LPSTR pDIB = NULL;

	m_hImage = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);

	if (m_hImage == NULL)
	{
		return;
	}

	pDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hImage);

	if (pDIB == NULL)
	{
		return;
	}

	// ����Ÿ���� 
	BITMAPINFOHEADER dibCpyHi;

	memcpy(&dibCpyHi, &dibHi, sizeof(BITMAPINFOHEADER));

	dibCpyHi.biBitCount = biBitCount;
	dibCpyHi.biHeight = height;
	dibCpyHi.biWidth = width;
	dibCpyHi.biSizeImage = height * rwsize;

	if (biBitCount == 8) dibCpyHi.biClrUsed = dibCpyHi.biClrImportant = MAXIMUM_PIXEL_VALUE;

	// �ڵ� �������� ���ؼ� ���� ������ �߻� ���� ����. 
	// ���� Ȯ�� �ʿ�
	memcpy(pDIB, &dibCpyHi, sizeof(BITMAPINFOHEADER));

	if (biBitCount == 8)
	{
		memcpy(pDIB + sizeof(BITMAPINFOHEADER), cUserRGBQuad.Get(), sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE);
		memcpy(pDIB + dwBitsSize - dibCpyHi.biSizeImage, m_CpyImg, dibCpyHi.biSizeImage);
	}
	else memcpy(pDIB + sizeof(BITMAPINFOHEADER), m_CpyImg, dibCpyHi.biSizeImage);

	// Ŭ������ ���� 
	::OpenClipboard(NULL);
	::SetClipboardData(CF_DIB, m_hImage);
	::CloseClipboard();

	::GlobalUnlock((HGLOBAL)m_hImage);
	GlobalFree(m_hImage);
}

///**
//*description   : ��Ʈ�� ���� ä���
//*@param input  : LPSTR pDIB 
//*@param output : CBitmapNode& bmpNode
//*@return		 : ���� ���� ����( true : ���� ����, false : ���� �߻� )
//*/
bool CBitmapClipBoard::OpenImageFromClipBoard(LPSTR pDIB, CUserBitmap& bmpNode)
{
	BITMAPINFOHEADER DibHi;
	BITMAPFILEHEADER DibHf;
	memset(&DibHi, 0, sizeof(BITMAPINFOHEADER));
	memset(&DibHf, 0, sizeof(BITMAPFILEHEADER));

	if (pDIB == NULL)
	{
		return false;
	}

	memcpy(&DibHi, pDIB, sizeof(BITMAPINFOHEADER));

	int rwsize = WIDTHBYTES(DibHi.biBitCount * DibHi.biWidth);

	DWORD dwBitsSize = (sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE + rwsize * DibHi.biHeight * sizeof(char));

	std::vector<unsigned char> pUcBmpImage;
	pUcBmpImage.resize(DibHi.biSizeImage);
	std::fill(pUcBmpImage.begin(), pUcBmpImage.end(), 0);

	if (DibHi.biBitCount == 8)
	{
		memcpy(pUcBmpImage.data(), pDIB + dwBitsSize - DibHi.biSizeImage, DibHi.biSizeImage);
	}
	else
	{
		memcpy(pUcBmpImage.data(), pDIB + sizeof(BITMAPINFOHEADER), DibHi.biSizeImage);
	}

	// BITMAP Filer Header�Ķ��Ÿ�� ���� 
	DibHf.bfType = 0x4d42;  // 'BM'
	DibHf.bfSize = dwBitsSize + sizeof(BITMAPFILEHEADER); // ��ü���� ũ�� 

	if (DibHi.biBitCount == 24) DibHf.bfSize -= sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE; // no pallette 

	DibHf.bfOffBits = DibHf.bfSize - rwsize * DibHi.biHeight * sizeof(char);
	DibHf.bfReserved1 = DibHf.bfReserved2 = 0;

	if (bmpNode.SetImage(pUcBmpImage.data(), &DibHi, &DibHf) == false)
	{
		return false;
	}

	return true;
}
