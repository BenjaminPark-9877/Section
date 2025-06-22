#include "pch.h"
#include "BitmapIO.h"
#include <iostream>
#include <stdexcept>

bool CBitmapIO::Open(const std::string& filepath, CUserBitmap& bmpNode, RGBQUAD* palRGB)
{
    BITMAPINFOHEADER DibHi = {};
    BITMAPFILEHEADER DibHf = {};

    if (filepath.empty())
        return false;

    CFile hFile;
    CString cstrPath(filepath.c_str()); // std::string to CString
    if (!hFile.Open(cstrPath, CFile::modeRead | CFile::typeBinary))
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


bool CBitmapIO::Save(const std::string& filepath, const CUserBitmap& bmpNode, RGBQUAD* palRGB)
{
    try
    {
        if (filepath.empty())
            return false;

        CString cstrPath = AddExtendString(filepath);
        CFile hFile;

        if (!hFile.Open(cstrPath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
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

CString CBitmapIO::AddExtendString(const std::string& filepath)
{
    CString cstrPath(filepath.c_str());
    CString cstrExt = cstrPath.Right(4);

    if (cstrExt.CompareNoCase(_T(".bmp")) != 0)
        cstrPath += _T(".bmp");

    return cstrPath;
}

bool CBitmapIO::OpenFile(const std::string& filepath, CFile& file)
{
    try
    {
        // std::string을 CString으로 변환
        CString cstrFilePath(filepath.c_str());

        // 파일 열기
        file.Open(cstrFilePath, CFile::modeRead | CFile::typeBinary);
        return true;
    }
    catch (CFileException* e)
    {
        std::cerr << "Failed to open file: " << e->m_strFileName.GetString() << std::endl;
        e->Delete();
        return false;
    }
}

bool CBitmapIO::ReadImageData(CFile& file, std::vector<unsigned char>& imageData, size_t dataSize)
{
    try
    {
        file.Read(imageData.data(), dataSize);
        return true;
    }
    catch (...)
    {
        std::cerr << "Error reading image data." << std::endl;
        return false;
    }
}

bool CBitmapIO::WriteImageData(CFile& file, const CUserBitmap& bmpNode)
{
    try
    {
        file.Write(bmpNode.GetBitmapFileHeader(), sizeof(BITMAPFILEHEADER));
        file.Write(bmpNode.GetBitmapInfoHeader(), sizeof(BITMAPINFOHEADER));
        return true;
    }
    catch (...)
    {
        std::cerr << "Error writing image data." << std::endl;
        return false;
    }
}
