/////** 
////*description   : Sobel 작업 수행 클래스 정의 헤더 파일
////*/
#ifndef _SOBELIMAGE_H_
#define _SOBELIMAGE_H_
#pragma once

#ifndef _DOUBLEMASKIMAGE_H_
#include "DoubleMaskImage.h"
#endif //_DOUBLEMASKIMAGE_H_

///** 
//*description   : Sobel 작업 수행 클래스
//*@parent class : public CDoubleMaskImage  
//*/
class CSobelImage : public CDoubleMaskImage
{
	//// 멤버 함수 정의 부분
public:
	//*description   : Sobel 필터 초기화 (1차 마스크)
	//*@param input  : 필터 마스크
	//*@param output : 윈도우 크기
	//*@return		 : 초기화 성공 여부
	//*/
	bool InitializeMask_1st(std::vector<float>& mask, const size_t& winsize);

	//*description   : Sobel 필터 초기화 (2차 마스크)
	//*@param input  : 필터 마스크
	//*@param output : 윈도우 크기
	//*@return		 : 초기화 성공 여부
	//*/
	bool InitializeMask_2nd(std::vector<float>& mask, const size_t& winsize);

protected:
private:

};
#endif //_SOBELIMAGE_H_