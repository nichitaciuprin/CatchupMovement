#pragma once

#include <unistd.h>
#include <time.h>
#include "Console.h"

long TimeAll = 0;
long TimeClockOld = 0;
long TimeClockNew = 0;

#define TimeFPS 60
const long TimeFixedDeltaTime = CLOCKS_PER_SEC/TimeFPS;
const float TimeFixedDeltaTimef = 1.0f/TimeFPS;
const double TimeClockPerSecFloat = (double)CLOCKS_PER_SEC;


clock_t TimeNow()
{
    return clock();
}
void TimeWaitSeconds(double seconds)
{
    useconds_t microseconds = seconds*1000000;
    usleep(microseconds);
}
void TimeWaitClocks(clock_t clocks)
{
    double seconds = clocks/TimeClockPerSecFloat;
    TimeWaitSeconds(seconds);
}
void TimeWaitLoop(clock_t oldTime, clock_t newTime, int timeStep)
{
    long calcTime = newTime-oldTime;
    long timeToWait = timeStep-calcTime;
    if (timeToWait > 0)
        TimeWaitClocks(timeToWait);
}
void TimeWaitLoopMark()
{
    TimeAll += TimeFixedDeltaTime;
    TimeClockNew = TimeNow();
    TimeWaitLoop(TimeClockOld,TimeClockNew,TimeFixedDeltaTime);
    TimeClockOld = TimeNow();
}