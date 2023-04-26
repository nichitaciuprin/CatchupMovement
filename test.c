#include <stdbool.h>
#include <tools/Math.h>
#include <tools/Console.h>
#include "tools/Time.h"

void Catchup(float* Apos, float* Avel, float Aacc, float Bpos, float Bvel, float deltaTime)
{
    float pos = *Apos - Bpos;
    float vel = *Avel - Bvel;

    float velAbs = MathAbs(vel);
    float haltTime = velAbs/Aacc;
    float haltOffset = vel*haltTime;
    float haltOffsetHalf = haltOffset/2;
    float pos2 = pos+haltOffsetHalf;
    int s1 = MathSign(pos);
    int s2 = MathSign(pos2);
    int s3 = MathSign(vel);
    bool isOvershoot = s1 == s3 || s1 != s2;
    int s = isOvershoot ? 1 : -1;
    int direction = -s2;
    float time2 = MathSqrt(MathAbs(-pos-haltOffsetHalf*s)/Aacc/2);
    float time1 = time2+haltTime*s;
    printf("%i %f %f\n",direction,time1,time2);
    // printf("%f %f\n",*Apos,Bpos);
    // printf("%f\n",haltTime);
    // printf("%i\n",s);

    // TODO
    if (time1 < 0)
    {
        // printf("pos == %.60f\n",pos);
        // printf("vel == %.60f\n",vel);
        // printf("!\n");
        return;
    }

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
    float Bpos = 100;
    float Bvel = 0;
    float deltaTimeSecods = 1;

    for (size_t i = 0; i < 10; i++)
    {
        Catchup(&Apos,&Avel,Aacc,Bpos,Bvel,deltaTimeSecods);
    }

    // Expected result
    // 1 5.000000 5.000000
    // 1 4.000000 5.000000
    // 1 3.000000 5.000000
    // 1 2.000000 5.000000
    // 1 1.000000 5.000000
    // 1 0.000000 5.000000
    // 1 0.000000 4.000000
    // 1 0.000000 3.000000
    // 1 0.000000 2.000000
    // 1 0.000000 1.000000
    return 0;
}