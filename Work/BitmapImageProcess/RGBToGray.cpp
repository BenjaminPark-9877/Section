/////** 
////*description   :  작업 수행 클래스 소스 파일
////*               
////* 
////*/
#include "pch.h"
#include "RGBToGray.h"
#include "BlobColoring.h"
#include "ColorConv.h"

//*description   : 
//*@param input  : CUserBitmap* pCbmpElementsIn
//*@param input  :   
//*@param input  :  
//*@param input  :  
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
void CRGBToGray::Process(const CUserBitmap* pCbmpElementsIn)
{
	if (pCbmpElementsIn->GetImage().data() == NULL) return;
	if (pCbmpElementsIn->GetBitmapInfo() == NULL) return;
	if (pCbmpElementsIn->GetBitCount() != 24) return;

	// 빈이미지로 초기화 하여야 하나 동작 확인 및 별도로 set 하는 일 막기 위해 이렇게 처리함
	if (!Set(*pCbmpElementsIn)) return;

	if (RGB2Gray(pCbmpElementsIn->GetImage().data(), m_pCbmpElements->GetImage().data(),
		(int)m_pCbmpElements->GetMaximumHeight(),
		(int)m_pCbmpElements->GetMaximumWidth()) == false) return;

	SpiltOneColorImage(*m_pCbmpElements, MONO_COLOR_TYPE);
}

bool CRGBToGray::RGB2Gray(const unsigned char* InImg, unsigned char* OutImg, int height, int width)
{
	if (!InImg || !OutImg || height <= 0 || width <= 0) return false;

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

			double gray;
			pColorConv.RGB_To_Gray(r, g, b, &gray);
			unsigned char gVal = (unsigned char)(gray * 255.0);
			OutImg[index + 3 * j] = OutImg[index + 3 * j + 1] = OutImg[index + 3 * j + 2] = gVal;
		}
	}
	return true;
}

bool CRGBToGray::SpiltOneColorImage(const CUserBitmap& bitmapNode, int nType)
{
	if (bitmapNode.GetImage().data() == NULL || nType <= 0 || nType > FOUR_COLOR_TYPE)
		return false;

	int width = (int)bitmapNode.GetMaximumWidth();
	int height = (int)bitmapNode.GetMaximumHeight();
	int rwsize = (int)bitmapNode.GetRwSize();
	size_t grRWSIZE = WIDTHBYTES(8 * width);

	std::vector<unsigned char> GrayImg(height * grRWSIZE, 0);

	for (int k = 0; k < nType; k++)
	{
		for (int i = 0; i < height; i++)
		{
			int index = (height - i - 1) * rwsize;
			for (int j = 0; j < width; j++)
			{
				GrayImg[(height - i - 1) * grRWSIZE + j] = bitmapNode[index + 3 * j + k];
			}
		}
		CopyClipboard(GrayImg.data(), height, width, 8);
		AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
	}
	return true;
}