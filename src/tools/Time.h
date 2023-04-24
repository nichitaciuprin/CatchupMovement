#pragma once

#include <time.h>
#include <unistd.h>

long TimeNow()
{
    return clock();
}
void TimeWaitLoop(long oldTime, long newTime, int timeStep)
{
    long calcTime = newTime-oldTime;
    long timeToWait = timeStep-calcTime;
    if (timeToWait > 0)
        usleep(timeToWait);
}