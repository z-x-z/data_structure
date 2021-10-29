#ifndef TOOLS_MYRANDOM_H
#define TOOLS_MYRANDOM_H

#include "tools/DescException.h"

class MyRandom
{
private:
  typedef unsigned long SizeType;
  static const SizeType A = 48271;
  static const SizeType M = 2147483647;
  static const SizeType Q = M / A;
  static const SizeType R = M % A;
  SizeType seed_;
  void generate_nextseed()
  {
    long tmp_seed = A * (seed_ % Q) - R * (seed_ / Q);
    if (tmp_seed < 0)
      seed_ = tmp_seed + M;
    else
      seed_ = tmp_seed;
  }

public:
  inline void srand(SizeType seed)
  {
    seed_ = seed;
    generate_nextseed();
  }

  MyRandom(SizeType init_seed = 1)
  {
    srand(init_seed);
  }

  inline SizeType get_maxnum() const
  {
    return M;
  }

  // [a, b)
  inline SizeType random(SizeType a, SizeType b)
  {
    if (a >= b)
      throw new IllegalOperationException();
    SizeType random_num = seed_ % (b - a) + a;
    generate_nextseed();
    return random_num;
  }

  inline SizeType random()
  {
    return random(0, M);
  }

  inline double random_double(double a, double b)
  {
    if(a>=b)
      throw new IllegalOperationException();
    double random_value = (1.0*seed_/M)*(b-a)+a;
    generate_nextseed();
    return random_value;
  }

  inline double random_01()
  {
    return random_double(0, 1);
  }

};

#endif