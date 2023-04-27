#pragma once

#include <stdbool.h>
#include <tools/Math.h>

void MathCatchupMove(float* pos, float* vel, float acc, int direction, float time)
{
    float velOffset = direction*acc*time;
    float posOffset = (*vel)*time + velOffset*time/2;
    *vel += velOffset;
    *pos += posOffset;
}
void MathCatchupMoveInfo(float pos, float vel, float Aacc, int* direction, float* time1, float* time2)
{
    float posAbs = MathAbs(pos);
    float velAbs = MathAbs(vel);
    float haltTime = velAbs/Aacc;
    float haltOffset = vel*haltTime/2;
    float pos2 = pos+haltOffset;
    int s1 = MathSign(pos);
    int s2 = MathSign(pos2);
    int s3 = MathSign(vel);
    bool mustHalt = s1 != s2 || s1 == s3;

    *direction = -s2;

    // Edge case. Can happen if A halting directly to B position.
    if (*direction == 0)
        *direction = s1;

    if (mustHalt)
    {
        float area3 = MathAbs(pos2);
        float halfTime = MathSqrt(area3/Aacc);
        *time1 = halfTime + haltTime;
        *time2 = halfTime;
    }
    else
    {
        float area1 = vel*vel/Aacc/2;
        float area2 = posAbs;
        float area3 = area1+area2;
        float halfTime = MathSqrt(area3/Aacc);
        *time1 = halfTime - haltTime;
        *time2 = halfTime;

        // Edge case. float calculation can be inaccurate when A is very close to B and results in negative time.
        if (*time1 < 0) *time1 = 0;
    }
}
void MathCatchup(float* Apos, float* Avel, float Aacc, float Bpos, float Bvel, float deltaTime)
{
    float pos = *Apos - Bpos;
    float vel = *Avel - Bvel;
    int direction = 0;
    float time1 = 0;
    float time2 = 0;
    MathCatchupMoveInfo(pos,vel,Aacc,&direction,&time1,&time2);

    int dir = direction;
    float t = time1;

    t = MathClamp(deltaTime,0,t);
    deltaTime -= t;
    MathCatchupMove(Apos,Avel,Aacc,dir,t);
    if (deltaTime == 0) return;

    dir = -direction;
    t = time2;

    t = MathClamp(deltaTime,0,t);
    deltaTime -= t;
    MathCatchupMove(Apos,Avel,Aacc,dir,t);
    if (deltaTime == 0) return;

    *Apos += (*Avel)*deltaTime;
}