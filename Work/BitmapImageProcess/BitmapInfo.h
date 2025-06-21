#ifndef _BITMAPINFO_H_
#define _BITMAPINFO_H_

#ifndef _BASICBONE_H_
#include "BasicBone.h"
#endif //_BASICBONE_H_

#include <Windows.h>  // BITMAPINFO, BITMAPINFOHEADER ����
#include <algorithm>   // std::copy

class CBitmapInfo : private CBasicBone
{
private:
    BITMAPINFO m_BitmapInfo;

public:
    // ������
    CBitmapInfo()
    {
        Clear();
    }

    // ���� ������
    CBitmapInfo(const CBitmapInfo& rhs)
    {
        std::copy(reinterpret_cast<const char*>(&rhs.m_BitmapInfo),
            reinterpret_cast<const char*>(&rhs.m_BitmapInfo) + sizeof(BITMAPINFO),
            reinterpret_cast<char*>(&m_BitmapInfo));
    }

    // ���� ������
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

    // �Ҹ���
    ~CBitmapInfo() = default;

    // BITMAPINFO ������ ��ȯ (�����)
    const BITMAPINFO* GetBitmapInfo() const { return &m_BitmapInfo; }

    // BITMAPINFO ������ ��ȯ (������)
    BITMAPINFO* GetBitmapInfo() { return &m_BitmapInfo; }

    // BITMAPINFOHEADER ������ ��ȯ (�����)
    const BITMAPINFOHEADER* GetBitmapInfoHeader() const { return &m_BitmapInfo.bmiHeader; }

    // BITMAPINFOHEADER ������ ��ȯ (������)
    BITMAPINFOHEADER* GetBitmapInfoHeader() { return &m_BitmapInfo.bmiHeader; }

    // BITMAPINFO ���� (����)
    bool Set(const BITMAPINFO& bmpInfo)
    {
        std::copy(reinterpret_cast<const char*>(&bmpInfo),
            reinterpret_cast<const char*>(&bmpInfo) + sizeof(BITMAPINFO),
            reinterpret_cast<char*>(&m_BitmapInfo));
        return true;
    }

    // BITMAPINFO ���� (������)
    bool Set(const BITMAPINFO* pBmpInfo)
    {
        if (!pBmpInfo) return false;
        std::copy(reinterpret_cast<const char*>(pBmpInfo),
            reinterpret_cast<const char*>(pBmpInfo) + sizeof(BITMAPINFO),
            reinterpret_cast<char*>(&m_BitmapInfo));
        return true;
    }

    // BITMAPINFOHEADER ���� (����)
    bool Set(const BITMAPINFOHEADER& bmpInfoHeader)
    {
        std::copy(reinterpret_cast<const char*>(&bmpInfoHeader),
            reinterpret_cast<const char*>(&bmpInfoHeader) + sizeof(BITMAPINFOHEADER),
            reinterpret_cast<char*>(&m_BitmapInfo.bmiHeader));
        return true;
    }

    // BITMAPINFOHEADER ���� (������)
    bool Set(const BITMAPINFOHEADER* pBmpInfoHeader)
    {
        if (!pBmpInfoHeader) return false;
        std::copy(reinterpret_cast<const char*>(pBmpInfoHeader),
            reinterpret_cast<const char*>(pBmpInfoHeader) + sizeof(BITMAPINFOHEADER),
            reinterpret_cast<char*>(&m_BitmapInfo.bmiHeader));
        return true;
    }

    // �̹��� �� ��ȯ
    LONG GetMaximumWidth() const
    {
        return m_BitmapInfo.bmiHeader.biWidth;
    }

    // �̹��� ���� ��ȯ
    LONG GetMaximumHeight() const
    {
        return m_BitmapInfo.bmiHeader.biHeight;
    }

    // 1�� ���� ����Ʈ ũ�� ��ȯ (DWORD ���� ����)
    unsigned long GetRwSize() const
    {
        int bitCount = m_BitmapInfo.bmiHeader.biBitCount;
        unsigned long width = static_cast<unsigned long>(GetMaximumWidth());
        return ((width * bitCount + 31) / 32) * 4;
    }

    // ��Ʈ �� ��ȯ
    int GetBitCount() const
    {
        return static_cast<int>(m_BitmapInfo.bmiHeader.biBitCount);
    }

    // ��ü �̹��� ũ�� ��ȯ (����Ʈ ����)
    unsigned long GetTotalSize() const
    {
        return GetRwSize() * GetMaximumHeight();
    }

    // �ʱ�ȭ
    void Clear()
    {
        std::memset(&m_BitmapInfo, 0, sizeof(BITMAPINFO));
        m_BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    }
};

#endif //_BITMAPINFO_H_
