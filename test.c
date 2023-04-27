#include <stdbool.h>
#include <tools/Math.h>
#include <tools/Console.h>
#include "tools/Time.h"

void Catchup(float* Apos, float* Avel, float Aacc, float Bpos, float Bvel, float deltaTime)
{
    float pos = *Apos - Bpos;
    float vel = *Avel - Bvel;

    float posAbs = MathAbs(pos);
    float velAbs = MathAbs(vel);
    float haltTime = velAbs/Aacc;
    float haltOffset = vel*haltTime/2;
    float pos2 = pos+haltOffset;
    int s1 = MathSign(pos);
    int s2 = MathSign(pos2);
    int s3 = MathSign(vel);
    bool mustHalt = s1 != s2 || s1 == s3;

    int direction = 0;
    float time1 = 0;
    float time2 = 0;

    direction = -s2;

    // Edge case. Can happen if A halting directly to B position
    if (direction == 0)
        direction = s1;

    if (mustHalt)
    {
        float area3 = MathAbs(pos2);
        float halfTime = MathSqrt(area3/Aacc);
        time1 = halfTime + haltTime;
        time2 = halfTime;
    }
    else
    {
        float area1 = vel*vel/Aacc/2;
        float area2 = posAbs;
        float area3 = area1+area2;
        float halfTime = MathSqrt(area3/Aacc);
        time1 = halfTime - haltTime;
        time2 = halfTime;

        // Edge case. float calc can be inaccurate when A very close to B
        if (time1 < 0) time1 = 0;

        // TODO
        // if (time1 < 0) return;
    }

    if (direction > 0)
        printf(" %i",direction);
    else
        printf("%i",direction);
    printf(" %f %f\n",time1,time2);

    int dir = direction;
    float t = time1;

    {
        t = Clamp(deltaTime,0,t);
        deltaTime -= t;
        float value1 = dir*Aacc*t;
        *Apos += (*Avel)*t;
        *Apos += value1*t/2;
        *Avel += value1;
        if (deltaTime == 0) return;
    }

    dir = -direction;
    t = time2;

    {
        t = Clamp(deltaTime,0,t);
        deltaTime -= t;
        float value1 = dir*Aacc*t;
        *Apos += (*Avel)*t;
        *Apos += value1*t/2;
        *Avel += value1;
        if (deltaTime == 0) return;
    }

    *Apos += (*Avel)*deltaTime;
}
int main(void)
{
    float Apos = 0;
    float Avel = 0;
    float Aacc = 2;
    float Bpos = 50;
    float Bvel = 0;
    float deltaTimeSecods = 1;

    for (size_t i = 0; i < 10; i++)
        Catchup(&Apos,&Avel,Aacc,Bpos,Bvel,deltaTimeSecods);

    // Expected result
    //  1 5.000000 5.000000
    //  1 4.000000 5.000000
    //  1 3.000000 5.000000
    //  1 2.000000 5.000000
    //  1 1.000000 5.000000
    // -1 5.000000 0.000000
    // -1 4.000000 0.000000
    // -1 3.000000 0.000000
    // -1 2.000000 0.000000
    // -1 1.000000 0.000000
    return 0;
}