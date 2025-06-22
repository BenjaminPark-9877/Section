/////** 
////*description   : 비트맵 영상을 처리하는 객체 정의 소스 파일
////*/
#include "pch.h"
#include "RGBToHSI.h"
#include "BlobColoring.h"
#include "ColorConv.h"

//*description   : RGB -> HSI 영상으로 변환 후 분할
void CRGBToHSI::Process(const CUserBitmap* pCbmpElementsIn)
{
	if (!pCbmpElementsIn ||
		pCbmpElementsIn->GetImage().data() == nullptr ||
		pCbmpElementsIn->GetBitmapInfo() == nullptr ||
		pCbmpElementsIn->GetBitCount() != 24)
		return;

	if (!Set(*pCbmpElementsIn))
		return;

	if (!RGB2HSI(pCbmpElementsIn->GetImage().data(), m_pCbmpElements->GetImage().data(),
		(int)m_pCbmpElements->GetMaximumHeight(),
		(int)m_pCbmpElements->GetMaximumWidth()))
		return;

	SpiltOneColorImage(*m_pCbmpElements);
}

//*description   : RGB 데이터를 HSI로 변환
bool CRGBToHSI::RGB2HSI(const unsigned char* InImg, unsigned char* OutImg, int height, int width)
{
	if (!InImg || !OutImg || height <= 0 || width <= 0)
		return false;

	size_t rwsize = WIDTHBYTES(24 * width);
	CColorConv pColorConv;

	for (int i = 0; i < height; i++)
	{
		int index = (height - i - 1) * (int)rwsize;
		for (int j = 0; j < width; j++)
		{
			double r = InImg[index + 3 * j + 2] / 255.0;
			double g = InImg[index + 3 * j + 1] / 255.0;
			double b = InImg[index + 3 * j] / 255.0;

			double h, s, iv;
			pColorConv.RGB_To_HSI(r, g, b, &h, &s, &iv);

			int ih = static_cast<int>(h * 255.0 / 360.0);
			OutImg[index + 3 * j] = static_cast<unsigned char>(ih);           // H
			OutImg[index + 3 * j + 1] = static_cast<unsigned char>(s * 255.0);    // S
			OutImg[index + 3 * j + 2] = static_cast<unsigned char>(iv * 255.0);   // I
		}
	}
	return true;
}

//*description   : 하나의 색상 채널씩 복사하여 클립보드에 출력
bool CRGBToHSI::SpiltOneColorImage(const CUserBitmap& bitmapNode, int nType /*= THREE_COLOR_TYPE*/)
{
	if (!bitmapNode.GetImage().data() || nType <= 0 || nType > FOUR_COLOR_TYPE)
		return false;

	int width = (int)bitmapNode.GetMaximumWidth();
	int height = (int)bitmapNode.GetMaximumHeight();
	int rwsize = (int)bitmapNode.GetRwSize();
	size_t grRWSIZE = WIDTHBYTES(8 * width);

	std::vector<unsigned char> GrayImg(height * grRWSIZE, 0);

	for (int k = 0; k < nType; ++k)
	{
		for (int i = 0; i < height; ++i)
		{
			int index = (height - i - 1) * rwsize;
			for (int j = 0; j < width; ++j)
			{
				GrayImg[(height - i - 1) * grRWSIZE + j] = bitmapNode[index + 3 * j + k];
			}
		}
		CopyClipboard(GrayImg.data(), height, width, 8);
		AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
	}

	return true;
}