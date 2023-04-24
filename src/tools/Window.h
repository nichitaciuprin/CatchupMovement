#pragma once

#include "raylib.h"
#include "Console.h"
#include "stdbool.h"

bool WindowInited = false;

const char * WindowName = "CatchupMovement";
const int WindowWidth = 1200;
const int WindowHeight = 400;
const int WindowOffset = 100;
const int WindowXCenter = WindowWidth/2;
const int WindowYCenter = WindowHeight/2;
const int WindowXLeft  =  WindowOffset;
const int WindowXRight = -WindowOffset+WindowWidth;
const float WindowCyrcleRadius = 10;
void WindowCreate()
{
    if (WindowInited) return;
    WindowInited = true;
    InitWindow(WindowWidth, WindowHeight, WindowName);
    ConsoleWriteLineStr("Window: Inited");
}
void WindowUpdate(float Apos, float Bpos)
{
    if (!WindowInited) return;
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(WindowXLeft,WindowYCenter,WindowXRight,WindowYCenter,DARKGREEN);
    DrawCircle(Apos,WindowYCenter,WindowCyrcleRadius,RED);
    DrawCircle(Bpos,WindowYCenter,WindowCyrcleRadius,WHITE);
    DrawText("1-auto 2-manual",20,20,30,WHITE);
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