#include "pch.h"
#include "BitmapIO.h"
#include <iostream>
#include <stdexcept>

CBitmapIO::CBitmapIO() {
    // CBasicBone 생성자 호출 및 초기화
    CBasicBone();
}

bool CBitmapIO::Open(const std::string& filepath, CUserBitmap& bmpNode, RGBQUAD* palRGB)
{
    BITMAPINFOHEADER DibHi = {};
    BITMAPFILEHEADER DibHf = {};

    if (filepath.empty())
        return false;

    CFile hFile;
    CString cstrPath(filepath.c_str());
    if (!OpenFile(filepath, hFile))
        return false;

    try {
        ReadBitmapHeaders(hFile, DibHf, DibHi);

        int ImgSize = CalculateImageSize(DibHi, hFile);
        std::vector<unsigned char> pUcBmpImage(ImgSize);
        ReadImageData(hFile, pUcBmpImage, ImgSize);

        if (DibHi.biBitCount == 8 && palRGB) {
            Process8BitImage(pUcBmpImage, DibHi, palRGB);
        }

        bmpNode.SetImage(pUcBmpImage.data(), &DibHi, &DibHf);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error opening file [" << filepath << "]: " << e.what() << std::endl;
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
        std::cerr << "Error saving file [" << filepath << "]: " << e.what() << std::endl;
        return false;
    }
}

CString CBitmapIO::AddExtendString(const std::string& filepath)
{
    CString cstrPath(filepath.c_str());
    CString cstrExt = cstrPath.Right(4);  // 확장자 부분을 추출 (".bmp")

    // 확장자가 ".bmp"인지 확인
    if (cstrExt.CompareNoCase(_T(".bmp")) != 0) {
        cstrPath += _T(".bmp");  // 없으면 .bmp 추가
    }

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
    catch (const CFileException& e)
    {
        std::cerr << "Failed to open file [" << filepath << "]: "
            << e.m_strFileName.GetString() << " with error code "
            << e.m_cause << std::endl;
        return false;
    }
}

bool CBitmapIO::ReadBitmapHeaders(CFile& file, BITMAPFILEHEADER& DibHf, BITMAPINFOHEADER& DibHi)
{
    file.Read(&DibHf, sizeof(BITMAPFILEHEADER));
    if (DibHf.bfType != 0x4D42)  // 'BM'
        throw std::runtime_error("Invalid file format");

    file.Read(&DibHi, sizeof(BITMAPINFOHEADER));
    if (DibHi.biBitCount != 8 && DibHi.biBitCount != 24)
        throw std::runtime_error("Unsupported bit count");

    return true;
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

void CBitmapIO::Process8BitImage(std::vector<unsigned char>& pUcBmpImage, const BITMAPINFOHEADER& DibHi, RGBQUAD* palRGB)
{
    size_t rwsize = WIDTHBYTES(DibHi.biBitCount * DibHi.biWidth);
    for (size_t i = 0; i < static_cast<size_t>(DibHi.biHeight); ++i) {
        size_t index = i * rwsize;
        for (size_t j = 0; j < static_cast<size_t>(DibHi.biWidth); ++j) {
            int palIndex = static_cast<int>(pUcBmpImage[index + j]);
            pUcBmpImage[index + j] = palRGB[palIndex].rgbBlue;
        }
    }
}

int CBitmapIO::CalculateImageSize(const BITMAPINFOHEADER& DibHi, CFile& hFile)
{
    return (DibHi.biBitCount == 8)
        ? hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - sizeof(RGBQUAD) * 256
        : hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
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
