#include "pch.h"
#include "BitmapProcess.h"

CBitmapProcess::CBitmapProcess()
{
    Initialize();
}

CBitmapProcess::~CBitmapProcess()
{
    Clear();
}

void CBitmapProcess::Clear()
{
    m_cbmpNodeIn.Clear();
    // m_cuserRGBQuad도 Clear 필요시 호출 가능
}

void CBitmapProcess::Initialize()
{
    Clear();
    m_cuserRGBQuad.Initialize();
}

bool CBitmapProcess::SaveImageToFile(LPCTSTR lpszPathName)
{
    if (!lpszPathName || lpszPathName[0] == _T('\0'))
        return false;

    CBitmapIO bitmapIO;
    return bitmapIO.Save(lpszPathName, m_cbmpNodeIn, m_cuserRGBQuad.Get());
}

bool CBitmapProcess::OpenImageFromFile(LPCTSTR lpszPathName)
{
    if (!lpszPathName || lpszPathName[0] == _T('\0'))
        return false;

    CBitmapIO bitmapIO;
    return bitmapIO.Open(lpszPathName, m_cbmpNodeIn, m_cuserRGBQuad.Get());
}

void CBitmapProcess::RGB2HSI()
{
    CRGBToHSI rgb2hsi;
    rgb2hsi.Process(m_cbmpNodeIn);
    // Clear() 불필요 (지역변수라 종료시 자동소멸)
}

void CBitmapProcess::RGB2Gray()
{
    CRGBToGray rgb2gray;
    rgb2gray.Process(m_cbmpNodeIn);
}

void CBitmapProcess::ColorEmbossing()
{
    CColorEmbossing colorEmbossing;
    colorEmbossing.Process(m_cbmpNodeIn);
}

void CBitmapProcess::RGBShapening()
{
    CRGBSharpening rgbSharpening;
    rgbSharpening.Process(m_cbmpNodeIn);
}

void CBitmapProcess::OnRgbSobel()
{
    CSobelImage sobelImage;
    sobelImage.Process(m_cbmpNodeIn);
}

void CBitmapProcess::ChannelsplitRgb()
{
    CChannelsplitRgb channelsplitRgb;
    channelsplitRgb.Process(m_cbmpNodeIn);
}

void CBitmapProcess::Blobcoloring(CClientDC* pDc)
{
    if (!pDc)
        return;

    CActBlobcoloring actBlobcoloring;
    actBlobcoloring.Process(m_cbmpNodeIn, pDc);
}

bool CBitmapProcess::OnImgDynbinSet(CDLG_DYNBIN* pDlg)
{
    if (!pDlg)
        return false;

    if (!m_cbmpNodeIn.GetBitmapInfo() || !m_cbmpNodeIn.GetImage().data())
        return false;

    pDlg->Set(m_cbmpNodeIn);
    return true;
}

bool CBitmapProcess::OnImgDynbinGet(CDLG_DYNBIN* pDlg)
{
    if (!pDlg)
        return false;

    if (!m_cbmpNodeIn.GetBitmapInfo() || !m_cbmpNodeIn.GetImage().data())
        return false;

    pDlg->Get(m_cbmpNodeIn);
    return true;
}

bool CBitmapProcess::NewDocument()
{
    CBitmapClipBoard bitmapClipBoard;
    return bitmapClipBoard.NewDocument(m_cbmpNodeIn, m_cuserRGBQuad);
}

size_t CBitmapProcess::GetImageWidth() const
{
    return m_cbmpNodeIn.GetMaximumWidth();
}

size_t CBitmapProcess::GetImageHeight() const
{
    return m_cbmpNodeIn.GetMaximumHeight();
}

int CBitmapProcess::GetImageBitCount() const
{
    return m_cbmpNodeIn.GetBitCount();
}

int CBitmapProcess::GetImageRwSize() const
{
    return m_cbmpNodeIn.GetRwSize();
}

bool CBitmapProcess::DrawImage(CDC* pDC)
{
    if (!pDC || !m_cbmpNodeIn.GetImage().data())
        return false;

    BOOL ret = SetDIBitsToDevice(
        pDC->GetSafeHdc(),
        0, 0,
        m_cbmpNodeIn.GetMaximumWidth(), m_cbmpNodeIn.GetMaximumHeight(),
        0, 0, 0, m_cbmpNodeIn.GetMaximumHeight(),
        m_cbmpNodeIn.GetImage().data(),
        m_cbmpNodeIn.GetBitmapInfo(),
        DIB_RGB_COLORS);

    return (ret != 0);
}

void CBitmapProcess::GetImageSize(CSize& csSizeImage) const
{
    csSizeImage.cx = static_cast<int>(GetImageWidth());
    csSizeImage.cy = static_cast<int>(GetImageHeight());
}

void CBitmapProcess::CopyClipboard()
{
    CBitmapClipBoard bitmapClipBoard;
    bitmapClipBoard.CopyClipboard(m_cbmpNodeIn, m_cuserRGBQuad);
}
