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
    // ���� ������ �۾� ����: ������ ����
    void Process(const CUserBitmap* pCbmpElementsIn);

    // ���� ������ �۾� ����: ���� ���� �ζ��� (������ ���� ȣ��)
    inline void Process( CUserBitmap& pCbmpElementsIn) { Process(&pCbmpElementsIn); }

protected:
    // ���� ������ ó�� �Լ� (3x3 �������)
    void ColorEmbossing(const unsigned char* InImg, unsigned char* OutImg, int height, int width);

private:
    // ����ũ �ʱ�ȭ ���� (�ʿ�� ���� �ʿ�)
    void InitializeMask(std::vector<float>& Mask, int winsize)
    {
        Mask.resize(winsize * winsize, 0.0f);
    }
};

#endif //_COLOREMBOSSING_H_
