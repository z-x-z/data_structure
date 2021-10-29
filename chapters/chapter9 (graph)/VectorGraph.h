#include<vector>
#define INFINITE INT_MAX
using namespace std;


typedef int WeightType;
/// EdgeType
/*
    边由指向顶点以及边权重构成。
*/
typedef pair<int, WeightType> EdgeType;
typedef vector<EdgeType> Edges;
/// VectorGraph
/*
    vector<pair<int, int> >
    使用vector实现的邻接表图，其中pair代表的是一条边；
    VectorGraph的每一项表示一个顶点，其包含一个边集（Edges）；
*/
typedef vector<Edges> VectorGraph;
