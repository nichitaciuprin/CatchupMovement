#pragma once

#include <unistd.h>
#include <time.h>

clock_t TimeAll = 0;
clock_t TimeClockOld = 0;
clock_t TimeClockNew = 0;

#define TimeFPS 60
const clock_t TimeFixedDeltaTimeClock = CLOCKS_PER_SEC/TimeFPS;
const float TimeFixedDeltaTimeFloat = 1.0f/TimeFPS;
const double TimeClockPerSecFloat = CLOCKS_PER_SEC;

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
    TimeAll += TimeFixedDeltaTimeClock;
    TimeClockNew = TimeNow();
    TimeWaitLoop(TimeClockOld,TimeClockNew,TimeFixedDeltaTimeClock);
    TimeClockOld = TimeNow();
}