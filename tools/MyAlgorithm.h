#ifndef TOOLS_MYALGORITHM_H
#define TOOLS_MYALGORITHM_H
#include "tools/MyRandom.h"
#include <ctime>
#include <vector>
class MyAlgorithm
{
private:
  static MyRandom * random_generator;

public:
  template <typename T>
  static inline void swap(T &a, T &b)
  {
    T tmp = a;
    a = b;
    b = tmp;
  }

  template <typename T>
  static void shuffle_local(std::vector<T> &arr)
  {
    if (random_generator == nullptr)
      random_generator = new MyRandom(time(nullptr));
    for (int i = arr.size() - 1; i >= 0; i--)
      swap(arr[i], arr[random_generator->random(0, i+1)]);
  }

  template <typename T>
  static inline std::vector<T> shuffle_remote(const std::vector<T> &arr)
  {
    if (random_generator == nullptr)
      random_generator = new MyRandom(time(nullptr));
    std::vector<T> result(arr.size());
    copy(arr.begin(), arr.end(), result.begin());
    shuffle_local(result);
    return result;
  }
};

// 类内静态成员初始化方式：
// 在类的实现文件中进行初始化
MyRandom* MyAlgorithm::random_generator (nullptr);
#endif
