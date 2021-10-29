#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

/// characteristic Equation
/*
    Second factor recursive sequence solution:
    x(n+1) = p*x(n) + q*x(n-1)
    And given number:
    x(1) = x1, x(2) = x2
    We can get the general formula:
    x(n) = k1 * a^(n) + k2 * b^(n)
    return vector<double>{k1, a, k2, b}
*/
vector<double> characteristicEquation(double p, double q, double x1, double x2)
{
    vector<double> ans (4);
    double delta = p*p+4*q;
    if(delta<0)
    {
        cerr<<"The delta should be positive!"<<endl;;
        return ans;
    }
    double sqrtDelta = sqrt(delta);
    double a, b, k1, k2;
    ans[1] = a = (p+sqrtDelta)/2;
    ans[3] =  b = (p-sqrtDelta)/2;
    ans[0] = k1 = (x2- b*x1)/(a*(a-b));
    ans[2] = k2 = (x2- a*x1)/(b*(b-a));
    printf("The general formula is:\nx(n) = %.3lf * %.3lf^(n) + %.3lf * %.3lf^(n)\n",
    k1, a, k2, b);
    return ans;
}

inline double recursiveSequence(const vector<double>& factors, const int n)
{
    return factors[0]*pow(factors[1], n)+factors[2]*pow(factors[3], n);
}
int main()
{
    vector<double> factors;
    factors = characteristicEquation(1, 2, 1, 1);
    const int maxN = 30;
    for (int i = 1; i <= maxN; i++)
    {
        printf("x(%d) = %.3lf\n", i, (recursiveSequence(factors, i)));
    }
}