#pragma once

#include <stdio.h>

void ConsoleWriteLineStr(const char * value)
{
    printf("%s\n",value);
}
void ConsoleWriteLineInt(const int value)
{
    printf("%i\n",value);
}
void ConsoleWriteLineFloat(const float value)
{
    printf("%f\n",value);
}