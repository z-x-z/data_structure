#include<iostream>
#include"Matrix.h"
using namespace std;

class A
{
public:
    string name;
    A(string _name):
    name(_name)
    {
        cout<<name<<" construct1"<<endl;
    }
    // A(A& a):
    // name(a.name)
    // {
    //     cout<<name<<" construct2"<<endl;
    // }
    A& operator=(A& a)
    {
        name = a.name;
        cout<<name<<" assign1"<<endl;
    }
    // A& operator=(A& a)
    // {
    //     name = a.name;
    //     cout<<name<<" assign"<<endl;
    // }
};
int main()
{
    Matrix<double> m = Matrix<double>::eye(3);
    m[0][1] = m[0][2] = m[1][0] = 1;
    const int num= 50;
    for (int i = 1; i <= num; i++)
    {
        cout<<i<<endl;
        cout<<(m^i);
    }

    return 0;
}