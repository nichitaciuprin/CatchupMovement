#pragma once

#include <stdbool.h>
#include <tools/Math.h>
// TODO
// #include <tools/Vector3.h>

Vector3 MathCatchupTargetVelocity(Vector3 pos, Vector3 vel, float acc)
{
    if (pos.x == 0 && pos.y == 0 && pos.z == 0) return pos;

    Vector3 direction = pos;
    direction = Vector3Negate(direction);
    direction = Vector3Normalize(direction);
    float distance = Vector3Length(pos);
    float speed = MathSqrt(distance*acc*2);

    Vector3 result;
    result = direction;
    result.x *= speed; // TODO
    result.y *= speed; // TODO
    result.z *= speed; // TODO
    result = Vector3Subtract(result,vel);
    return result;
}
// TODO
void MathCatchupDuno(Vector3* Apos, Vector3* Avel, float acc, Vector3 Bpos, Vector3 Bvel, float deltaTime)
{
    Vector3 pos = Vector3Subtract(*Apos,Bpos);
    Vector3 vel = Vector3Subtract(*Avel,Bvel);

    Vector3 oldVel = *Avel;
    Vector3 targetVelocity = MathCatchupTargetVelocity(pos,vel,acc);
    Vector3 newVel = targetVelocity; // TODO MoveTowards(oldVel,targetVelocity,acc*deltaTime);
    Vector3 normVel = Vector3Add(oldVel,newVel);
    normVel.x /= 2; // TODO
    normVel.y /= 2; // TODO
    normVel.z /= 2; // TODO
    Vector3 posChange = normVel;
    posChange.x *= deltaTime; // TODO
    posChange.y *= deltaTime; // TODO
    posChange.z *= deltaTime; // TODO

    *Apos = Vector3Add(*Apos,posChange);
    *Avel = normVel;
    // TODO
    // Apos = Snap(Apos,Bpos);
}
void MathCatchupMove(float* pos, float* vel, float acc, int direction, float time)
{
    float velOffset = direction*acc*time;
    float posOffset = (*vel)*time + velOffset*time/2;
    *vel += velOffset;
    *pos += posOffset;
}
void MathCatchupMoveInfo(float pos, float vel, float Aacc, int* direction_out, float* time1_out, float* time2_out)
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

    *direction_out = -s2;

    // Edge case. Can happen if A halting directly to B position.
    if (*direction_out == 0)
        *direction_out = s1;

    if (mustHalt)
    {
        float area3 = MathAbs(pos2);
        float halfTime = MathSqrt(area3/Aacc);
        *time1_out = halfTime + haltTime;
        *time2_out = halfTime;
    }
    else
    {
        float area1 = vel*vel/Aacc/2;
        float area2 = posAbs;
        float area3 = area1+area2;
        float halfTime = MathSqrt(area3/Aacc);
        *time1_out = halfTime - haltTime;
        *time2_out = halfTime;

        // Edge case. float calculation can be inaccurate when A is very close to B and results in negative time.
        if (*time1_out < 0) *time1_out = 0;
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