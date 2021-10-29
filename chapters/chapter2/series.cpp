#include<iostream>
using namespace std;
int main()
{
    const double k = 0.25;
    double sum = 0;
    double t = 1;
    for (int i = 0; i < 10; i++)
    {
        sum += i*i * t;
        t*= k;
    }
    printf("result is %lf ? %lf", sum, 1. * 20/27);
}