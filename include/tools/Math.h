#pragma once

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
    if (value < min) { return min; }
    if (value > max) { return max; }
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
    return (value - x) / (y - x);
}
float MathMod(float value, float div)
{
    return fmodf(value, div);
}
float MathPingPong(float value, float length)
{
    // TODO. Maybe wrong negative number logic
    if (value < 0)
        value = length + MathAbs(value);

    int whole = value / length;
    float rem = fmodf(value, length);

    return whole % 2 == 0 ? rem : length - rem;
}