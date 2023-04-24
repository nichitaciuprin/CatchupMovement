#pragma once

#include <stdlib.h>
// #include <stdbool.h>
#include <math.h>

#define MATH_M_PI_2 M_PI_2

float MathAbs(float value)
{
    return fabsf(value);
}
float MathSqrt(float value)
{
    return sqrtf(value);
}
float MathClamp(float value, float min, float max)
{
    float result = (value < min)? min : value;
    if (result > max) result = max;
    return result;
}
int MathSign(float value)
{
    if (value > 0) { return  1; }
    if (value < 0) { return -1; }
                     return  0;
}
float MathInverseLerp(float x, float y, float value)
{
    return (value - x)/(y - x);
}
float MathMod(float value, float div)
{
    return fmodf(value,div);
}
float MathPingPong(float value, float div)
{
    int whole = value/div;
    float rem = fmodf(value,div);
    return whole % 2 == 0 ? rem : div-rem;
}