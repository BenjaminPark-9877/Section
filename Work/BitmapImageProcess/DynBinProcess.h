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

// ������� ��ũ�ο��� const�� ����
constexpr int LUT_SIZE = 256;
constexpr int BITCOUNT_8 = 8;
constexpr int BITCOUNT_24 = 24;
constexpr int RGB_CHANNELS = 3;

///** 
//*description   : ���� ����ȭ ó���ϴ� ��ü
//*@parent class : private CBasicBone : ���� ������, ���� ������ ȣ�� ������
//*/
class CDynBinProcess : private CBasicBone
{
public:
    // ��� ����
    int m_nThresValueDisp;
    CUserBitmap m_bmpDynBinIn;
    CUserBitmap m_bmpDynBinOut;

public:
    // �����ڿ� �Ҹ���
    CDynBinProcess();
    ~CDynBinProcess();

    // �ζ��� �Լ���
    inline void SetThreshValueDisp(int nThresValueDisp) { m_nThresValueDisp = nThresValueDisp; }
    inline int GetThreshValueDisp() const { return m_nThresValueDisp; }

    // �޼ҵ��
    void Clear();
    bool OnInitDialog(int nThresValueDisp);
    bool OnNMCustomdrawSldThreshhold(int nThresValueDisp);
    bool OnPaint(const CPaintDC& dcView, const CRect& rect);
    bool GetImage(CUserBitmap& bitmapNode) const;
    bool SetImage(const CUserBitmap& bitmapNode);

    // �ʱ�ȭ �Լ�
    void Initialize(int nThresValueDisp = 0);

private:
    // ����� private �Լ����� �ʿ��� ���, Ư�� ����� ���������� �и� ����
    bool CreateLUT(std::array<unsigned char, LUT_SIZE>& LUT);
    bool ApplyThreshold24bit(const std::array<unsigned char, LUT_SIZE>& LUT);
    bool ApplyThreshold8bit(const std::array<unsigned char, LUT_SIZE>& LUT);
};

#endif //_DYNBINPROCESS_H_