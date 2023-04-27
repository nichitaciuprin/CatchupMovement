#include "tools/Vector2.h"
#include "tools/Math.h"
#include "tools/MathCatchup.h"
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
void UpdateA(float* Apos, float* Avel, float Bpos, float Bvel, float deltaTime)
{
    MathCatchup(&_Apos,&_Avel,400,_Bpos,_Bvel,deltaTime);
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