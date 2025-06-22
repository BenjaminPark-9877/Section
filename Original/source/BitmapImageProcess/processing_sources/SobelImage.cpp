/////** 
////*description   : Sobel �۾� ���� Ŭ���� ���� �ҽ� ����
////*               
////* 
////*/
#include "pch.h"
#include "SobelImage.h"

//*description   : 
//*@param input  :  
//*@param output : 
//*@return		 :  
//*/
bool CSobelImage::InitializeMask_1St(std::vector<float>& mask, const size_t& winsize)
{
	std::vector<float> pattern;
	
	pattern.resize(winsize * winsize);

	pattern = {-1,0,1,-2,0,2,-1,0,1};

	FillMaskPattern(mask, pattern, winsize);

	return true;
}

//*description   : 
//*@param input  :  
//*@param output : 
//*@return		 :  
//*/
bool CSobelImage::InitializeMask_2nd(std::vector<float>& mask, const size_t& winsize)
{
	std::vector<float> pattern;
	
	pattern.resize(winsize * winsize);

	pattern = {1,2,1,0,0,0,-1,-2,-1};

	FillMaskPattern(mask, pattern, winsize);

	return true;
}
