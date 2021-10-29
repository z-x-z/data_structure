#include <iostream>
#include <cstring>
using namespace std;

int class_count = 0;
class DemoClass
{
public:
  char *name;
  DemoClass()
  {
    name = new char[10];
    name[0] = 'c';
    name[1] = 'l';
    name[2] = '0' + class_count;
    name[3] = 0;
    cout << name << " is constructed!" << endl;
    class_count++;
  }
  ~DemoClass()
  {
    cout << name << " is deconstructed!" << endl;
    delete name;
  }
};
typedef DemoClass *PtrToDemoClass;

struct DemoStruct
{
  char *name;
  DemoStruct()
  {
    name = "DemoStruct ";
    cout << name << " is constructed!" << endl;
  }
};
int main()
{
  const int maxnum = 10;
  DemoClass *democlasses = new DemoClass[maxnum];
  DemoStruct *demostruct = new DemoStruct[maxnum];
  for (int i = 0; i < maxnum; i++)
  {
    cout << democlasses[i].name << " " << demostruct[i].name << endl;
  }
  PtrToDemoClass *democlass_points = new PtrToDemoClass[maxnum];
  for (int i = 0; i < maxnum; i++)
  {
    democlass_points[i] = &democlasses[i];
  }
  for (int i = 0; i < maxnum; i++)
  {
    cout<<"Access point "<<i<<", point class name is "<<democlass_points[i]->name<<endl;
  }

  delete[] democlasses;
  delete[] demostruct;
  return 0;
}
