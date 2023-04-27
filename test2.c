#include "tools/MathCatchup.h"
#include <tools/Console.h>

int main(void)
{
    float Apos = 0;
    float Avel = 0;
    float Aacc = 2;
    float Bpos = 7;
    float Bvel = 2;
    float deltaTimeSecods = 1;

    printf("%f %f\n",Apos,Avel);
    for (size_t i = 0; i < 5; i++)
    {
        MathCatchup(&Apos,&Avel,Aacc,Bpos,Bvel,deltaTimeSecods);
        Bpos += Bvel*deltaTimeSecods;
        printf("%f %f\n",Apos,Avel);
        // printf("%f \n",Bpos);
    }

    // Expected result
    //  0.000000 0.000000
    //  1.000000 2.000000
    //  4.000000 4.000000
    //  9.000000 6.000000
    // 14.000000 4.000000
    // 17.000000 2.000000
    return 0;
}