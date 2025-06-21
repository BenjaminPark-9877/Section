#include "pch.h"
#include "UserBitmap.h"
#include <cstring>
#include <algorithm>  // std::copy

CUserBitmap::CUserBitmap() noexcept
    : m_optVecBmpImage(std::nullopt) // 초기화 안 된 상태
{}

CUserBitmap::~CUserBitmap()
{
    Clear();
}

CUserBitmap::CUserBitmap(const CUserBitmap& rhs)
{
    SetImage(rhs);
}

CUserBitmap& CUserBitmap::operator=(const CUserBitmap& rhs)
{
    if (this != &rhs)
        SetImage(rhs);
    return *this;
}

CUserBitmap::CUserBitmap(CUserBitmap&& rhs) noexcept
    : m_BmpInfo(std::move(rhs.m_BmpInfo))
    , m_DibHf(std::move(rhs.m_DibHf))
    , m_optVecBmpImage(std::move(rhs.m_optVecBmpImage))
{}

CUserBitmap& CUserBitmap::operator=(CUserBitmap&& rhs) noexcept
{
    if (this != &rhs) {
        m_BmpInfo = std::move(rhs.m_BmpInfo);
        m_DibHf = std::move(rhs.m_DibHf);
        m_optVecBmpImage = std::move(rhs.m_optVecBmpImage);
    }
    return *this;
}

void CUserBitmap::Clear() noexcept
{
    m_BmpInfo.Clear();
    m_DibHf.Clear();
    m_optVecBmpImage.reset(); // vector 초기화 상태 해제
}

const BITMAPINFO* CUserBitmap::GetBitmapInfo() const noexcept
{
    return m_BmpInfo.GetBitmapInfo();
}

const BITMAPINFOHEADER* CUserBitmap::GetBitmapInfoHeader() const noexcept
{
    return m_BmpInfo.GetBitmapInfoHeader();
}

bool CUserBitmap::GetBitmapInfoHeader(BITMAPINFOHEADER& out) const noexcept
{
    const auto* hdr = GetBitmapInfoHeader();
    if (!hdr) return false;
    out = *hdr;
    return true;
}

bool CUserBitmap::GetBitmapInfoHeader(BITMAPINFOHEADER* out) const noexcept
{
    if (!out) return false;
    const auto* hdr = GetBitmapInfoHeader();
    if (!hdr) return false;
    *out = *hdr;
    return true;
}

const BITMAPFILEHEADER* CUserBitmap::GetBitmapFileHeader() const noexcept
{
    return m_DibHf.GetBitmapFileHeader();
}

bool CUserBitmap::GetBitmapFileHeader(BITMAPFILEHEADER& out) const noexcept
{
    const auto* hdr = GetBitmapFileHeader();
    if (!hdr) return false;
    out = *hdr;
    return true;
}

bool CUserBitmap::GetBitmapFileHeader(BITMAPFILEHEADER* out) const noexcept
{
    if (!out) return false;
    const auto* hdr = GetBitmapFileHeader();
    if (!hdr) return false;
    *out = *hdr;
    return true;
}

unsigned long CUserBitmap::GetMaximumWidth() const noexcept
{
    return m_BmpInfo.GetMaximumWidth();
}

unsigned long CUserBitmap::GetMaximumHeight() const noexcept
{
    return m_BmpInfo.GetMaximumHeight();
}

unsigned long CUserBitmap::GetRwSize() const noexcept
{
    return m_BmpInfo.GetRwSize();
}

int CUserBitmap::GetBitCount() const noexcept
{
    return m_BmpInfo.GetBitCount();
}

unsigned long CUserBitmap::GetTotalSize() const noexcept
{
    return m_BmpInfo.GetTotalSize();
}

unsigned char& CUserBitmap::operator[](size_t pos)
{
    if (!m_optVecBmpImage)
        throw std::runtime_error("Image data not initialized");
    return m_optVecBmpImage->at(pos);
}

const unsigned char CUserBitmap::operator[](size_t pos) const
{
    if (!m_optVecBmpImage)
        throw std::runtime_error("Image data not initialized");
    return m_optVecBmpImage->at(pos);
}

#ifdef _DEBUG
unsigned char& CUserBitmap::operator()(size_t row, size_t col)
{
    if (!m_optVecBmpImage)
        throw std::runtime_error("Image data not initialized");
    auto width = GetMaximumWidth();
    if (row >= GetMaximumHeight() || col >= width)
        throw std::out_of_range("operator(): Index out of bounds");
    return m_optVecBmpImage->at(row * width + col);
}

const unsigned char CUserBitmap::operator()(size_t row, size_t col) const
{
    if (!m_optVecBmpImage)
        throw std::runtime_error("Image data not initialized");
    auto width = GetMaximumWidth();
    if (row >= GetMaximumHeight() || col >= width)
        throw std::out_of_range("operator() const: Index out of bounds");
    return m_optVecBmpImage->at(row * width + col);
}
#else
unsigned char& CUserBitmap::operator()(size_t row, size_t col) noexcept
{
    return (*m_optVecBmpImage)[row * GetMaximumWidth() + col];
}

