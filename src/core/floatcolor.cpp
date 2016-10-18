#include <core/floatcolor.hpp>

FloatColor::FloatColor(float r, float g, float b):
    r(r), g(g), b(b)
{}

FloatColor::FloatColor():
    r(0.0f), g(0.0f), b(0.0f)
{}

FloatColor operator+(const FloatColor &a, const FloatColor &b)
{
    return FloatColor(a.r + b.r, a.g + b.g, a.b + b.b);
}

FloatColor operator-(const FloatColor &a, const FloatColor &b)
{
    return FloatColor(a.r - b.r, a.g - b.g, a.b - b.b);
}

FloatColor operator*(const FloatColor &a, float factor)
{
    return FloatColor(a.r * factor, a.g * factor, a.b * factor);
}

FloatColor &operator+=(FloatColor &a, const FloatColor &b)
{
    a.r += b.r;
    a.g += b.g;
    a.b += b.b;
    return a;
}
