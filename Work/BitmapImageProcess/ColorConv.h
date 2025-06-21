#ifndef _COLORCONV_H_
#define _COLORCONV_H_

#pragma once

#ifndef _USERMACHRO_H_
#include "UserMachro.h"
#endif

#ifndef _BASICBONE_H_
#include "BasicBone.h"
#endif

#include <cmath>
#include <limits>
#include <algorithm>

class CColorConv : private CBasicBone
{
private:
    static constexpr double UNDEFINED = std::numeric_limits<double>::quiet_NaN();

public:
    CColorConv();
    virtual ~CColorConv();

    void RGB_To_Gray(double r, double g, double b, double* gray);
    void Gray_To_RGB(double gray, double* r, double* g, double* b);

    void RGB_To_CMY(double r, double g, double b, double* c, double* m, double* y);
    void CMY_To_RGB(double c, double m, double y, double* r, double* g, double* b);

    void RGB_To_HSI(double r, double g, double b, double* h, double* s, double* i);
    void HSI_To_RGB(double h, double s, double i, double* r, double* g, double* b);

    void RGB_To_HSV(double r, double g, double b, double* h, double* s, double* v);
    void HSV_To_RGB(double h, double s, double v, double* r, double* g, double* b);

    void RGB_To_HSL(double r, double g, double b, double* h, double* l, double* s);
    void HSL_To_RGB(double h, double l, double s, double* r, double* g, double* b);

    void RGB_To_YIQ(double r, double g, double b, double* y, double* i, double* q);

private:
    // 방어적 상속을 위한 복사 생성자 및 대입 연산자
    CColorConv(const CColorConv&) = delete;  // 복사 생성자 금지
    CColorConv& operator=(const CColorConv&) = delete;  // 복사 대입 연산자 금지
    CColorConv(CColorConv&&) = delete;  // 이동 생성자 금지
    CColorConv& operator=(CColorConv&&) = delete;  // 이동 대입 연산자 금지
};

#endif // _COLORCONV_H_
