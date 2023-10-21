#pragma once

void CatchupMove(float* pos, float* vel, float acc, int direction, float time)
{
    float velocityOffset = direction * acc * time;
    float positionOffset = (*vel) * time + velocityOffset * time / 2;
    *vel += velocityOffset;
    *pos += positionOffset;
}
void CatchupInfo(float pos, float vel, float Aacc, int* outDirection, float* outTime1, float* outTime2)
{
    float posAbs = MathAbs(pos);
    float velAbs = MathAbs(vel);
    float haltTime = velAbs / Aacc;
    float haltOffset = vel * haltTime / 2;
    float pos2 = pos + haltOffset;
    int s1 = MathSign(pos);
    int s2 = MathSign(pos2);
    int s3 = MathSign(vel);
    bool mustHalt = s1 != s2 || s1 == s3;

    *outDirection = -s2;

    // can happen if A halting directly to B position.
    if (*outDirection == 0)
        *outDirection = s1;

    if (mustHalt)
    {
        float area3 = MathAbs(pos2);
        float halfTime = MathSqrt(area3 / Aacc);
        *outTime1 = halfTime + haltTime;
        *outTime2 = halfTime;
    }
    else
    {
        float area1 = vel * vel / Aacc / 2;
        float area2 = posAbs;
        float area3 = area1 + area2;
        float halfTime = MathSqrt(area3 / Aacc);
        *outTime1 = halfTime - haltTime;
        *outTime2 = halfTime;

        // float calculation can be inaccurate
        // when A is very close to B and results in negative time.
        if (*outTime1 < 0)
            *outTime1 = 0;
    }
}
void CatchupUpdate(float* Apos, float* Avel, float Aacc, float Bpos, float Bvel, float deltaTime)
{
    float pos = *Apos - Bpos;
    float vel = *Avel - Bvel;

    int direction = 0;
    float time1 = 0;
    float time2 = 0;
    CatchupInfo(pos, vel, Aacc, &direction, &time1, &time2);

    int dir = direction;
    float t = time1;

    t = MathClamp(deltaTime, 0, t);
    deltaTime -= t;
    CatchupMove(Apos, Avel, Aacc, dir, t);
    if (deltaTime == 0) return;

    dir = -direction;
    t = time2;

    t = MathClamp(deltaTime, 0, t);
    deltaTime -= t;
    CatchupMove(Apos, Avel, Aacc, dir, t);
    if (deltaTime == 0) return;

    *Apos += (*Avel) * deltaTime;
}