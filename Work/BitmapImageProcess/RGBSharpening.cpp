/////** 
////*description   : 색상 영상을 선명하게 만드는 작업 수행 클래스 정의 소스 파일
////*               
////* 
////*/
#include "pch.h"
#include "RGBSharpening.h"
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
void CRGBSharpening::Process(CUserBitmap* pCbmpElementsIn)
{
	if (pCbmpElementsIn->GetImage().data() == NULL)
	{
		return;
	}

	if (pCbmpElementsIn->GetBitmapInfo() == NULL)
	{
		return;
	}

	if (pCbmpElementsIn->GetBitCount() != 24)
	{
		return;
	}

	// 빈이미지로 초기화 하여야 하나 동작 확인 및 별도로 set 하는 일 막기 위해 이렇게 처리함
	if (Set(*pCbmpElementsIn) == false)
	{
		return;
	}

	bool bResult = RGBSharpening(pCbmpElementsIn->GetImage(), m_pCbmpElements->GetImage(),
		(int)m_pCbmpElements->GetMaximumHeight(), (int)m_pCbmpElements->GetMaximumWidth());

	if (bResult == false)
	{
		// 실패시 처리 코드 추가 가능 (예: 로그, 메시지 등)
		return;
	}

	CopyClipboard(m_pCbmpElements->GetImage().data(), (int)m_pCbmpElements->GetMaximumHeight(),
		(int)m_pCbmpElements->GetMaximumWidth(), 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//*description   : 
//*@param input  :  
//*@param input  :  
//*@param input  :  
//*@param input  :  
//*@param input  :  
//*@param input  :  
//*@param output :  
//*@return		 :  
//*/
bool CRGBSharpening::InitializeMask(std::vector<float>& mask, const size_t& winsize)
{
	CBitmapAction::InitializeMask(mask, winsize);

	mask[1] = mask[3] = mask[5] = mask[7] = -1.0f;
	mask[4] = 5.0f;

	return true;
}

//*description   : 
//*@param input  :  
//*@param input  :  
//*@param input  : int				height
//*@param input  : int				width
//*@param input  : 
//*@param output : -
//*@return		 :  
//*/
bool CRGBSharpening::RGBSharpening(std::vector<unsigned char>& InImg, std::vector<unsigned char>& OutImg, const int& height, const int& width)
{
	if (InImg.empty() == true) { return false; }

	if (OutImg.empty() == true) { return false; }

	if (height <= 0) { return false; }

	if (width <= 0) { return false; }

	// convolution MASK의 정의 
	const int winsize = 3;
	std::vector<float> Mask;
	InitializeMask(Mask, winsize);

	// HSI영상을 위한 메모리 정의
	std::vector<short> H;
	InitializeBufferImage(H, (height * width));

	std::vector<unsigned char> S;
	InitializeBufferImage(S, (height * width));

	std::vector<unsigned char> IV;
	InitializeBufferImage(IV, (height * width));

	if ((H.empty() != true) && (S.empty() != true) && (IV.empty() != true))
	{
		RGBtoHSI(InImg, H, S, IV, height, width);

		std::vector<unsigned char> IVO;
		InitializeBufferImage(IVO, (height * width));

		if (IVO.empty() == false)
		{
			ImgConvolution(IV, IVO, height, width, Mask, winsize);

			HSItoRGB(OutImg, H, S, IVO, height, width);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}
