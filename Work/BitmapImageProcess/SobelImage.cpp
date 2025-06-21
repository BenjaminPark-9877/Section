/////** 
////*description   : Sobel �۾� ���� Ŭ���� ���� �ҽ� ����
////*/
#include "pch.h"
#include "SobelImage.h"

//*description   : Sobel X ���� ����ũ �ʱ�ȭ (1st)
//*@param input  : mask - ����ũ�� ����� ����
//*@param input  : winsize - ����ũ�� ���μ��� ũ�� (���� 3)
//*@return       : ���� ����
//*/
bool CSobelImage::InitializeMask_1st(std::vector<float>& mask, const size_t& winsize)
{
	if (winsize != 3) return false;  // Sobel ����ũ�� �Ϲ������� 3x3

	const std::vector<float> pattern = {
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1
	};

	return FillMaskPattern(mask, pattern, winsize);
}

//*description   : Sobel Y ���� ����ũ �ʱ�ȭ (2nd)
//*@param input  : mask - ����ũ�� ����� ����
//*@param input  : winsize - ����ũ�� ���μ��� ũ�� (���� 3)
//*@return       : ���� ����
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