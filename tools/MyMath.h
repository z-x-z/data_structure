#ifndef TOOLS_MYMATH_H
#define TOOLS_MYMATH_H
class MyMath
{
  // x^n
  private:
  static double fastPowRecur(double x, unsigned int N)
  {
      if(N==0) return 1;
      if(N%2==0) return fastPowRecur(x*x, N/2);
      else return fastPowRecur(x*x, N/2) * x;
  }
  public:
  inline static double fast_pow(double x, int N)
  {
    if(N<0)
      return 1./fastPowRecur(x, -N);
    else
      return fastPowRecur(x, N);
  }

  
}


#endif
