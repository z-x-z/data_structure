// #include"GraphAlgorithm.h"
#include<queue>
#include<fstream>
#include<iostream>
using namespace std;
class demo
{
public:
    int val;
    demo()
    :val(0){}
    demo(int _val)
    :val(_val){}
};
/*
    vector<demo> demos(2);
    demos[1].val = 1;
    const demo& a = demos[0];
    cout<<a.val<<endl; // 0
    demos[0] = demos[1];
    cout<<a.val<<endl; // 1
    对一个容器的元素的引用，若容器发生了改变，其会作用于该引用
 */
struct ab
{
    int c;

};

int main()
{
    ifstream ifs("data/dataIn.txt");
    ofstream ofs("data/dataOut.txt");
    if(!ifs)
    {
        cout<<"File open failed!";
        return 0;
    }
    // istream is(ifs); // ERROR, copy constructor is delete!
    // stream.rdbuf(); return the buf that stream use.
    istream is (ifs.rdbuf()); // But we can let them share the same buf
    ostream os (ofs.rdbuf()); // Now is and ifs share the same buf
    while (!is.eof()&&!is.bad())
    {
        string buf;
        getline(is, buf); // 一行一行的写入数据getline(istream, string)
        cout<<buf<<endl;
        os<<buf<<endl;
    }
    ifs.close();
    ofs.close();
}
