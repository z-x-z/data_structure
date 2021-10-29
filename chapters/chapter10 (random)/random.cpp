#include<stdlib.h>
#include<stdio.h>
#include<time.h>


static unsigned long Seed = 1;

#define A 48271L
#define M 2147483647L
#define Q (M / A)
#define R (M % A)


double myRandom1()
{
    Seed = (Seed * A) % M;
    return (double)Seed/M;
}

double myRandom2()
{
    long tmpSeed;
    tmpSeed = A * (Seed % Q) - R * (Seed / Q);
    if(tmpSeed < 0) Seed = tmpSeed + M;
    else Seed = tmpSeed;
    return (double) Seed / M;
}

void initialSeed(unsigned long seed) {Seed = seed;}

void testNormal()
{
    const int num = 10000;
    const int intervalNum = 30;
    int frequencies[intervalNum+1];
    for (int i = 0; i <= intervalNum; i++) frequencies[i] = 0.;
    initialSeed(time(NULL));
    for (int i = 0; i < num; i++)
    {
        double randomVal = myRandom2();
        frequencies[(int) (randomVal*intervalNum)] ++;
    }
    for (int i = 0; i < intervalNum; i++)
    {
        printf("The frequency of interval No.%d is %.4lf\n", i, (double)frequencies[i] / num);
    }
    if(frequencies[intervalNum]) printf("---------------------------\n!!!There is a val that equals 1.0");
    
}
