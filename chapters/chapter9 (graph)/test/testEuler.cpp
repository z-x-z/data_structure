#include"../GraphAlgorithm.h"
#include"../GraphTools.h"
using namespace std;
int main()
{
    ifstream ifs("../data/dataTestEuler.txt");
    if(!ifs)
    {
        cout<<"File open fair!"<<endl;
        return 0;
    }
    auto graph= readVectorGraphByStream(ifs);
    dfsSearchEulerPath(graph);

}