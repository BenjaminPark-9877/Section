#pragma once

#include <vector>
#include <windows.h>
#include <winnt.h>

#ifndef _BASICBONE_H_
#include "basicbone.h"
#endif

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif

#ifndef _USER_RGBQUAD_H_
#include "UserRGBQuad.h"
#endif

#ifndef _BITMAPFILEHEADER_H_
#include "BitmapFileHeader.h"
#endif

#ifndef _USERBITMAP_H_
#include "UserBitmap.h"
#endif

//------------------------------------------------------------------------------
// CBitmapClipBoard: 클립보드 연동 함수 객체
//------------------------------------------------------------------------------
class CBitmapClipBoard : private CBasicBone
{
public:
    bool NewDocument(CUserBitmap& cbmpNodeIn, CUserRGBQuad& cUserRGBQuad);
    void CopyClipboard(const CUserBitmap& cbmpNodeIn, CUserRGBQuad& cUserRGBQuad);

private:
    void CopyClipboard(const unsigned char* m_CpyImg, int height, int width, int biBitCount, const BITMAPINFOHEADER& dibHi, CUserRGBQuad& cUserRGBQuad);
    bool OpenImageFromClipBoard(LPSTR pDIB, CUserBitmap& bmpNode);
};
