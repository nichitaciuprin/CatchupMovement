#pragma once

#include <stdlib.h>
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
double MathSqrt2(double value)
{
    return sqrt(value);
}
float MathClamp(float value, float min, float max)
{
    if (value < min) { return min; };
    if (value > max) { return max; };
                       return value;
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
float MathPingPong(float value, float length)
{
    // TODO. Maybe wrong negative number logic
    if (value < 0) { value = length + MathAbs(value); }
    int whole = value/length;
    float rem = fmodf(value,length);
    return whole % 2 == 0 ? rem : length-rem;
}
void MathPingPong2(float value, float length, float* valueNew, int* directionNew)
{
    if (value < 0) { value = length + MathAbs(value); }
    int whole = value/length;
    float rem = fmodf(value,length);
    if (whole % 2 == 0)
    {
        *directionNew = 1;
        *valueNew = rem;
    }
    else
    {
        *directionNew = -1;
        *valueNew = length-rem;
    }
}