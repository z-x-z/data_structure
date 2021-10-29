#include "tools/MyRandom.h"
#include<iostream>
#include<ctime>

using namespace std;

int main()
{
  MyRandom my_ramdom(5);
  const int test_count = 50;
  for (int i = 0; i < test_count; i++)
  {
    cout<<my_ramdom.random(0, 100)<<"\t"<<my_ramdom.random_double(-10, -5)<<endl;
  }

  return 0;
}