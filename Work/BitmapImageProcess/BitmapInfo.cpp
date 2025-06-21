#include "pch.h"
#include "BitmapInfo.h"
#undef max


CBitmapInfo::CBitmapInfo()
    : m_pBitmapData(nullptr), m_dataSize(0)
{
}

CBitmapInfo::CBitmapInfo(const CBitmapInfo& other)
    : m_pBitmapData(nullptr), m_dataSize(0)
{
    Set(other);
}

CBitmapInfo& CBitmapInfo::operator=(const CBitmapInfo& other)
{
    if (this == &other) return *this;

    Set(other);
    return *this;
}

CBitmapInfo::~CBitmapInfo()
{
    Clear();
}

void CBitmapInfo::Clear()
{
    m_pBitmapData.reset();
    m_dataSize = 0;
}

bool CBitmapInfo::IsDataValid() const
{
    return m_pBitmapData != nullptr && m_dataSize > 0;
}

bool CBitmapInfo::Set(const BITMAPINFO& bmpInfo)
{
    return Set(&bmpInfo);
}

bool CBitmapInfo::Set(const BITMAPINFO* pBmpInfo)
{
    if (!pBmpInfo) return false;

    size_t size = sizeof(BITMAPINFOHEADER);
    if (pBmpInfo->bmiHeader.biClrUsed > 0)
    {
        size += pBmpInfo->bmiHeader.biClrUsed * sizeof(RGBQUAD);
    }
    else
    {
        // 기본 팔레트 크기 (비트 수에 따라 다를 수 있음)
        if (pBmpInfo->bmiHeader.biBitCount <= 8)
        {
            size += (1 << pBmpInfo->bmiHeader.biBitCount) * sizeof(RGBQUAD);
        }
    }

    size = std::max(size, sizeof(BITMAPINFOHEADER));
        
    m_pBitmapData = std::make_unique<BYTE[]>(size);
    if (!m_pBitmapData) return false;

    std::memcpy(m_pBitmapData.get(), pBmpInfo, size);
    m_dataSize = size;

    return true;
}

bool CBitmapInfo::Set(const BITMAPINFOHEADER& bmpInfoHeader)
{
    return Set(&bmpInfoHeader);
}

bool CBitmapInfo::Set(const BITMAPINFOHEADER* pBmpInfoHeader)
{
    if (!pBmpInfoHeader) return false;

    int size = sizeof(BITMAPINFOHEADER);
    m_pBitmapData = std::make_unique<BYTE[]>(size);
    if (!m_pBitmapData) return false;

    std::memcpy(m_pBitmapData.get(), pBmpInfoHeader, size);
    m_dataSize = size;

    return true;
}

bool CBitmapInfo::Set(const CBitmapInfo& other)
{
    if (!other.IsDataValid()) return false;

    m_pBitmapData = std::make_unique<BYTE[]>(other.m_dataSize);
    if (!m_pBitmapData) return false;

    std::memcpy(m_pBitmapData.get(), other.m_pBitmapData.get(), other.m_dataSize);
    m_dataSize = other.m_dataSize;

    return true;
}

BITMAPINFO* CBitmapInfo::GetBitmapInfo()
{
    return IsDataValid() ? reinterpret_cast<BITMAPINFO*>(m_pBitmapData.get()) : nullptr;
}

const BITMAPINFO* CBitmapInfo::GetBitmapInfo() const
{
    return IsDataValid() ? reinterpret_cast<const BITMAPINFO*>(m_pBitmapData.get()) : nullptr;
}

BITMAPINFOHEADER* CBitmapInfo::GetBitmapInfoHeader()
{
    if (!IsDataValid()) return nullptr;

    BITMAPINFO* pInfo = reinterpret_cast<BITMAPINFO*>(m_pBitmapData.get());
    return &pInfo->bmiHeader;
}

const BITMAPINFOHEADER* CBitmapInfo::GetBitmapInfoHeader() const
{
    if (!IsDataValid()) return nullptr;

    const BITMAPINFO* pInfo = reinterpret_cast<const BITMAPINFO*>(m_pBitmapData.get());
    return &pInfo->bmiHeader;
}

int CBitmapInfo::GetMaximumWidth() const
{
    const BITMAPINFOHEADER* header = GetBitmapInfoHeader();
    return header ? header->biWidth : 0;
}

int CBitmapInfo::GetMaximumHeight() const
{
    const BITMAPINFOHEADER* header = GetBitmapInfoHeader();
    return header ? abs(header->biHeight) : 0;
}

int CBitmapInfo::GetRwSize() const
{
    const BITMAPINFOHEADER* header = GetBitmapInfoHeader();
    return header ? header->biSizeImage : 0;
}

int CBitmapInfo::GetBitCount() const
{
    const BITMAPINFOHEADER* header = GetBitmapInfoHeader();
    return header ? header->biBitCount : 0;
}

int CBitmapInfo::GetTotalSize() const
{
    return m_dataSize;
}

// 추가된 메소드들

bool CBitmapInfo::HasColorTable() const
{
    const BITMAPINFOHEADER* header = GetBitmapInfoHeader();
    return header && (header->biBitCount <= 8 || header->biClrUsed > 0);
}

bool CBitmapInfo::IsColorIndexed() const
{
    const BITMAPINFOHEADER* header = GetBitmapInfoHeader();
    return header && header->biBitCount <= 8;
}

bool CBitmapInfo::IsValidBmp() const
{
    const BITMAPINFOHEADER* header = GetBitmapInfoHeader();
    return header && header->biSize == sizeof(BITMAPINFOHEADER);
}

void CBitmapInfo::ResetBitmapData()
{
    m_pBitmapData.reset();
    m_dataSize = 0;
}

void CBitmapInfo::SetColorTable(const RGBQUAD* pColorTable, size_t colorCount)
{
    if (!pColorTable || colorCount == 0) return;

    BITMAPINFO* pInfo = reinterpret_cast<BITMAPINFO*>(m_pBitmapData.get());
    if (!pInfo) return;

    pInfo->bmiHeader.biClrUsed = static_cast<UINT>(colorCount);
    std::memcpy(pInfo->bmiColors, pColorTable, colorCount * sizeof(RGBQUAD));
}
