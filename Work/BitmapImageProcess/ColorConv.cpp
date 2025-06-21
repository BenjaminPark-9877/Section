#include "pch.h"
#include "ColorConv.h"


#undef min
#undef max

constexpr double DEG_TO_RAD = 3.14159265358979323846 / 180.0;

CColorConv::CColorConv() {}
CColorConv::~CColorConv() {}

void CColorConv::RGB_To_Gray(double r, double g, double b, double* gray)
{
    if (!gray) return;
    *gray = r * 0.30 + g * 0.59 + b * 0.11;
}

void CColorConv::Gray_To_RGB(double gray, double* r, double* g, double* b)
{
    if (!r || !g || !b) return;
    *r = *g = *b = gray;
}

void CColorConv::RGB_To_CMY(double r, double g, double b, double* c, double* m, double* y)
{
    if (!c || !m || !y) return;
    *c = 1.0 - r;
    *m = 1.0 - g;
    *y = 1.0 - b;
}

void CColorConv::CMY_To_RGB(double c, double m, double y, double* r, double* g, double* b)
{
    if (!r || !g || !b) return;
    *r = 1.0 - c;
    *g = 1.0 - m;
    *b = 1.0 - y;
}

void CColorConv::RGB_To_HSV(double r, double g, double b, double* h, double* s, double* v)
{
    if (!h || !s || !v) return;

    double max_val = std::max({ r, g, b });
    double min_val = std::min({ r, g, b });

    *v = max_val;
    *s = (max_val != 0.0) ? (max_val - min_val) / max_val : 0.0;

    if (*s == 0.0)
    {
        *h = CColorConv::UNDEFINED;
        return;
    }

    double delta = max_val - min_val;

    if (r == max_val)
        *h = (g - b) / delta;
    else if (g == max_val)
        *h = 2.0 + (b - r) / delta;
    else
        *h = 4.0 + (r - g) / delta;

    *h *= 60.0;
    if (*h < 0.0)
        *h += 360.0;
}

void CColorConv::HSV_To_RGB(double h, double s, double v, double* r, double* g, double* b)
{
    if (!r || !g || !b) return;

    if (s == 0.0)
    {
        *r = *g = *b = v;
        return;
    }

    h = std::fmod(h, 360.0);
    if (h < 0.0) h += 360.0;
    h /= 60.0;

    int i = static_cast<int>(std::floor(h));
    double f = h - i;
    double p = v * (1.0 - s);
    double q = v * (1.0 - s * f);
    double t = v * (1.0 - s * (1.0 - f));

    switch (i)
    {
    case 0: *r = v; *g = t; *b = p; break;
    case 1: *r = q; *g = v; *b = p; break;
    case 2: *r = p; *g = v; *b = t; break;
    case 3: *r = p; *g = q; *b = v; break;
    case 4: *r = t; *g = p; *b = v; break;
    default: *r = v; *g = p; *b = q; break;
    }
}

void CColorConv::RGB_To_HSL(double r, double g, double b, double* h, double* l, double* s)
{
    if (!h || !l || !s) return;

    double max_val = std::max({ r, g, b });
    double min_val = std::min({ r, g, b });

    *l = (max_val + min_val) / 2.0;

    if (max_val == min_val)
    {
        *s = 0.0;
        *h = CColorConv::UNDEFINED;
        return;
    }

    double delta = max_val - min_val;

    *s = (*l < 0.5)
        ? delta / (max_val + min_val)
        : delta / (2.0 - max_val - min_val);

    if (r == max_val)
        *h = (g - b) / delta;
    else if (g == max_val)
        *h = 2.0 + (b - r) / delta;
    else
        *h = 4.0 + (r - g) / delta;

    *h *= 60.0;
    if (*h < 0.0)
        *h += 360.0;
}

void CColorConv::HSL_To_RGB(double h, double l, double s, double* r, double* g, double* b)
{
    if (!r || !g || !b) return;

    if (s == 0.0)
    {
        *r = *g = *b = l;
        return;
    }

    auto hue_to_rgb = [](double p, double q, double t) -> double {
        if (t < 0.0) t += 1.0;
        if (t > 1.0) t -= 1.0;
        if (t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
        if (t < 1.0 / 2.0) return q;
        if (t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
        return p;
    };

    double q = (l < 0.5) ? l * (1.0 + s) : l + s - l * s;
    double p = 2.0 * l - q;
    double hk = h / 360.0;

    *r = hue_to_rgb(p, q, hk + 1.0 / 3.0);
    *g = hue_to_rgb(p, q, hk);
    *b = hue_to_rgb(p, q, hk - 1.0 / 3.0);
}

void CColorConv::RGB_To_YIQ(double r, double g, double b, double* y, double* i, double* q)
{
    if (!y || !i || !q) return;

    *y = 0.299 * r + 0.587 * g + 0.114 * b;
    *i = 0.596 * r - 0.275 * g - 0.321 * b;
    *q = 0.212 * r - 0.528 * g + 0.311 * b;
}

void CColorConv::RGB_To_HSI(double r, double g, double b, double* h, double* s, double* i)
{
    if (!h || !s || !i) return;

    double min_val = std::min({ r, g, b });
    *i = (r + g + b) / 3.0;

    if ((r == g) && (g == b))
    {
        *s = 0.0;
        *h = CColorConv::UNDEFINED;
        return;
    }

    *s = 1.0 - (3.0 / (r + g + b)) * min_val;

    double num = r - 0.5 * g - 0.5 * b;
    double denom = std::sqrt((r - g) * (r - g) + (r - b) * (g - b));

    if (denom == 0.0)
    {
        *h = CColorConv::UNDEFINED;
    }
    else
    {
        double angle = std::clamp(num / denom, -1.0, 1.0);
        *h = std::acos(angle) * 180.0 / 3.14159265358979323846;
        if (b > g)
            *h = 360.0 - *h;
    }
}

void CColorConv::HSI_To_RGB(double h, double s, double i, double* r, double* g, double* b)
{
    if (!r || !g || !b) return;

    if (s == 0.0)
    {
        *r = *g = *b = i;
        return;
    }

    h = std::fmod(h, 360.0);
    if (h < 0.0) h += 360.0;

    double z = 1.0 - std::fabs(std::fmod(h / 60.0, 2) - 1.0);
    double c = (3 * i * s) / (1 + z);
    double x = c * z;
    double m = i * (1.0 - s);

    if (h < 120)
    {
        *r = c + m;
        *g = x + m;
        *b = m;
    }
    else if (h < 240)
    {
        h -= 120;
        *r = m;
        *g = c + m;
        *b = x + m;
    }
    else
    {
        h -= 240;
        *r = x + m;
        *g = m;
        *b = c + m;
    }
}
