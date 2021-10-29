#include"../GraphTools.h"

int main()
{
    ifstream ifs("../data/data.txt");
    if(!ifs)
    {
        cout<<"File open fair";
        return 0;
    }
    VectorGraph graph = readVectorGraphByStream(ifs, true);
    cout<<graph.size()<<endl;
    writeVectorGraphToStream(cout, graph);

}