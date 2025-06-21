#include "pch.h"
#include "BitmapAction.h"

CBitmapAction::CBitmapAction() noexcept
{
    Initialize();
}

CBitmapAction::~CBitmapAction() noexcept
{
    Clear();
}

CBitmapAction::CBitmapAction(const CBitmapAction& rhs)
{
    Initialize();
    Set(rhs);
}

CBitmapAction::CBitmapAction(CBitmapAction&& rhs) noexcept
    : m_pCuserRGBQuad(std::move(rhs.m_pCuserRGBQuad)),
    m_pCbmpElements(std::move(rhs.m_pCbmpElements))
{
}

CBitmapAction& CBitmapAction::operator=(const CBitmapAction& rhs)
{
    if (this != &rhs)
    {
        Clear();
        Initialize();
        Set(rhs);
    }
    return *this;
}

CBitmapAction& CBitmapAction::operator=(CBitmapAction&& rhs) noexcept
{
    if (this != &rhs)
    {
        m_pCuserRGBQuad = std::move(rhs.m_pCuserRGBQuad);
        m_pCbmpElements = std::move(rhs.m_pCbmpElements);
    }
    return *this;
}

void CBitmapAction::Clear() noexcept
{
    m_pCuserRGBQuad.reset();
    m_pCbmpElements.reset();
}

bool CBitmapAction::Initialize() noexcept
{
    m_pCuserRGBQuad = std::make_unique<CUserRGBQuad>();
    m_pCbmpElements = std::make_unique<CUserBitmap>();

    if (!m_pCuserRGBQuad || !m_pCbmpElements)
        return false;

    m_pCuserRGBQuad->Initialize();
    return true;
}

bool CBitmapAction::Set(const CBitmapAction& rhs)
{
    if (this == &rhs || !rhs.m_pCbmpElements || !rhs.m_pCuserRGBQuad)
        return false;

    return Set(*rhs.m_pCbmpElements, *rhs.m_pCuserRGBQuad);
}

bool CBitmapAction::Set(const CUserBitmap& userBitmap)
{
    if (!m_pCbmpElements || !userBitmap.GetImage().data())
        return false;

    Clear();
    if (!Initialize()) return false;

    return m_pCbmpElements->SetImage(userBitmap);
}

bool CBitmapAction::Set(const CUserBitmap& userBitmap, const CUserRGBQuad& rgbQuad)
{
    Clear();
    if (!Initialize()) return false;

    if (!m_pCbmpElements->SetImage(userBitmap)) return false;
    if (!m_pCuserRGBQuad->Set(rgbQuad)) return false;

    return true;
}

bool CBitmapAction::Get(CUserBitmap& userBitmap) const
{
    if (!m_pCbmpElements) return false;
    return userBitmap.SetImage(*m_pCbmpElements);
}

bool CBitmapAction::Get(CBitmapAction& rhs) const
{
    if (this == &rhs || !m_pCbmpElements || !m_pCuserRGBQuad)
        return false;

    rhs.Clear();
    rhs.Initialize();

    if (!rhs.m_pCbmpElements->SetImage(*m_pCbmpElements)) return false;
    if (!rhs.m_pCuserRGBQuad->Set(*m_pCuserRGBQuad)) return false;

    return true;
}

bool CBitmapAction::DrawImage(CDC* pDC) const noexcept
{
    if (!pDC || !m_pCbmpElements || !m_pCbmpElements->GetImage().data())
        return false;

    SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0,
        GetImageWidth(), GetImageHeight(),
        0, 0, 0, GetImageHeight(),
        m_pCbmpElements->GetImage().data(),
        m_pCbmpElements->GetBitmapInfo(),
        DIB_RGB_COLORS);

    return true;
}

bool CBitmapAction::CopyClipboard() const noexcept
{
    if (!m_pCbmpElements || !m_pCbmpElements->GetImage().data())
        return false;

    CopyClipboard(m_pCbmpElements->GetImage().data(),
        static_cast<int>(GetImageHeight()),
        static_cast<int>(GetImageWidth()),
        static_cast<int>(GetImageBitCount()));

    return true;
}

