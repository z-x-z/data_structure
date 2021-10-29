#include"../VectorGraph copy.h"
#include<iostream>
using namespace std;

int main()
{
    ifstream ifs("../data/data.txt");
    if(!ifs)
    {
        cout<<"File open fail"<<endl;
        return 0;
    }
    VectorGraph graph = VectorGraph::readVectorGraphByStream(ifs, true);
    cout<<graph;
}