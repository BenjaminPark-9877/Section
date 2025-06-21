/////** 
////*description   : 비트맵 영상을 처리하는 객체 정의 소스 파일
////*               
////* 
////*/

#include "pch.h"
#include "BitmapClipBoard.h"

//------------------------
// CBitmapClipBoard 구현
//------------------------

bool CBitmapClipBoard::NewDocument(CUserBitmap& cbmpNodeIn, CUserRGBQuad& cUserRGBQuad)
{
    if (!::OpenClipboard(nullptr)) return false;
    if (!IsClipboardFormatAvailable(CF_DIB))
    {
        ::CloseClipboard();
        return false;
    }

    HGLOBAL m_hImage = ::GetClipboardData(CF_DIB);
    if (m_hImage == nullptr)
    {
        ::CloseClipboard();
        return false;
    }

    LPSTR pDIB = (LPSTR)::GlobalLock(m_hImage);
    ::CloseClipboard();

    if (pDIB == nullptr) return false;

    bool ret = OpenImageFromClipBoard(pDIB, cbmpNodeIn);

    ::GlobalUnlock(m_hImage);

    if (ret && cbmpNodeIn.GetBitCount() == 8)
    {
        cUserRGBQuad.Set(pDIB + sizeof(BITMAPINFOHEADER));
    }

    return ret;
}

void CBitmapClipBoard::CopyClipboard(const CUserBitmap& cbmpNodeIn, CUserRGBQuad& cUserRGBQuad)
{
    CopyClipboard(cbmpNodeIn.GetImage().data(), cbmpNodeIn.GetMaximumHeight(), cbmpNodeIn.GetMaximumWidth(),
        cbmpNodeIn.GetBitCount(), *cbmpNodeIn.GetBitmapInfoHeader(), cUserRGBQuad);
}

void CBitmapClipBoard::CopyClipboard(const unsigned char* m_CpyImg, int height, int width, int biBitCount,
    const BITMAPINFOHEADER& dibHi, CUserRGBQuad& cUserRGBQuad)
{
    if (!m_CpyImg || height <= 0 || width <= 0 || (biBitCount != 8 && biBitCount != 24)) return;

    size_t rwsize = WIDTHBYTES(biBitCount * width);
    DWORD dwBitsSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE + rwsize * height;

    HGLOBAL m_hImage = ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize);
    if (m_hImage == nullptr) return;

    LPSTR pDIB = (LPSTR)::GlobalLock(m_hImage);
    if (pDIB == nullptr)
    {
        ::GlobalFree(m_hImage);
        return;
    }

    BITMAPINFOHEADER dibCpyHi = dibHi;
    dibCpyHi.biBitCount = biBitCount;
    dibCpyHi.biHeight = height;
    dibCpyHi.biWidth = width;
    dibCpyHi.biSizeImage = height * rwsize;
    if (biBitCount == 8)
    {
        dibCpyHi.biClrUsed = dibCpyHi.biClrImportant = MAXIMUM_PIXEL_VALUE;
    }

    memcpy(pDIB, &dibCpyHi, sizeof(BITMAPINFOHEADER));
    if (biBitCount == 8)
    {
        memcpy(pDIB + sizeof(BITMAPINFOHEADER), cUserRGBQuad.Get(), sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE);
        memcpy(pDIB + dwBitsSize - dibCpyHi.biSizeImage, m_CpyImg, dibCpyHi.biSizeImage);
    }
    else
    {
        memcpy(pDIB + sizeof(BITMAPINFOHEADER), m_CpyImg, dibCpyHi.biSizeImage);
    }

    ::OpenClipboard(nullptr);
    ::EmptyClipboard();
    ::SetClipboardData(CF_DIB, m_hImage);
    ::CloseClipboard();

    ::GlobalUnlock(m_hImage);
    ::GlobalFree(m_hImage);
}

bool CBitmapClipBoard::OpenImageFromClipBoard(LPSTR pDIB, CUserBitmap& bmpNode)
{
    if (pDIB == nullptr) return false;

    BITMAPINFOHEADER DibHi = {};
    BITMAPFILEHEADER DibHf = {};
    memcpy(&DibHi, pDIB, sizeof(BITMAPINFOHEADER));

    size_t rwsize = WIDTHBYTES(DibHi.biBitCount * DibHi.biWidth);
    DWORD dwBitsSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE + rwsize * DibHi.biHeight;

    std::vector<unsigned char> pUcBmpImage(DibHi.biSizeImage, 0);

    if (DibHi.biBitCount == 8)
    {
        memcpy(pUcBmpImage.data(), pDIB + dwBitsSize - DibHi.biSizeImage, DibHi.biSizeImage);
    }
    else
    {
        memcpy(pUcBmpImage.data(), pDIB + sizeof(BITMAPINFOHEADER), DibHi.biSizeImage);
    }

    DibHf.bfType = 0x4D42;  // 'BM'
    DibHf.bfSize = dwBitsSize + sizeof(BITMAPFILEHEADER);
    if (DibHi.biBitCount == 24) DibHf.bfSize -= sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE;
    DibHf.bfOffBits = DibHf.bfSize - rwsize * DibHi.biHeight;
    DibHf.bfReserved1 = DibHf.bfReserved2 = 0;

    return bmpNode.SetImage(pUcBmpImage.data(), &DibHi, &DibHf);
}