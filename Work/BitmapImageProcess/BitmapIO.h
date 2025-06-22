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

class CBitmapIO : public IBitmapIO  // IBitmapIO�κ��� ���
{
public:
    CBitmapIO() 
    {
        CBasicBone();// CBasicBone ������ ȣ��
        // �߰� �ʱ�ȭ �ڵ�        
    }
    ~CBitmapIO() = default; // �⺻ �Ҹ���

    bool Open(const std::string& filepath, CUserBitmap& bmpNode, RGBQUAD* palRGB = nullptr) override;
    bool Save(const std::string& filepath, const CUserBitmap& bmpNode, RGBQUAD* palRGB = nullptr) override;

protected:
    CString AddExtendString(const std::string& filepath);
    bool ReadImageData(CFile& file, std::vector<unsigned char>& imageData, size_t dataSize);
    bool WriteImageData(CFile& file, const CUserBitmap& bmpNode);
    bool OpenFile(const std::string& filepath, CFile& file);
};

#endif //_BITMAPIO_H_