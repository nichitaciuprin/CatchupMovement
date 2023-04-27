#include "tools/MathCatchup.h"
#include <tools/Console.h>

int main(void)
{
    float Apos = 0;
    float Avel = 0;
    float Aacc = 2;
    float Bpos = 50;
    float Bvel = 0;
    float deltaTimeSecods = 1;

    printf("%f %f\n",Apos,Avel);
    for (size_t i = 0; i < 10; i++)
    {
        MathCatchup(&Apos,&Avel,Aacc,Bpos,Bvel,deltaTimeSecods);
        Bpos += Bvel*deltaTimeSecods;
        printf("%f %f\n",Apos,Avel);
    }

    // Expected result
    //  0.000000   0.000000
    //  1.000000   2.000000
    //  4.000000   4.000000
    //  9.000000   6.000000
    // 16.000000   8.000000
    // 25.000000  10.000000
    // 34.000000   8.000000
    // 41.000000   6.000000
    // 46.000000   4.000000
    // 49.000000   2.000000
    // 50.000000   0.000000
    return 0;
}