// IBitmapIO.h
#pragma once
#ifndef _IBITMAPIO_H_
#define _IBITMAPIO_H_

#include "UserBitmap.h"
#include <string>

class IBitmapIO : public CBasicBone
{
public:
    // �⺻ ������ �߰� (�ʿ��ϸ� ����)
    IBitmapIO() = default;

    virtual ~IBitmapIO() = default;

    // �̹��� �б� (���� ���, CUserBitmap ���� ����)
    virtual bool Open(const std::string& filepath, CUserBitmap& bmpNode, RGBQUAD* palRGB = nullptr) = 0;

    // �̹��� ���� (���� ���, CUserBitmap ���� ����)
    virtual bool Save(const std::string& filepath, const CUserBitmap& bmpNode, RGBQUAD* palRGB = nullptr) = 0;

    // �̹��� �б� (���� ���, CUserBitmap ���� ����)
    //virtual bool ReadImage(const std::string& filepath, CUserBitmap& bmpNode) = 0;

    // �̹��� ���� (���� ���, CUserBitmap ���� ����)
    //virtual bool WriteImage(const std::string& filepath, const CUserBitmap& bmpNode) = 0;

    /// ���� ������ �� ���� ���� ������ ����
    IBitmapIO(const IBitmapIO&) = delete;
    IBitmapIO& operator=(const IBitmapIO&) = delete;

    //// �̵� ������ �� �̵� ���� ������ ����
    IBitmapIO(IBitmapIO&&) = delete;
    IBitmapIO& operator=(IBitmapIO&&) = delete;
};

#endif //_IBITMAPIO_H_


