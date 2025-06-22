/////** 
////*description   : Sobel 작업 수행 클래스 정의 소스 파일
////*/
#include "pch.h"
#include "SobelImage.h"

//*description   : Sobel X 방향 마스크 초기화 (1st)
//*@param input  : mask - 마스크가 저장될 벡터
//*@param input  : winsize - 마스크의 가로세로 크기 (보통 3)
//*@return       : 성공 여부
//*/
bool CSobelImage::InitializeMask_1st(std::vector<float>& mask, const size_t& winsize)
{
	if (winsize != 3) return false;  // Sobel 마스크는 일반적으로 3x3

	const std::vector<float> pattern = {
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1
	};

	return FillMaskPattern(mask, pattern, winsize);
}

//*description   : Sobel Y 방향 마스크 초기화 (2nd)
//*@param input  : mask - 마스크가 저장될 벡터
//*@param input  : winsize - 마스크의 가로세로 크기 (보통 3)
//*@return       : 성공 여부
//*/
bool CSobelImage::InitializeMask_2nd(std::vector<float>& mask, const size_t& winsize)
{
	if (winsize != 3) return false;

	const std::vector<float> pattern = {
		 1,  2,  1,
		 0,  0,  0,
		-1, -2, -1
	};

	return FillMaskPattern(mask, pattern, winsize);
}