const unsigned char CUserBitmap::operator()(size_t row, size_t col) const noexcept
{
    return (*m_optVecBmpImage)[row * GetMaximumWidth() + col];
}
#endif

std::vector<unsigned char>& CUserBitmap::GetImage() 
{
    if (!m_optVecBmpImage)
        throw std::runtime_error("Image data not initialized");
    return *m_optVecBmpImage;
}


const std::vector<unsigned char>& CUserBitmap::GetImage() const
{
    if (!m_optVecBmpImage)
        throw std::runtime_error("Image data not initialized");
    return *m_optVecBmpImage;
}

const unsigned char* CUserBitmap::Data() const noexcept
{
    if (!m_optVecBmpImage)
        return nullptr;
    return m_optVecBmpImage->data();
}

bool CUserBitmap::SetImage(const unsigned char* src, const BITMAPINFO* info)
{
    if (!src || !info)
        return false;

    if (!m_BmpInfo.Set(info))
        return false;

    size_t dataSize = GetRwSize() * GetMaximumHeight();
    PushBitmapImageVector(src, dataSize);

    m_DibHf.Initialize(); // 초기화 시점은 꼭 필요한 경우만 조정 가능

    return true;
}

bool CUserBitmap::SetImage(const unsigned char* src, const BITMAPINFOHEADER* hdr, const BITMAPFILEHEADER* fhdr)
{
    if (!src || !hdr || !fhdr)
        return false;

    if (!m_BmpInfo.Set(hdr))
        return false;
    if (!m_DibHf.Set(fhdr))
        return false;

    size_t dataSize = GetRwSize() * GetMaximumHeight();
    PushBitmapImageVector(src, dataSize);

    return true;
}

bool CUserBitmap::SetImage(const CUserBitmap& rhs)
{
    if (this == &rhs)
        return false;

    if (!rhs.GetBitmapInfo() || !rhs.GetBitmapFileHeader())
        return false;

    if (!m_BmpInfo.Set(rhs.GetBitmapInfo()))
        return false;
    if (!m_DibHf.Set(rhs.GetBitmapFileHeader()))
        return false;

    size_t dataSize = rhs.GetRwSize() * rhs.GetMaximumHeight();
    PushBitmapImageVector(rhs.Data(), dataSize);

    return true;
}

bool CUserBitmap::GetImage(unsigned char* dest, BITMAPINFO* info) const
{
    if (!m_optVecBmpImage || m_optVecBmpImage->empty() || !dest || !info)
        return false;

    const auto* srcInfo = GetBitmapInfo();
    if (!srcInfo)
        return false;

    size_t headerSize = sizeof(BITMAPINFOHEADER);
    int bitCount = srcInfo->bmiHeader.biBitCount;
    size_t colorTableSize = (bitCount <= 8) ? (1 << bitCount) * sizeof(RGBQUAD) : 0;

    std::memcpy(info, srcInfo, headerSize + colorTableSize);
    std::memcpy(dest, Data(), GetRwSize() * GetMaximumHeight());

    return true;
}

bool CUserBitmap::GetImage(unsigned char* dest, BITMAPINFOHEADER* hdr, BITMAPFILEHEADER* fhdr) const
{
    if (!m_optVecBmpImage || m_optVecBmpImage->empty() || !dest || !hdr || !fhdr)
        return false;

    const auto* srcHdr = GetBitmapInfoHeader();
    const auto* srcFhdr = GetBitmapFileHeader();

    if (!srcHdr || !srcFhdr)
        return false;

    std::memcpy(hdr, srcHdr, sizeof(BITMAPINFOHEADER));
    std::memcpy(fhdr, srcFhdr, sizeof(BITMAPFILEHEADER));
    std::memcpy(dest, Data(), GetRwSize() * GetMaximumHeight());

    return true;
}

bool CUserBitmap::SetBitmapInfo(const BITMAPINFO& info)
{
    return m_BmpInfo.Set(info);
}

bool CUserBitmap::SetBitmapInfo(const BITMAPINFO* info)
{
    return m_BmpInfo.Set(info);
}

bool CUserBitmap::SetBitmapInfoHeader(const BITMAPINFOHEADER& hdr)
{
    return m_BmpInfo.Set(hdr);
}

bool CUserBitmap::SetBitmapFileHeader(const BITMAPFILEHEADER& fhdr)
{
    return m_DibHf.Set(fhdr);
}

void CUserBitmap::PushBitmapImageVector(const unsigned char* src, size_t size)
{
    if (!src || size == 0)
        return;

    // std::optional 내부 벡터 초기화 및 예외 안전한 복사 수행
    try {
        m_optVecBmpImage.emplace(size);
        std::copy(src, src + size, m_optVecBmpImage->begin());
    }
    catch (...) {
        m_optVecBmpImage.reset();
        throw; // 호출자에게 예외 전달
    }
}
