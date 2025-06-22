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
    CString cstrPath(filepath.c_str());
    if (!hFile.Open(cstrPath, CFile::modeRead | CFile::typeBinary))
        return false;

    try {
        hFile.Read(&DibHf, sizeof(BITMAPFILEHEADER));
        if (DibHf.bfType != 0x4D42) // 'BM'
            throw std::runtime_error("Invalid file format");

        hFile.Read(&DibHi, sizeof(BITMAPINFOHEADER));
        if (DibHi.biBitCount != 8 && DibHi.biBitCount != 24)
            throw std::runtime_error("Unsupported bit count");

        if (DibHi.biBitCount == 8 && palRGB)
            hFile.Read(palRGB, sizeof(RGBQUAD) * 256);

        int ImgSize = (DibHi.biBitCount == 8 && palRGB)
            ? hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - sizeof(RGBQUAD) * 256
            : hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);

        std::vector<unsigned char> pUcBmpImage(ImgSize);
        hFile.Read(pUcBmpImage.data(), ImgSize);

        if (DibHi.biBitCount == 8 && palRGB) {
            size_t rwsize = WIDTHBYTES(DibHi.biBitCount * DibHi.biWidth);
            for (size_t i = 0; i < static_cast<size_t>(DibHi.biHeight); ++i) {
                size_t index = i * rwsize;
                for (size_t j = 0; j < static_cast<size_t>(DibHi.biWidth); ++j) {
                    int palIndex = static_cast<int>(pUcBmpImage[index + j]);
                    pUcBmpImage[index + j] = palRGB[palIndex].rgbBlue;
                }
            }
        }

        bmpNode.SetImage(pUcBmpImage.data(), &DibHi, &DibHf);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error opening file: " << e.what() << std::endl;
        return false;
    }

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

        WriteImageData(hFile, bmpNode, palRGB);
        hFile.Close();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error saving file: " << e.what() << std::endl;
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
        CString cstrFilePath(filepath.c_str());
        file.Open(cstrFilePath, CFile::modeRead | CFile::typeBinary);
        return true;
    }
    catch (const CFileException& e) // 포인터가 아니라 참조로 잡음
    {
        std::cerr << "Failed to open file: " << e.m_strFileName.GetString() << std::endl;
        //e->Delete(); //CFileException 객체는 예외가 발생한 후 catch 블록에서 자동으로 관리됩니다.
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
    catch (const std::exception& e)
    {
        std::cerr << "Error reading image data: " << e.what() << std::endl;
        return false;
    }
}

bool CBitmapIO::WriteImageData(CFile& file, const CUserBitmap& bmpNode, RGBQUAD* palRGB)
{
    try
    {
        file.Write(bmpNode.GetBitmapFileHeader(), sizeof(BITMAPFILEHEADER));
        file.Write(bmpNode.GetBitmapInfoHeader(), sizeof(BITMAPINFOHEADER));

        if (bmpNode.GetBitmapInfoHeader()->biBitCount == 8 && palRGB)
            file.Write(palRGB, sizeof(RGBQUAD) * 256);

        const auto& imageData = bmpNode.GetImage();
        file.Write(imageData.data(), imageData.size());
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error writing image data: " << e.what() << std::endl;
        return false;
    }
}
