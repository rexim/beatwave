#ifndef CORE_FLOATCOLOR_HPP_
#define CORE_FLOATCOLOR_HPP_

class FloatColor
{
public:
    FloatColor(float r, float g, float b, float a);
    FloatColor();

    float r, g, b, a;
};

FloatColor operator+(const FloatColor &a, const FloatColor &b);
FloatColor operator-(const FloatColor &a, const FloatColor &b);
FloatColor operator*(const FloatColor &a, float factor);
FloatColor &operator+=(FloatColor &a, const FloatColor &b);

#endif  // CORE_FLOATCOLOR_HPP_
