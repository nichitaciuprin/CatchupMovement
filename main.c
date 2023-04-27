#include "tools/Vector2.h"
#include "tools/Math.h"
#include "tools/Time.h"
#include "tools/Console.h"
#include "tools/Window.h"

float _Apos = WindowXLeft;
float _Avel = 0;
float _Bpos = WindowXCenter;
float _Bvel = 0;
float _Bpos2 = 0;
int _state = 0;

float GetSpeed(float position)
{
    float cap = 3000;
    float duno = MathMod(position,cap);
    float t = MathInverseLerp(0,cap,duno);
    if (t < 0.2f) return 100;
    if (t < 0.5f) return 200;
    return 300;
}
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
void UpdateA(float* Apos, float* Avel, float Bpos, float Bvel, float deltaTime)
{
    // ConsoleWriteLineFloat(*Apos);
    // ConsoleWriteLineFloat(*Avel);
    // ConsoleWriteLineFloat(Bpos);
    // ConsoleWriteLineFloat(Bvel);
    // ConsoleWriteLineStr("---------");
    Catchup(&_Apos,&_Avel,400,_Bpos,_Bvel,deltaTime);
}
void UpdateB(float* Bpos, float* Bvel, float deltaTime)
{
    switch (_state)
    {
        case 0:
        {
            // _Bpos2 += 100*deltaTime;
            // *Bpos += GetSpeed(*Bpos)*deltaTime;
            // *Bpos = WindowXLeft + MathPingPong(WindowWidth2/2+_Bpos2,WindowWidth2);
            // _Bpos2 = MathPingPong(_Bpos2+deltaTime,WindowWidth2);
            break;
        }
        case 1:
        {
            *Bpos = WindowMousePosition.x;
            *Bvel = WindowMouseVelocity.x;
            break;
        }
    }
}
void Update(float deltaTime)
{
    UpdateB(&_Bpos,&_Bvel,deltaTime);
    UpdateA(&_Apos,&_Avel,_Bpos,_Bvel,deltaTime);
}
void HandleInput()
{
    if (IsKeyPressed('1')) { _state = 0; return; }
    if (IsKeyPressed('2')) { _state = 1; return; }
}
int main(void)
{
    WindowRender(_Apos,_Bpos);
    HandleInput();
    TimeWaitLoopMark();

    while (true)
    {
        if (WindowMustClose()) break;

        Update(TimeFixedDeltaTimeFloat);

        WindowRender(_Apos,_Bpos);
        HandleInput();
        TimeWaitLoopMark();
    }

    return 0;
}