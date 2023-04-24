#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

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