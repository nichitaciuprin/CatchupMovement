#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "math.h"
#include "raylib.h"
#include "raymath.h"
#include "Math.h"
#include "Time.h"


const int m_windowWidth = 1200;
const int m_windowHeight = 400;
const int m_centerX = m_windowWidth/2;
const int m_centerY = m_windowHeight/2;
const int m_windowBorderSize = 100;
Vector2 m_Bpos = {m_centerX,m_centerY};
Vector2 m_Bvel = {0,0};
Vector2 m_Apos = {50,m_centerY};
Vector2 m_Avel = {0,0};
Vector2 m_oldMousePosition = {0,0};
Vector2 m_newMousePosition = {0,0};
float m_Bpos2 = m_centerX-m_windowBorderSize;
int state = 0;

Vector2 BVelocity(float time, float windowWidth, float offset)
{
    Vector2 result;
    time += windowWidth - offset*2;
    float length = windowWidth - offset*2;
    int direction = (int)(time/length) % 2 == 0 ? 1 : -1;
    result.x = 300*direction;
    result.y = 0;
    return result;
}
Vector2 BPosition(float time, float windowWidth, float windowHeight, float offset)
{
    Vector2 result;
    time += windowWidth - offset*2;
    float length = windowWidth - offset*2;
    // MathMod(time,12);
    // float rem = time;
    result.x = offset + MathPingPong(time,length);
    result.y = windowHeight/2;
    return result;
}

Vector2 GetMouseVelocity(Vector2 oldMousePosition, Vector2 newMousePosition, float deltaTime)
{
    Vector2 diff = Vector2Subtract(newMousePosition,oldMousePosition);
    diff.x /= deltaTime;
    diff.y /= deltaTime;
    return diff;
}
Vector2 TargetPosition(int windowWidth, int windowHeight, int mouseX)
{
    float centerX = Clamp(GetMouseX(),50,windowWidth-50);
    Vector2 result = {centerX,windowHeight/2};
    return result;
    // Vector2 result = {windowWidth/2,windowHeight/2};
    // return result;
}
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
    float time2 = MathSqrt(MathAbs(-pos-haltOffsetHalf*s)/Aacc);
    float time1 = time2+haltTime*s;

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
float GetSpeed(float position)
{
    float cap = 3000;
    float duno = fmodf(position,cap);
    float t = MathInverseLerp(0,cap,duno);
    if (t < 0.2f) return 100;
    if (t < 0.5f) return 200;
    return 300;
}
void Init()
{
    m_oldMousePosition = GetMousePosition();
    m_newMousePosition = GetMousePosition();
}
void HandleInput()
{
    if (IsKeyPressed('1'))
    {
        state = 0;
        return;
    }
    if (IsKeyPressed('2'))
    {
        state = 1;
        return;
    }
}
void Update(float deltaTime)
{
    const float m_Aacc = 600;

    Catchup(&m_Apos.x,&m_Avel.x,m_Aacc,m_Bpos.x,m_Bvel.x,deltaTime);
    m_Apos.y = m_Bpos.y;

    switch (state)
    {
        case 0:
        {
            float speed = GetSpeed(m_Bpos2);
            m_Bpos2 += speed*deltaTime;
            float oldDuno = m_Bpos.x;
            m_Bpos.x = m_windowBorderSize + MathPingPong(m_Bpos2,m_windowWidth-m_windowBorderSize*2);
            float newDuno = m_Bpos.x;
            float vel = newDuno-oldDuno;
            int sign = MathSign(vel);
            m_Bvel.x = speed*sign;
            break;
        }
        case 1:
        {
            m_newMousePosition = GetMousePosition();
            m_Bvel = GetMouseVelocity(m_oldMousePosition,m_newMousePosition,deltaTime);
            m_Bpos = TargetPosition(m_windowWidth,m_windowHeight,m_newMousePosition.x);
            m_oldMousePosition = m_newMousePosition;
            break;
        }
    }

}
void WindowInit()
{
    InitWindow(m_windowWidth, m_windowHeight, "CatchupMovement");
    printf("Window inited\n");
}
void WindowUpdate()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(m_windowBorderSize,m_centerY,m_windowWidth-m_windowBorderSize,m_centerY,DARKGREEN);
    const float radius = 10;
    DrawCircle(m_Bpos.x,m_Bpos.y,radius,WHITE);
    DrawCircle(m_Apos.x,m_Apos.y,radius,RED);
    DrawText("1-auto 2-manual",20,20,30,WHITE);
    EndDrawing();
}
int main(void)
{
    long fps = 60;
    long timeStep = CLOCKS_PER_SEC/fps;
    float deltaTime = 0.020f;
    long oldTime = 0;
    long newTime = 0;


    {
        oldTime = TimeNow();
        Init();
        WindowInit();
        newTime = TimeNow();
        TimeWaitLoop(oldTime,newTime,timeStep);
    }

    while (true)
    {
        if (WindowShouldClose()) break;

        oldTime = TimeNow();
        Update(deltaTime);
        WindowUpdate();
        newTime = TimeNow();
        TimeWaitLoop(oldTime,newTime,timeStep);
    }

    CloseWindow();

    return 0;
}