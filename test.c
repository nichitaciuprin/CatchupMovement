#include <stdbool.h>
#include "tools/Time.h"

int main(void)
{
    while (true)
    {
        printf("HI\n");
        TimeWaitClocks(CLOCKS_PER_SEC);
    }
    return 0;
}