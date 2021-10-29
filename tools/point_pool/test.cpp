#include "tools/point_pool/point_pool.h"
#include "ds/LinearList/link_list.h"
#include <iostream>
#include <vector>
#include "tools/MyRandom.h"

using namespace std;

void test_pointpool()
{
  unsigned int increment = 10;
  PointPool<string> pool(increment);
  vector<string *> vsp;
  LinkList<string *> list;
  MyRandom my_random(5);
  const int total_operations = 100;

  for (int i = 0; i < total_operations; i++)
  {
    if (my_random.random_01() > 0.4)
    {
      string *p_s = pool.release_point();
      if(p_s==nullptr)
      {
        cout<<"nullptr"<<endl;
      }
      list.push_element(p_s);
      printf("Release point.\n");
    }
    else
    {
      if (list.size() > 0)
      {
        pool.recycle_point(list.get_element(list.size() - 1));
        list.remove_element(list.size() - 1);
        printf("Recycle point.\n");
      }
    }
    if (i % 5 == 0)
    {
      printf("Pool capacity: %d, size: %d\n", pool.capacity(), pool.size());
      printf("list size: %d\n\n", list.size());
    }
  }
}

int main()
{
  test_pointpool();
  return 0;
}