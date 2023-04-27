#pragma once

#include "raylib.h"
#include "Console.h"
#include "stdbool.h"

bool WindowInited = false;
Vector2 WindowMousePosition = {0,0};
Vector2 WindowMouseVelocity = {0,0};

const int WindowWidth = 1200;
const int WindowHeight = 400;
const int WindowOffset = 200;
const int WindowXCenter = WindowWidth/2;
const int WindowYCenter = WindowHeight/2;
const int WindowXLeft  =  WindowOffset;
const int WindowXRight = -WindowOffset+WindowWidth;
const int WindowLineLength = WindowWidth-WindowOffset*2;
const float WindowCyrcleRadius = 10;

void MouseUpdate()
{
    Vector2 mousePositionNew = GetMousePosition();
    mousePositionNew.x = MathClamp(mousePositionNew.x,WindowXLeft,WindowXRight);
    mousePositionNew.y = WindowYCenter;
    WindowMouseVelocity =  Vector2Subtract(mousePositionNew,WindowMousePosition);
    WindowMousePosition = mousePositionNew;
}
void WindowCreate()
{
    if (WindowInited) return;
    WindowInited = true;
    InitWindow(WindowWidth, WindowHeight, "CatchupMovement");
    ConsoleWriteLineStr("Window: Inited");
}
void WindowRender(float Apos, float Bpos)
{
    WindowCreate();
    MouseUpdate();
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(WindowXLeft,WindowYCenter,WindowXRight,WindowYCenter,DARKGREEN);
    DrawCircle(Bpos,WindowYCenter,WindowCyrcleRadius,WHITE);
    DrawCircle(Apos,WindowYCenter,WindowCyrcleRadius,RED);
    DrawText("1-auto 2-manual",20,20,30,WHITE);
    EndDrawing();
}
void WindowRender2(float Apos, float Bpos, float Bvel)
{
    WindowCreate();
    MouseUpdate();
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(WindowXLeft,WindowYCenter,WindowXRight,WindowYCenter,DARKGREEN);
    DrawCircle(Bpos,WindowYCenter,WindowCyrcleRadius,WHITE);
    DrawCircle(Apos,WindowYCenter,WindowCyrcleRadius,RED);
    DrawText("1-auto 2-manual",20,20,30,WHITE);
    char buffer[64];
    snprintf(buffer, sizeof buffer, "%f", Bvel);
    DrawText(buffer,Bpos-5,WindowYCenter-35,20,WHITE);
    // DrawText("B",Bpos-5,WindowYCenter-35,20,WHITE);
    EndDrawing();
}
void WindowClose()
{
    if (!WindowInited) return;
    WindowInited = false;
    CloseWindow();
}
bool WindowMustClose()
{
    return WindowShouldClose();
}
