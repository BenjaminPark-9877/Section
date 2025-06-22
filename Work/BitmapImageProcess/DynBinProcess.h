#ifndef _DYNBINPROCESS_H_
#define _DYNBINPROCESS_H_

#pragma once
#include <winnt.h>
#include <wingdi.h>
#include <vcruntime_string.h>
#include <windef.h>
#include <tchar.h>
#include <afx.h>
#include <array>

#include "BlobColoring.h"
#include "ColorConv.h"
#include "basicbone.h"
#include "UserMachro.h"
#include "UserRGBQuad.h"
#include "UserBitmap.h"

// 상수값을 매크로에서 const로 변경
constexpr int LUT_SIZE = 256;
constexpr int BITCOUNT_8 = 8;
constexpr int BITCOUNT_24 = 24;
constexpr int RGB_CHANNELS = 3;

///** 
//*description   : 동적 이진화 처리하는 객체
//*@parent class : private CBasicBone : 대입 연산자, 복사 생성자 호출 방지용
//*/
class CDynBinProcess : private CBasicBone
{
public:
    // 멤버 변수
    int m_nThresValueDisp;
    CUserBitmap m_bmpDynBinIn;
    CUserBitmap m_bmpDynBinOut;

public:
    // 생성자와 소멸자
    CDynBinProcess();
    ~CDynBinProcess();

    // 인라인 함수들
    inline void SetThreshValueDisp(int nThresValueDisp) { m_nThresValueDisp = nThresValueDisp; }
    inline int GetThreshValueDisp() const { return m_nThresValueDisp; }

    // 메소드들
    void Clear();
    bool OnInitDialog(int nThresValueDisp);
    bool OnNMCustomdrawSldThreshhold(int nThresValueDisp);
    bool OnPaint(const CPaintDC& dcView, const CRect& rect);
    bool GetImage(CUserBitmap& bitmapNode) const;
    bool SetImage(const CUserBitmap& bitmapNode);

    // 초기화 함수
    void Initialize(int nThresValueDisp = 0);

private:
    // 여기는 private 함수들은 필요한 경우, 특정 기능을 독립적으로 분리 가능
    bool CreateLUT(std::array<unsigned char, LUT_SIZE>& LUT);
    bool ApplyThreshold24bit(const std::array<unsigned char, LUT_SIZE>& LUT);
    bool ApplyThreshold8bit(const std::array<unsigned char, LUT_SIZE>& LUT);
};

#endif //_DYNBINPROCESS_H_