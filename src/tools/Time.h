#pragma once

#include <unistd.h>
#include <time.h>

long TimeAll = 0;
long TimeClockOld = 0;
long TimeClockNew = 0;

#define TimeFPS 60
const long TimeFixedDeltaTime = CLOCKS_PER_SEC/TimeFPS;
const float TimeFixedDeltaTimef = 1.0f/TimeFPS;

void TimeWaitLoop(long oldTime, long newTime, int timeStep)
{
    long calcTime = newTime-oldTime;
    long timeToWait = timeStep-calcTime;
    if (timeToWait > 0)
        usleep(timeToWait);
}
void TimeWaitLoopMark()
{
    TimeAll += TimeFixedDeltaTime;
    TimeClockNew = clock();
    TimeWaitLoop(TimeClockOld,TimeClockNew,TimeFixedDeltaTime);
    TimeClockOld = clock();
}