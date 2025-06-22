// IBitmapIO.h
#pragma once
#ifndef _IBITMAPIO_H_
#define _IBITMAPIO_H_

#include "UserBitmap.h"
#include <string>

class IBitmapIO : public CBasicBone
{
public:
    // 기본 생성자 추가 (필요하면 구현)
    IBitmapIO() = default;

    virtual ~IBitmapIO() = default;

    // 이미지 읽기 (파일 경로, CUserBitmap 참조 전달)
    virtual bool Open(const std::string& filepath, CUserBitmap& bmpNode, RGBQUAD* palRGB = nullptr) = 0;

    // 이미지 쓰기 (파일 경로, CUserBitmap 참조 전달)
    virtual bool Save(const std::string& filepath, const CUserBitmap& bmpNode, RGBQUAD* palRGB = nullptr) = 0;

    // 이미지 읽기 (파일 경로, CUserBitmap 참조 전달)
    //virtual bool ReadImage(const std::string& filepath, CUserBitmap& bmpNode) = 0;

    // 이미지 쓰기 (파일 경로, CUserBitmap 참조 전달)
    //virtual bool WriteImage(const std::string& filepath, const CUserBitmap& bmpNode) = 0;

    /// 복사 생성자 및 복사 대입 연산자 금지
    IBitmapIO(const IBitmapIO&) = delete;
    IBitmapIO& operator=(const IBitmapIO&) = delete;

    //// 이동 생성자 및 이동 대입 연산자 금지
    IBitmapIO(IBitmapIO&&) = delete;
    IBitmapIO& operator=(IBitmapIO&&) = delete;
};

#endif //_IBITMAPIO_H_


