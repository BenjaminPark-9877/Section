#ifndef _BITMAPPROCESS_H_
#define _BITMAPPROCESS_H_

#pragma once

#include <afxwin.h> // CDC, CClientDC ��
#include <tchar.h>
#include <string>

#ifndef _BASICBONE_H_
#include "basicbone.h"
#endif //_BASICBONE_H_

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif //_USERMACHRO_H_


#include "UserBitmap.h"
#include "UserRGBQuad.h"
#include "BitmapIO.h"
#include "RGBToHSI.h"
#include "RGBToGray.h"
#include "ColorEmbossing.h"
#include "RGBSharpening.h"
#include "SobelImage.h"
#include "ChannelSplitRgb.h"
#include "ActBlobcoloring.h"
#include "BitmapClipBoard.h"
#include "CDLG_DYNBIN.h"

class CBitmapProcess : private CBasicBone
{
public:
    CBitmapProcess();
    ~CBitmapProcess();

    void Clear();
    void Initialize();

    bool SaveImageToFile(LPCTSTR lpszPathName);
    bool OpenImageFromFile(LPCTSTR lpszPathName);

    void RGB2HSI();
    void RGB2Gray();
    void ColorEmbossing();
    void RGBShapening();
    void OnRgbSobel();
    void ChannelsplitRgb();
    void Blobcoloring(CClientDC* pDc);

    bool OnImgDynbinSet(CDLG_DYNBIN* pDlg);
    bool OnImgDynbinGet(CDLG_DYNBIN* pDlg);

    bool NewDocument();

    size_t GetImageWidth() const;
    size_t GetImageHeight() const;
    int GetImageBitCount() const;
    int GetImageRwSize() const;

    bool DrawImage(CDC* pDC);

    void GetImageSize(CSize& csSizeImage) const;

    void CopyClipboard();

private:
    // ����� ����� ���� ���� ������ �� ���� ������
    CBitmapProcess(const CBitmapProcess&) = delete;  // ���� ������ ����
    CBitmapProcess& operator=(const CBitmapProcess&) = delete;  // ���� ���� ������ ����
    CBitmapProcess(CBitmapProcess&&) = delete;  // �̵� ������ ����
    CBitmapProcess& operator=(CBitmapProcess&&) = delete;  // �̵� ���� ������ ����

private:
    CUserBitmap m_cbmpNodeIn;
    CUserRGBQuad m_cuserRGBQuad;
};

#endif //_BITMAPPROCESS_H_