#ifndef _BITMAPINFO_H_
#define _BITMAPINFO_H_

#ifndef _BASICBONE_H_
#include "BasicBone.h"
#endif //_BASICBONE_H_

#include <Windows.h>  // BITMAPINFO, BITMAPINFOHEADER ����
#include <cstring>     // std::memset, std::memcpy

class CBitmapInfo : public CBasicBone
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
        std::memcpy(&m_BitmapInfo, &rhs.m_BitmapInfo, sizeof(BITMAPINFO));
    }

    // ���� ������
    CBitmapInfo& operator=(const CBitmapInfo& rhs)
    {
        if (this != &rhs)
        {
            std::memcpy(&m_BitmapInfo, &rhs.m_BitmapInfo, sizeof(BITMAPINFO));
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

    // BITMAPINFO ����
    bool Set(const BITMAPINFO& bmpInfo)
    {
        std::memcpy(&m_BitmapInfo, &bmpInfo, sizeof(BITMAPINFO));
        return true;
    }

    // BITMAPINFO ���� (������)
    bool Set(const BITMAPINFO* pBmpInfo)
    {
        if (!pBmpInfo) return false;
        std::memcpy(&m_BitmapInfo, pBmpInfo, sizeof(BITMAPINFO));
        return true;
    }

    // BITMAPINFOHEADER ����
    bool Set(const BITMAPINFOHEADER& bmpInfoHeader)
    {
        std::memcpy(&m_BitmapInfo.bmiHeader, &bmpInfoHeader, sizeof(BITMAPINFOHEADER));
        return true;
    }

    // BITMAPINFOHEADER ���� (������)
    bool Set(const BITMAPINFOHEADER* pBmpInfoHeader)
    {
        if (!pBmpInfoHeader) return false;
        std::memcpy(&m_BitmapInfo.bmiHeader, pBmpInfoHeader, sizeof(BITMAPINFOHEADER));
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