// 비-const 버전
void CBitmapAction::CopyClipboard(const unsigned char* img, int height, int width, int biBitCount) noexcept
{
    if (!img || height <= 0 || width <= 0 || (biBitCount != 8 && biBitCount != 24))
        return;

    size_t rwsize = WIDTHBYTES(biBitCount * width);
    DWORD dibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE + rwsize * height;

    HGLOBAL hImage = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dibSize);
    if (!hImage) return;

    LPSTR pDIB = (LPSTR)GlobalLock(hImage);
    if (!pDIB)
    {
        GlobalFree(hImage);
        return;
    }

    BITMAPINFOHEADER bih;
    m_pCbmpElements->GetBitmapInfoHeader(bih);

    bih.biBitCount = static_cast<WORD>(biBitCount);
    bih.biHeight = height;
    bih.biWidth = width;
    bih.biSizeImage = height * rwsize;
    if (biBitCount == 8) bih.biClrUsed = bih.biClrImportant = MAXIMUM_PIXEL_VALUE;

    memcpy(pDIB, &bih, sizeof(BITMAPINFOHEADER));

    if (biBitCount == 8)
    {
        memcpy(pDIB + sizeof(BITMAPINFOHEADER), m_pCuserRGBQuad->Get(), sizeof(RGBQUAD) * MAXIMUM_PIXEL_VALUE);
        memcpy(pDIB + dibSize - bih.biSizeImage, img, bih.biSizeImage);
    }
    else
    {
        memcpy(pDIB + sizeof(BITMAPINFOHEADER), img, bih.biSizeImage);
    }

    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_DIB, hImage);
    CloseClipboard();

    GlobalUnlock(hImage);
    // GlobalFree(hImage);  // 시스템이 소유하므로 여기서 해제하지 않음
}

// const 버전
void CBitmapAction::CopyClipboard(const unsigned char* img, int height, int width, int biBitCount) const noexcept
{
    // const 함수에서 비-const 호출 시 const_cast 사용
    const_cast<CBitmapAction*>(this)->CopyClipboard(img, height, width, biBitCount);
}

size_t CBitmapAction::GetImageWidth() const noexcept
{
    return (m_pCbmpElements && m_pCbmpElements->GetBitmapInfoHeader()) ? m_pCbmpElements->GetMaximumWidth() : 0;
}

size_t CBitmapAction::GetImageHeight() const noexcept
{
    return (m_pCbmpElements && m_pCbmpElements->GetBitmapInfoHeader()) ? m_pCbmpElements->GetMaximumHeight() : 0;
}

int CBitmapAction::GetImageBitCount() const noexcept
{
    return (m_pCbmpElements && m_pCbmpElements->GetBitmapInfoHeader()) ? m_pCbmpElements->GetBitCount() : 0;
}

unsigned long CBitmapAction::GetImageRwSize() const noexcept
{
    return (m_pCbmpElements && m_pCbmpElements->GetBitmapInfoHeader()) ? m_pCbmpElements->GetRwSize() : 0;
}

unsigned long CBitmapAction::GetTotalSize() const noexcept
{
    return (m_pCbmpElements && m_pCbmpElements->GetBitmapInfoHeader()) ? m_pCbmpElements->GetTotalSize() : 0;
}

void CBitmapAction::GetImageSize(CSize& csSizeImage) const noexcept
{
    csSizeImage.cx = static_cast<int>(GetImageWidth());
    csSizeImage.cy = static_cast<int>(GetImageHeight());
}

bool CBitmapAction::ImgConvolution(std::vector<unsigned char>& InImg, std::vector<unsigned char>& OutImg,
    const size_t& height, const size_t& width,
    std::vector<float>& Mask, int winsize) const noexcept
{
    if (InImg.empty() || OutImg.empty() || Mask.empty())
        return false;
    if (height <= 0 || width <= 0 || winsize <= 0)
        return false;

    std::fill(OutImg.begin(), OutImg.end(), 0);

    int n = (winsize - 1) >> 1;

    for (size_t i = n; i < height - n; i++)
    {
        size_t index1 = i * width;
        for (size_t j = n; j < width - n; j++)
        {
            double sum = 0.0;
            for (int k = -n; k <= n; k++)
            {
                size_t index2 = (i + k) * width;
                size_t index3 = (k + n) * winsize;
                for (int l = -n; l <= n; l++)
                {
                    sum += static_cast<double>(InImg[index2 + (j + l)]) * static_cast<double>(Mask[index3 + l + n]);
                }
            }
            CLIP<double>(sum, 0.0, 255.0);
            OutImg[index1 + j] = static_cast<unsigned char>(sum);
        }
    }
    return true;
}

