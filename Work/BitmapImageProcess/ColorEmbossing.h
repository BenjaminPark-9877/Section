#ifndef _COLOREMBOSSING_H_
#define _COLOREMBOSSING_H_
#pragma once

#ifndef _BITMAPACTION_H_
#include "BitmapAction.h"
#endif //_BITMAPACTION_H_

#include <vector>

class CColorEmbossing : public CBitmapAction
{
public:
    // 색상 엠보싱 작업 수행: 포인터 버전
    void Process(const CUserBitmap* pCbmpElementsIn);

    // 색상 엠보싱 작업 수행: 참조 버전 인라인 (포인터 버전 호출)
    inline void Process( CUserBitmap& pCbmpElementsIn) { Process(&pCbmpElementsIn); }

protected:
    // 실제 엠보싱 처리 함수 (3x3 컨볼루션)
    void ColorEmbossing(const unsigned char* InImg, unsigned char* OutImg, int height, int width);

private:
    // 마스크 초기화 헬퍼 (필요시 구현 필요)
    void InitializeMask(std::vector<float>& Mask, int winsize)
    {
        Mask.resize(winsize * winsize, 0.0f);
    }
};

#endif //_COLOREMBOSSING_H_
