#ifndef _BITMAPIO_H_
#define _BITMAPIO_H_

#pragma once

#include <winnt.h>
#include <vector>
#include "BasicBone.h"
#include "UserRGBQuad.h"
#include "BitmapFileHeader.h"
#include "IBitmapIO.h"
#include "UserBitmap.h"
#include <string>
#include <afx.h>  // For CFile

class CBitmapIO : public IBitmapIO  // IBitmapIO로부터 상속
{
public:
    CBitmapIO();
    ~CBitmapIO() = default;

    bool Open(const std::string& filepath, CUserBitmap& bmpNode, RGBQUAD* palRGB = nullptr) override;
    bool Save(const std::string& filepath, const CUserBitmap& bmpNode, RGBQUAD* palRGB = nullptr) override;

protected:
    CString AddExtendString(const std::string& filepath);
    bool OpenFile(const std::string& filepath, CFile& file);
    bool ReadBitmapHeaders(CFile& file, BITMAPFILEHEADER& DibHf, BITMAPINFOHEADER& DibHi);
    bool ReadImageData(CFile& file, std::vector<unsigned char>& imageData, size_t dataSize);
    bool WriteImageData(CFile& file, const CUserBitmap& bmpNode, RGBQUAD* palRGB);
    void Process8BitImage(std::vector<unsigned char>& pUcBmpImage, const BITMAPINFOHEADER& DibHi, RGBQUAD* palRGB);
    int CalculateImageSize(const BITMAPINFOHEADER& DibHi, CFile& hFile);
};

#endif //_BITMAPIO_H_
