#ifndef _BITMAPACTION_H_
#define _BITMAPACTION_H_
#pragma once

#include <memory>
#include <vector>
#include <afxwin.h>
#include "basicbone.h"
#include "UserMachro.h"
#include "UserRGBQuad.h"
#include "UserBitmap.h"
#include "ColorConv.h"

class CBitmapAction : private CBasicBone
{
public:
    CBitmapAction() noexcept;
    virtual ~CBitmapAction() noexcept;

    CBitmapAction(const CBitmapAction& rhs);
    CBitmapAction(CBitmapAction&& rhs) noexcept;

    CBitmapAction& operator=(const CBitmapAction& rhs);
    CBitmapAction& operator=(CBitmapAction&& rhs) noexcept;

    void Clear() noexcept;
    bool DrawImage(CDC* pDC) const noexcept;

    void GetImageSize(CSize& csSizeImage) const noexcept;
    bool CopyClipboard() const noexcept;

    // CopyClipboard 내부 호출용 (const, non-const 둘 다)
    void CopyClipboard(const unsigned char* img, int height, int width, int biBitCount) noexcept;
    void CopyClipboard(const unsigned char* img, int height, int width, int biBitCount) const noexcept;

    size_t GetImageWidth() const noexcept;
    size_t GetImageHeight() const noexcept;
    int GetImageBitCount() const noexcept;
    unsigned long GetImageRwSize() const noexcept;
    unsigned long GetTotalSize() const noexcept;

    bool ImgConvolution(std::vector<unsigned char>& InImg, std::vector<unsigned char>& OutImg,
        const size_t& height, const size_t& width,
        std::vector<float>& Mask, int winsize) const noexcept;

    bool RGBtoHSI(const std::vector<unsigned char>& InImg, std::vector<short>& H,
        std::vector<unsigned char>& S, std::vector<unsigned char>& IV,
        const size_t& height, const size_t& width) const noexcept;

    bool HSItoRGB(std::vector<unsigned char>& OutImg, const std::vector<short>& H,
        const std::vector<unsigned char>& S, const std::vector<unsigned char>& IV,
        const size_t& height, const size_t& width) const noexcept;

    bool InitializeMask(std::vector<float>& mask, const size_t& winsize) const noexcept;
    bool FillMaskPattern(std::vector<float>& mask, const std::vector<float>& pattern, const size_t& winsize) const noexcept;

    bool InitializeBufferImage(std::vector<unsigned char>& ucImage, const size_t& imageSize) const noexcept;
    bool InitializeBufferImage(std::vector<short>& sImage, const size_t& imageSize) const noexcept;

    bool Set(const CUserBitmap& userBitmap);
    bool Set(const CUserBitmap& userBitmap, const CUserRGBQuad& rgbQuad);
    bool Set(const CBitmapAction& rhs);

    bool Get(CUserBitmap& userBitmap) const;
    bool Get(CBitmapAction& rhs) const;

    const CUserBitmap* GetUserBitmap() const noexcept { return m_pCbmpElements.get(); }
    const CUserRGBQuad* GetRGBQuad() const noexcept { return m_pCuserRGBQuad.get(); }

    // 비-const 접근자
    CUserBitmap* GetBitmapActionPtr() noexcept { return m_pCbmpElements.get(); }

protected:
    bool Initialize() noexcept;

    std::unique_ptr<CUserRGBQuad> m_pCuserRGBQuad;
    std::unique_ptr<CUserBitmap> m_pCbmpElements;

private:

};

#endif //_BITMAPACTION_H_
