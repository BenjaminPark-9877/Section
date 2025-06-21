#include "pch.h"
#include "DynBinProcess.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "BitmapImageProcessDoc.h"
#include "BitmapImageProcessView.h"

CDynBinProcess::CDynBinProcess() : m_nThresValueDisp(0)
{
}

CDynBinProcess::~CDynBinProcess()
{
	Clear();
}

void CDynBinProcess::Clear()
{
	m_bmpDynBinIn.Clear();
	m_bmpDynBinOut.Clear();
}

bool CDynBinProcess::OnInitDialog(int nThresValueDisp)
{
	SetThreshValueDisp(nThresValueDisp);
	return true;
}

void CDynBinProcess::Initialize(int nThresValueDisp /*=0*/)
{
	SetThreshValueDisp(nThresValueDisp);
	Clear();
}

bool CDynBinProcess::SetImage(const CUserBitmap& bitmapNode)
{
	if (bitmapNode.GetBitCount() != BITCOUNT_24)
		return false;

	Clear();

	if (!m_bmpDynBinIn.SetImage(bitmapNode))
		return false;

	if (!m_bmpDynBinOut.SetImage(bitmapNode))
		return false;

	return true;
}

// LUT 생성 함수 분리
bool CDynBinProcess::CreateLUT(std::array<unsigned char, LUT_SIZE>& LUT)
{
	if (LUT.size() != LUT_SIZE) return false; // 혹은 다른 검증 로직

	for (int i = 0; i < LUT_SIZE; i++)
	{
		LUT[i] = (i > m_nThresValueDisp) ? 255 : 0;
	}
	return true;
}

// 24비트 처리 함수 분리
bool CDynBinProcess::ApplyThreshold24bit(const std::array<unsigned char, LUT_SIZE>& LUT)
{
	const int height = m_bmpDynBinIn.GetMaximumHeight();
	const int width = m_bmpDynBinIn.GetMaximumWidth();
	const int rwsize = m_bmpDynBinIn.GetRwSize();

	for (int i = 0; i < height; i++)
	{
		int rowIndex = (height - i - 1) * rwsize;
		for (int j = 0; j < width; j++)
		{
			int pixelIndex = rowIndex + RGB_CHANNELS * j;
			m_bmpDynBinOut[pixelIndex] = LUT[m_bmpDynBinIn[pixelIndex]];
			m_bmpDynBinOut[pixelIndex + 1] = LUT[m_bmpDynBinIn[pixelIndex + 1]];
			m_bmpDynBinOut[pixelIndex + 2] = LUT[m_bmpDynBinIn[pixelIndex + 2]];
		}
	}
	return true;
}

// 8비트 처리 함수 분리
bool CDynBinProcess::ApplyThreshold8bit(const std::array<unsigned char, LUT_SIZE>& LUT)
{
	const int height = m_bmpDynBinIn.GetMaximumHeight();
	const int width = m_bmpDynBinIn.GetMaximumWidth();
	const int rwsize = m_bmpDynBinIn.GetRwSize();

	for (int i = 0; i < height; i++)
	{
		int rowIndex = (height - i - 1) * rwsize;
		for (int j = 0; j < width; j++)
		{
			int pixelIndex = rowIndex + j;
			m_bmpDynBinOut[pixelIndex] = LUT[m_bmpDynBinIn[pixelIndex]];
		}
	}
	return true;
}

bool CDynBinProcess::OnNMCustomdrawSldThreshhold(int nThresValueDisp)
{
	SetThreshValueDisp(nThresValueDisp);

	const int height = m_bmpDynBinIn.GetMaximumHeight();
	const int width = m_bmpDynBinIn.GetMaximumWidth();
	const int bitcount = m_bmpDynBinIn.GetBitCount();

	if (height <= 0 || width <= 0)
		return false;

	std::array<unsigned char, LUT_SIZE> LUT{};

	if (!CreateLUT(LUT))
		return false;

	if (bitcount == BITCOUNT_24)
	{
		ApplyThreshold24bit(LUT);
	}
	else if (bitcount == BITCOUNT_8)
	{
		ApplyThreshold8bit(LUT);
	}
	else
	{
		return false;
	}

	return true;
}

bool CDynBinProcess::OnPaint(const CPaintDC& dcView, const CRect& rect)
{
	if (!m_bmpDynBinOut.GetImage().data())
		return false;

	StretchDIBits(dcView.m_hDC, rect.left, rect.top, rect.Width(), rect.Height(), 0, 0,
		m_bmpDynBinOut.GetMaximumWidth(), m_bmpDynBinOut.GetMaximumHeight(),
		m_bmpDynBinOut.GetImage().data(), m_bmpDynBinOut.GetBitmapInfo(), BI_RGB, SRCCOPY);

	return true;
}

bool CDynBinProcess::GetImage(CUserBitmap& bitmapNode) const
{
	if (!m_bmpDynBinOut.GetImage().data())
		return false;

	return bitmapNode.SetImage(m_bmpDynBinOut);
}