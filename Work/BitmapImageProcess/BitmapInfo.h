#ifndef _BITMAPINFO_H_
#define _BITMAPINFO_H_

#ifndef _BASICBONE_H_
#include "BasicBone.h"
#endif //_BASICBONE_H_

#include <Windows.h>  // BITMAPINFO, BITMAPINFOHEADER 정의
#include <algorithm>   // std::copy

class CBitmapInfo : private CBasicBone
{
private:
    BITMAPINFO m_BitmapInfo;

public:
    // 생성자
    CBitmapInfo()
    {
        Clear();
    }

    // 복사 생성자
    CBitmapInfo(const CBitmapInfo& rhs)
    {
        std::copy(reinterpret_cast<const char*>(&rhs.m_BitmapInfo),
            reinterpret_cast<const char*>(&rhs.m_BitmapInfo) + sizeof(BITMAPINFO),
            reinterpret_cast<char*>(&m_BitmapInfo));
    }

    // 대입 연산자
    CBitmapInfo& operator=(const CBitmapInfo& rhs)
    {
        if (this != &rhs)
        {
            std::copy(reinterpret_cast<const char*>(&rhs.m_BitmapInfo),
                reinterpret_cast<const char*>(&rhs.m_BitmapInfo) + sizeof(BITMAPINFO),
                reinterpret_cast<char*>(&m_BitmapInfo));
        }
        return *this;
    }

    // 소멸자
    ~CBitmapInfo() = default;

    // BITMAPINFO 포인터 반환 (상수형)
    const BITMAPINFO* GetBitmapInfo() const { return &m_BitmapInfo; }

    // BITMAPINFO 포인터 반환 (비상수형)
    BITMAPINFO* GetBitmapInfo() { return &m_BitmapInfo; }

    // BITMAPINFOHEADER 포인터 반환 (상수형)
    const BITMAPINFOHEADER* GetBitmapInfoHeader() const { return &m_BitmapInfo.bmiHeader; }

    // BITMAPINFOHEADER 포인터 반환 (비상수형)
    BITMAPINFOHEADER* GetBitmapInfoHeader() { return &m_BitmapInfo.bmiHeader; }

    // BITMAPINFO 설정 (참조)
    bool Set(const BITMAPINFO& bmpInfo)
    {
        std::copy(reinterpret_cast<const char*>(&bmpInfo),
            reinterpret_cast<const char*>(&bmpInfo) + sizeof(BITMAPINFO),
            reinterpret_cast<char*>(&m_BitmapInfo));
        return true;
    }

    // BITMAPINFO 설정 (포인터)
    bool Set(const BITMAPINFO* pBmpInfo)
    {
        if (!pBmpInfo) return false;
        std::copy(reinterpret_cast<const char*>(pBmpInfo),
            reinterpret_cast<const char*>(pBmpInfo) + sizeof(BITMAPINFO),
            reinterpret_cast<char*>(&m_BitmapInfo));
        return true;
    }

    // BITMAPINFOHEADER 설정 (참조)
    bool Set(const BITMAPINFOHEADER& bmpInfoHeader)
    {
        std::copy(reinterpret_cast<const char*>(&bmpInfoHeader),
            reinterpret_cast<const char*>(&bmpInfoHeader) + sizeof(BITMAPINFOHEADER),
            reinterpret_cast<char*>(&m_BitmapInfo.bmiHeader));
        return true;
    }

    // BITMAPINFOHEADER 설정 (포인터)
    bool Set(const BITMAPINFOHEADER* pBmpInfoHeader)
    {
        if (!pBmpInfoHeader) return false;
        std::copy(reinterpret_cast<const char*>(pBmpInfoHeader),
            reinterpret_cast<const char*>(pBmpInfoHeader) + sizeof(BITMAPINFOHEADER),
            reinterpret_cast<char*>(&m_BitmapInfo.bmiHeader));
        return true;
    }

    // 이미지 폭 반환
    LONG GetMaximumWidth() const
    {
        return m_BitmapInfo.bmiHeader.biWidth;
    }

    // 이미지 높이 반환
    LONG GetMaximumHeight() const
    {
        return m_BitmapInfo.bmiHeader.biHeight;
    }

    // 1줄 실제 바이트 크기 반환 (DWORD 정렬 포함)
    unsigned long GetRwSize() const
    {
        int bitCount = m_BitmapInfo.bmiHeader.biBitCount;
        unsigned long width = static_cast<unsigned long>(GetMaximumWidth());
        return ((width * bitCount + 31) / 32) * 4;
    }

    // 비트 수 반환
    int GetBitCount() const
    {
        return static_cast<int>(m_BitmapInfo.bmiHeader.biBitCount);
    }

    // 전체 이미지 크기 반환 (바이트 단위)
    unsigned long GetTotalSize() const
    {
        return GetRwSize() * GetMaximumHeight();
    }

    // 초기화
    void Clear()
    {
        std::memset(&m_BitmapInfo, 0, sizeof(BITMAPINFO));
        m_BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    }
};

#endif //_BITMAPINFO_H_
