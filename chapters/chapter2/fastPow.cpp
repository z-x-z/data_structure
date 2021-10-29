#include<iostream>
#include<ctime>
#include<cmath>

using namespace std;

// recursive method implement x ^ N (N>=0)
double fastPowRecur(double x, unsigned int N)
{
    if(N==0) return 1;
    if(N%2==0) return fastPowRecur(x*x, N/2);
    else return fastPowRecur(x*x, N/2) * x;
}

// Iterative method implement  x^N (N>=0)
double fastPowIter(double x, unsigned int N)
{
    double result = 1;
    double pow = x;
    const unsigned int lowBitMask = 0x00000001;
    while(N!=0)
    {
        // 通过低位掩码获取最低位
        if(N&lowBitMask) result*=pow; // 或者 if(n%2)
        // 由于n>0所以默认为逻辑右移动
        N >>= 1; // n/=2
        pow*=pow;//pow = pow^2
    }
    return result;
}

double fastPow(double x, int N)
{
    return 0;
}

int main()
{
    int i = INT_MIN;
    int j = -i;
    int k = INT_MAX;
    unsigned int ui = i;
    unsigned int uj = -i;
    unsigned int uk = k;
    cout<<ui<<endl;
    cout<<uj<<endl;
    cout<<uk<<endl;
}