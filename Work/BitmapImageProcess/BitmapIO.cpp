// BitmapIO.cpp
#include "pch.h"
#include "BitmapIO.h"

bool CBitmapIO::Open(LPCTSTR lpszPathName, CUserBitmap& bmpNode, RGBQUAD* palRGB)
{
    BITMAPINFOHEADER DibHi = {};
    BITMAPFILEHEADER DibHf = {};

    if (!lpszPathName || _tcslen(lpszPathName) == 0)
        return false;

    CFile hFile;
    if (!hFile.Open(lpszPathName, CFile::modeRead | CFile::typeBinary))
        return false;

    hFile.Read(&DibHf, sizeof(BITMAPFILEHEADER));
    if (DibHf.bfType != 0x4D42) // 'BM'
        return false;

    hFile.Read(&DibHi, sizeof(BITMAPINFOHEADER));
    if (DibHi.biBitCount != 8 && DibHi.biBitCount != 24)
        return false;

    if (DibHi.biBitCount == 8 && palRGB)
        hFile.Read(palRGB, sizeof(RGBQUAD) * 256);

    int ImgSize = 0;
    if (DibHi.biBitCount == 8 && palRGB)
        ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - sizeof(RGBQUAD) * 256;
    else
        ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);

    std::vector<unsigned char> pUcBmpImage(ImgSize);
    hFile.Read(pUcBmpImage.data(), ImgSize);
    hFile.Close();

    if (DibHi.biBitCount == 8 && palRGB)
    {
        size_t rwsize = WIDTHBYTES(DibHi.biBitCount * DibHi.biWidth);
        for (size_t i = 0; i < static_cast<size_t>(DibHi.biHeight); ++i)
        {
            size_t index = i * rwsize;
            for (size_t j = 0; j < static_cast<size_t>(DibHi.biWidth); ++j)
            {
                int palIndex = static_cast<int>(pUcBmpImage[index + j]);
                pUcBmpImage[index + j] = palRGB[palIndex].rgbBlue;
            }
        }
    }

    bmpNode.SetImage(pUcBmpImage.data(), &DibHi, &DibHf);
    return true;
}

bool CBitmapIO::Save(LPCTSTR lpszPathName, CUserBitmap& bmpNode, RGBQUAD* palRGB)
{
    try
    {
        if (!lpszPathName || _tcslen(lpszPathName) == 0)
            return false;

        CString cStrPathName = AddExtendString(lpszPathName);
        CFile hFile;

        if (!hFile.Open(cStrPathName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
            return false;

        hFile.Write(bmpNode.GetBitmapFileHeader(), sizeof(BITMAPFILEHEADER));
        hFile.Write(bmpNode.GetBitmapInfoHeader(), sizeof(BITMAPINFOHEADER));

        if (bmpNode.GetBitmapInfoHeader()->biBitCount == 8 && palRGB)
            hFile.Write(palRGB, sizeof(RGBQUAD) * 256);

        hFile.Write(bmpNode.GetImage().data(), bmpNode.GetBitmapInfoHeader()->biSize);
        hFile.Close();

        return true;
    }
    catch (...)
    {
        return false;
    }
}

CString CBitmapIO::AddExtendString(CString lpszPathName)
{
    CString cStrPathName = CString(lpszPathName).Trim();
    CString cStrExt = cStrPathName.Right(4);

    if (cStrExt.CompareNoCase(STR_DEFAULT_EXTEND_NAME))
        cStrPathName += STR_DEFAULT_EXTEND_NAME;

    return cStrPathName;
}
