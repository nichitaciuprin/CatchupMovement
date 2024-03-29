#include <tools/Tools.h>

enum AppState
{
    AppStateAuto,
    AppStateManual
};

float Apos = WindowXLeft;
float Bpos = WindowXCenter;
float BposDist = WindowLineLength / 2;
float Avel = 0;
float Bvel = 0;
int BState = AppStateAuto;

float GetBvel()
{
    float speed1 = 80;
    float speed2 = speed1 * 2;
    float speed3 = speed1 * 3;

    float range1 = 800;
    float range2 = range1 * 2;
    float range3 = range1 * 3;

    float curentRange = MathMod(BposDist, range3);

    float speed;

    if      (curentRange < range1) { speed = speed1; }
    else if (curentRange < range2) { speed = speed2; }
    else                           { speed = speed3; }

    float mod = MathMod(BposDist,WindowLineLength * 2);
    int direction = mod < WindowLineLength ? 1 : -1;

    return speed * direction;
}
void UpdateA(float deltaTime)
{
    CatchupUpdate(&Apos, &Avel, 500, Bpos, Bvel, deltaTime);
}
void UpdateB(float deltaTime)
{
    switch (BState)
    {
        case AppStateAuto:
        {
            Bvel = GetBvel();
            BposDist += MathAbs(Bvel) * deltaTime;
            Bpos = WindowXLeft + MathPingPong(BposDist, WindowLineLength);
            break;
        }
        case AppStateManual:
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
    if (IsKeyPressed('1')) { BState = 0; return; }
    if (IsKeyPressed('2')) { BState = 1; return; }
}
int main()
{
    // testing gdb stacktrace on segfault
    // *(char*)NULL = 0;

    HandleInput();
    WindowRender(Apos, Bpos);

    while (!WindowMustClose())
    {
        HandleInput();
        Update(WindowFixedDeltaTime);
    	WindowRender(Apos, Bpos);
    }

    return 0;
}