bool CBitmapAction::RGBtoHSI(const std::vector<unsigned char>& InImg, std::vector<short>& H,
    std::vector<unsigned char>& S, std::vector<unsigned char>& IV,
    const size_t& height, const size_t& width) const noexcept
{
    if (InImg.empty() || H.empty() || S.empty() || IV.empty())
        return false;
    if (height <= 0 || width <= 0)
        return false;

    size_t rwsize = WIDTHBYTES(24 * width);

    CColorConv pColorConv;

    for (size_t i = 0; i < height; i++)
    {
        size_t index1 = (height - i - 1) * rwsize;
        size_t index2 = (height - i - 1) * width;

        for (size_t j = 0; j < width; j++)
        {
            double r = static_cast<double>(InImg[index1 + 3 * j + 2]) / 255.0;
            double g = static_cast<double>(InImg[index1 + 3 * j + 1]) / 255.0;
            double b = static_cast<double>(InImg[index1 + 3 * j]) / 255.0;

            double hue = 0.0, satu = 0.0, intens = 0.0;
            pColorConv.RGB_To_HSI(r, g, b, &hue, &satu, &intens);

            H[index2 + j] = static_cast<short>(hue);
            S[index2 + j] = static_cast<unsigned char>(satu * 255.0);
            IV[index2 + j] = static_cast<unsigned char>(intens * 255.0);
        }
    }

    return true;
}

bool CBitmapAction::HSItoRGB(std::vector<unsigned char>& OutImg, const std::vector<short>& H,
    const std::vector<unsigned char>& S, const std::vector<unsigned char>& IV,
    const size_t& height, const size_t& width) const noexcept
{
    if (OutImg.empty() || H.empty() || S.empty() || IV.empty())
        return false;
    if (height <= 0 || width <= 0)
        return false;

    size_t rwsize = WIDTHBYTES(24 * width);

    CColorConv pColorConv;

    for (size_t i = 0; i < height; i++)
    {
        size_t index1 = (height - i - 1) * rwsize;
        size_t index2 = (height - i - 1) * width;

        for (size_t j = 0; j < width; j++)
        {
            double hue = static_cast<double>(H[index2 + j]);
            double satu = static_cast<double>(S[index2 + j]) / 255.0;
            double intens = static_cast<double>(IV[index2 + j]) / 255.0;

            double r = 0.0, g = 0.0, b = 0.0;
            pColorConv.HSI_To_RGB(hue, satu, intens, &r, &g, &b);

            double rr = r * 255.0;
            double gg = g * 255.0;
            double bb = b * 255.0;

            CLIP<double>(rr, 0, 255);
            CLIP<double>(gg, 0, 255);
            CLIP<double>(bb, 0, 255);

            OutImg[index1 + 3 * j] = static_cast<unsigned char>(bb);
            OutImg[index1 + 3 * j + 1] = static_cast<unsigned char>(gg);
            OutImg[index1 + 3 * j + 2] = static_cast<unsigned char>(rr);
        }
    }

    return true;
}

bool CBitmapAction::InitializeMask(std::vector<float>& mask, const size_t& winsize) const noexcept
{
    mask.resize(winsize * winsize);
    std::fill(mask.begin(), mask.end(), 0.0f);
    return true;
}

bool CBitmapAction::FillMaskPattern(std::vector<float>& mask, const std::vector<float>& pattern, const size_t& winsize) const noexcept
{
    InitializeMask(mask, winsize);

    if (pattern.empty() || pattern.size() != winsize * winsize)
        return false;

    std::copy(pattern.begin(), pattern.end(), mask.begin());
    return true;
}

bool CBitmapAction::InitializeBufferImage(std::vector<unsigned char>& ucImage, const size_t& imageSize) const noexcept
{
    ucImage.resize(imageSize);
    std::fill(ucImage.begin(), ucImage.end(), 0);
    return true;
}

bool CBitmapAction::InitializeBufferImage(std::vector<short>& sImage, const size_t& imageSize) const noexcept
{
    sImage.resize(imageSize);
    std::fill(sImage.begin(), sImage.end(), 0);
    return true;
}
