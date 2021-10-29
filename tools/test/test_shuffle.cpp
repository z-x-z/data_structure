#include"tools/MyAlgorithm.h"
#include<iostream>
#include<vector>
using namespace std;
int main()
{
  vector<int> nums {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const int max_times = 20;

  for (int i = 0; i < max_times; i++)
  {
      for (auto t: MyAlgorithm::shuffle_remote(nums))
    {
      cout<<t<<" ";
    }
    cout<<endl;
  }


  return 0;
}