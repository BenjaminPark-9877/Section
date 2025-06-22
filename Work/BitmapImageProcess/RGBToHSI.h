/////** 
////*description   : 비트맵 영상 받아서 RGB To HSI 작업 수행 클래스 정의 헤더 파일
////*               
////* 
////*/
#ifndef _RGBTOHSI_H_
#define _RGBTOHSI_H_

#pragma once

#include "BitmapAction.h"

///** 
//*description   : 비트맵 영상 받아서 RGB To HSI 작업 수행 클래스
//*@parent class : public CBitmapAction  
//*/
class CRGBToHSI : public CBitmapAction
{
	//// 멤버 변수 정의 부분
public:

protected:

private:

	//// 멤버 함수 정의 부분
public:

	//*description   : RGB -> HSI 영상으로 변환 후 분할 (오버로드: 참조 전달)
	inline void Process(const CUserBitmap& pCbmpElementsIn) { Process(&pCbmpElementsIn); }

	//*description   : RGB -> HSI 영상으로 변환 후 분할
	void Process(const CUserBitmap* pCbmpElementsIn);

protected:

	//*description   : RGB 이미지로부터 HSI 변환
	bool RGB2HSI(const unsigned char* InImg, unsigned char* OutImg, int height, int width);

	//*description   : 하나의 색상 채널씩 분할 출력
	bool SpiltOneColorImage(const CUserBitmap& bitmapNode, int nType = THREE_COLOR_TYPE);

private:

};

#endif //_RGBTOHSI_H_