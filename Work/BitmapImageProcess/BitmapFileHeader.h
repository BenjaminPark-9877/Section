#ifndef _BITMAPFILEHEADER_H_
#define _BITMAPFILEHEADER_H_

#pragma once

#ifndef _BASICBONE_H_
#include "BasicBone.h"
#endif //_BASICBONE_H_

#include <memory>
#include <windows.h>

class CBitmapFileHeader : private CBasicBone
{
public:
    CBitmapFileHeader();
    ~CBitmapFileHeader();

    CBitmapFileHeader(const CBitmapFileHeader& rhs);
    CBitmapFileHeader(CBitmapFileHeader&& rhs) noexcept;

    CBitmapFileHeader(const BITMAPFILEHEADER& rhs);

    CBitmapFileHeader& operator=(const CBitmapFileHeader& rhs);
    CBitmapFileHeader& operator=(CBitmapFileHeader&& rhs) noexcept;

    CBitmapFileHeader& operator=(const BITMAPFILEHEADER& rhs);

    bool Initialize();
    bool Set(const BITMAPFILEHEADER& rhs);
    bool Set(const CBitmapFileHeader& rhs);
    bool Set(const BITMAPFILEHEADER* pDibHf);
    bool Set(const CBitmapFileHeader* pBmpFileHead);

    bool GetBitmapFileHeader(BITMAPFILEHEADER& outHeader) const;
    const BITMAPFILEHEADER* GetBitmapFileHeader() const;

    const CBitmapFileHeader* Get() const;

    bool isEqual(const CBitmapFileHeader& rhs) const;
    bool isEqual(const BITMAPFILEHEADER& rhs) const;

    bool operator==(const CBitmapFileHeader& rhs) const { return isEqual(rhs); }
    bool operator==(const BITMAPFILEHEADER& rhs) const { return isEqual(rhs); }

    bool operator!=(const CBitmapFileHeader& rhs) const { return !isEqual(rhs); }
    bool operator!=(const BITMAPFILEHEADER& rhs) const { return !isEqual(rhs); }

    void Clear();

private:
    std::unique_ptr<BITMAPFILEHEADER> m_pDibHf;
};

#endif //_BITMAPFILEHEADER_H_
