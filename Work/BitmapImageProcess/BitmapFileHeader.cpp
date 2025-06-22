#include "pch.h"
#include "BitmapFileHeader.h"
#include <cstring>

CBitmapFileHeader::CBitmapFileHeader() = default;

CBitmapFileHeader::~CBitmapFileHeader() = default;

CBitmapFileHeader::CBitmapFileHeader(const CBitmapFileHeader & rhs) {
    if (rhs.m_pDibHf) {
        m_pDibHf = std::make_unique<BITMAPFILEHEADER>(*rhs.m_pDibHf);
    }
    else {
        Initialize();  // nullptr일 때도 초기화 유지 권장
    }
}

CBitmapFileHeader::CBitmapFileHeader(const BITMAPFILEHEADER & rhs) {
    m_pDibHf = std::make_unique<BITMAPFILEHEADER>(rhs);
}

CBitmapFileHeader::CBitmapFileHeader(CBitmapFileHeader && rhs) noexcept
    : m_pDibHf(std::move(rhs.m_pDibHf)) {}

CBitmapFileHeader& CBitmapFileHeader::operator=(const CBitmapFileHeader & rhs) {
    if (this != &rhs) {
        m_pDibHf = rhs.m_pDibHf
            ? std::make_unique<BITMAPFILEHEADER>(*rhs.m_pDibHf)
            : nullptr;
    }
    return *this;
}

CBitmapFileHeader& CBitmapFileHeader::operator=(CBitmapFileHeader && rhs) noexcept {
    if (this != &rhs) {
        m_pDibHf = std::move(rhs.m_pDibHf);
        // 명시적 nullptr 대입 (실제론 불필요하지만 가독성 위해)
        rhs.m_pDibHf = nullptr;
    }
    return *this;
}

CBitmapFileHeader& CBitmapFileHeader::operator=(const BITMAPFILEHEADER & rhs) {
    m_pDibHf = std::make_unique<BITMAPFILEHEADER>(rhs);
    return *this;
}

bool CBitmapFileHeader::Initialize() {
    m_pDibHf = std::make_unique<BITMAPFILEHEADER>();
    if (!m_pDibHf) return false;

    std::memset(m_pDibHf.get(), 0, sizeof(BITMAPFILEHEADER));
    return true;
}

bool CBitmapFileHeader::Set(const BITMAPFILEHEADER & rhs) {
    m_pDibHf = std::make_unique<BITMAPFILEHEADER>(rhs);
    return true;
}

bool CBitmapFileHeader::Set(const CBitmapFileHeader & rhs) {
    if (this == &rhs || !rhs.m_pDibHf) return false;
    m_pDibHf = std::make_unique<BITMAPFILEHEADER>(*rhs.m_pDibHf);
    return true;
}

bool CBitmapFileHeader::Set(const BITMAPFILEHEADER * pDibHf) {
    if (!pDibHf) return false;
    m_pDibHf = std::make_unique<BITMAPFILEHEADER>(*pDibHf);
    return true;
}

bool CBitmapFileHeader::Set(const CBitmapFileHeader * pBmpFileHead) {
    if (!pBmpFileHead || this == pBmpFileHead || !pBmpFileHead->m_pDibHf) return false;
    m_pDibHf = std::make_unique<BITMAPFILEHEADER>(*pBmpFileHead->m_pDibHf);
    return true;
}

bool CBitmapFileHeader::GetBitmapFileHeader(BITMAPFILEHEADER & outHeader) const {
    if (!m_pDibHf) return false;
    outHeader = *m_pDibHf;
    return true;
}

const BITMAPFILEHEADER* CBitmapFileHeader::GetBitmapFileHeader() const {
    return m_pDibHf ? m_pDibHf.get() : nullptr;
}

const CBitmapFileHeader* CBitmapFileHeader::Get() const {
    return m_pDibHf ? this : nullptr;
}

bool CBitmapFileHeader::isEqual(const CBitmapFileHeader & rhs) const {
    return rhs.m_pDibHf && m_pDibHf && std::memcmp(m_pDibHf.get(), rhs.m_pDibHf.get(), sizeof(BITMAPFILEHEADER)) == 0;
}

bool CBitmapFileHeader::isEqual(const BITMAPFILEHEADER & rhs) const {
    return m_pDibHf && std::memcmp(m_pDibHf.get(), &rhs, sizeof(BITMAPFILEHEADER)) == 0;
}

void CBitmapFileHeader::Clear() {
    m_pDibHf.reset();
}
