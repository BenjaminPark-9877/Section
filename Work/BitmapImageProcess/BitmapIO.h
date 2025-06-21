// BitmapIO.h
#ifndef _BITMAPIO_H_
#define _BITMAPIO_H_
#pragma once

#include <winnt.h>
#include <vector>
#include <string>
#include <afx.h> // For CFile

#include "basicbone.h"
#include "UserMachro.h"
#include "UserRGBQuad.h"
#include "BitmapFileHeader.h"
#include "UserBitmap.h"

class CBitmapIO : private CBasicBone
{
public:
    bool Open(LPCTSTR lpszPathName, CUserBitmap& bmpNode, RGBQUAD* palRGB = nullptr);
    bool Save(LPCTSTR lpszPathName, CUserBitmap& bmpNode, RGBQUAD* palRGB = nullptr);

protected:
    CString AddExtendString(CString lpszPathName);
};

#endif //_BITMAPIO_H_

