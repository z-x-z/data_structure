#include<iostream>
using namespace std;
class intCell
{
private:
    int* val;
public:
    intCell(int initVal= 0): val(new int(initVal)){}
    // intCell(const intCell& cell): val(new int(cell.get())){}
    /* const intCell& operator=(const intCell& cell)
    {
        if(this!=&cell)
        {
            *val = cell.get();
        }
        return *this;
    } */
    ~intCell()
    {
        delete val;
    }
    int get() const // getter
    {
        return *val;
    }
    void set(int x)
    {
        *val = x;
    }
};

int main()
{
    intCell a(3);
    intCell b = a; // call default copy constructor
    intCell c;
    c= b; // call default operator = 
    a.set(5);
    // lack deconstructor
    // 5 5 5
    // 5 3 3
    cout<<a.get()<<endl<<b.get()<<endl<<c.get()<<endl;
}