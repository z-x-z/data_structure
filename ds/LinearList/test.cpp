#include <bits/stdc++.h>
#include "ds/LinearList/seq_list.h"
#include "ds/LinearList/link_list.h"
#include "ds/LinearList/double_circular_link_list.h"
using namespace std;

int main()
{
  DoubleCircularLinkList<int> list = {1, 2, 3};
  cout<<list.to_string()<<endl;
  list.set_element(2, 5);
  list.insert_element(1, -1);
  cout<<list.to_string()<<endl;
  list.push_element(2);
  cout<<list.to_string()<<endl;
  list.remove_element(list.size()-2);
  list.pushfront_element(-2);
  cout<<list.to_string()<<endl;
  DoubleCircularLinkList<string> str_list = {"123", "456", "78"};
  cout<<str_list.to_string()<<endl;
  return 0;
}