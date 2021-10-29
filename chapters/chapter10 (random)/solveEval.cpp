//place: JiangXi, ShangRao
//date: 2020/02/27
#include <iostream>
using namespace std;

double solveEval_recur(int N)
{
    if (N == 0)
        return 1;
    double sum = 0.;
    for (int i = 0; i < N; i++)
        sum += solveEval_recur(i);
    return sum * 2. / N + N;
}

double solveEval_linear(int N)
{
    if(N==0) return 1;
    double sumEvals[N];
    sumEvals[0] = 1;
    for (int i = 1; i < N; i++)
    {
        sumEvals[i] = sumEvals[i - 1] + (sumEvals[i - 1] * 2. / i + i);
    }
    return sumEvals[N - 1] * 2. / N + N;
}

void test()
{
    const int N = 10;
    for (int i = 0; i < N; i++)
    {
        printf("i: %d,\tsolveEval_recur(i): %.2lf,\tsolveEval_linear(i):\t%.2lf\n\n",
               i, solveEval_recur(i), solveEval_linear(i));
    }
}

int main()
{
    test();
}