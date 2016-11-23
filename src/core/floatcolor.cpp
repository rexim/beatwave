#include <core/floatcolor.hpp>

FloatColor::FloatColor(float r, float g, float b, float a):
    r(r), g(g), b(b), a(a)
{}

FloatColor::FloatColor():
    r(0.0f), g(0.0f), b(0.0f), a(0.0f)
{}

FloatColor operator+(const FloatColor &a, const FloatColor &b)
{
    return FloatColor(a.r + b.r,
                      a.g + b.g,
                      a.b + b.b,
                      a.a + b.a);
}

FloatColor operator-(const FloatColor &a, const FloatColor &b)
{
    return FloatColor(a.r - b.r,
                      a.g - b.g,
                      a.b - b.b,
                      a.a - b.a);
}

FloatColor operator*(const FloatColor &a, float factor)
{
    return FloatColor(a.r * factor,
                      a.g * factor,
                      a.b * factor,
                      a.a * factor);
}

FloatColor &operator+=(FloatColor &a, const FloatColor &b)
{
    a.r += b.r;
    a.g += b.g;
    a.b += b.b;
    a.a += b.a;
    return a;
}
