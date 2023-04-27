#include "tools/Vector2.h"
#include "tools/Math.h"
#include "tools/MathCatchup.h"
#include "tools/Time.h"
#include "tools/Console.h"
#include "tools/Window.h"

float Apos = WindowXLeft;
float Avel = 0;
float Bpos = WindowXCenter;
float Bvel = 0;
float Bpos2 = 0;
int state = 0;

float Bspeed()
{
    float cap = 3000;
    float duno = MathMod(Bpos,cap);
    float t = MathInverseLerp(0,cap,duno);
    if (t < 0.2f) return 100;
    if (t < 0.5f) return 200;
    return 300;
}
void UpdateA(float deltaTime)
{
    MathCatchup(&Apos,&Avel,400,Bpos,Bvel,deltaTime);
}
void UpdateB(float deltaTime)
{
    switch (state)
    {
        case 0:
        {
            // Bpos2 += 100*deltaTime;
            // *Bpos += Bspeed(*Bpos)*deltaTime;
            // *Bpos = WindowXLeft + MathPingPong(WindowWidth2/2+Bpos2,WindowWidth2);
            // Bpos2 = MathPingPong(Bpos2+deltaTime,WindowWidth2);
            break;
        }
        case 1:
        {
            Bpos = WindowMousePosition.x;
            Bvel = WindowMouseVelocity.x;
            break;
        }
    }
}
void Update(float deltaTime)
{
    UpdateA(deltaTime);
    UpdateB(deltaTime);
}
void HandleInput()
{
    if (IsKeyPressed('1')) { state = 0; return; }
    if (IsKeyPressed('2')) { state = 1; return; }
}
int main(void)
{
    WindowRender(Apos,Bpos);
    HandleInput();
    TimeWaitLoopMark();

    while (true)
    {
        if (WindowMustClose()) break;

        Update(TimeFixedDeltaTimeFloat);

        WindowRender(Apos,Bpos);
        HandleInput();
        TimeWaitLoopMark();
    }

    return 0;
}