#include<vector>
#include<iostream>
#include<fstream>
#define INFINITE INT_MAX
using namespace std;

// typedef int WeightType;
// /// EdgeType
// /*
//     边由指向顶点以及边权重构成。
// */
// typedef pair<int, WeightType> EdgeType;
// typedef vector<EdgeType> Edges;
// /// VectorGraph
// /*
//     vector<pair<int, int> >
//     使用vector实现的邻接表图，其中pair代表的是一条边；
//     VectorGraph的每一项表示一个顶点，其包含一个边集（Edges）；
// */
// typedef vector<Edges> VectorGraph;
class VectorGraph
{
private:
// 对外下标从1开始，实际上对内vector从0开始。
typedef unsigned int VertexType;
typedef int WeightType;
typedef pair<VertexType, WeightType> EdgeType;
typedef vector<EdgeType> EdgesType;
    vector<EdgesType> graph;
    int vertexNum;
    bool isWeighted;
    bool isDirected;
public:
    VectorGraph()
    {}

    VectorGraph(int _vertexNum, bool _isWeighted= false, bool _isDirected= true):
    graph(_vertexNum), vertexNum(_vertexNum), isWeighted(_isWeighted), isDirected(_isDirected)
    {}

    ~VectorGraph()
    {}

    EdgesType& operator[](VertexType vertexId)
    {
        vertexId--;
        return graph[vertexId];
    }

    void insert(VertexType toId, VertexType inId, WeightType weight= 1)
    {
        toId--; inId--;
        // 有向
        if(isDirected)
            graph[toId].push_back(make_pair(inId, weight));
        // 无向
        else
        {
            graph[toId].push_back(make_pair(inId, weight));
            graph[inId].push_back(make_pair(toId, weight));
        }
    }

    static void writeVectorGraphToStream(ostream& os, VectorGraph& vectorGraph)
    {
        for (int i = 1; i <= vectorGraph.vertexNum; i++)
        {
            printf("%3d:  ", i);
            for(auto edge: vectorGraph[i])
            {
                os<<"->"<<setw(3)<<edge.first<<"("<<setw(5)<<edge.second<<")  ";
            }
            os<<endl;
        }
    }

    static void writeVectorGraphToStream(ofstream& ofs, VectorGraph& vectorGraph)
    {
        ostream os(ofs.rdbuf());
        writeVectorGraphToStream(os, vectorGraph);
    }

    friend ostream& operator<<(ostream& os, VectorGraph& vectorGraph)
    {
        writeVectorGraphToStream(os, vectorGraph);
        return os;
    }

    static VectorGraph readVectorGraphByStream(istream& is, bool isWeighted= false, bool isDirected= true)
    {
        int vertexNum;
        is>>vertexNum;
        //下标从1开始
        VectorGraph vectorGraph(vertexNum);
        int edgeNum;
        is>>edgeNum;
        for (int i=1;i<=edgeNum;i++)
        {
            int v, u;
            WeightType weight= 1;
            is>>v>>u;
            if(isWeighted)
                is>>weight;
            // cout<<v<<" "<<u<<" "<<weight<<endl;
            if(isDirected)
                vectorGraph[v].push_back(make_pair(u, weight));
            else
                {
                    vectorGraph[v].push_back(make_pair(u, weight));
                    vectorGraph[u].push_back(make_pair(v, weight));
                }
        }
        return vectorGraph;
    }

    static VectorGraph readVectorGraphByStream(ifstream& ifs, bool isWeighted= false, bool isDirected= true)
    {
        istream is(ifs.rdbuf());
        return readVectorGraphByStream(is, isWeighted, isDirected);
    }

    friend istream& operator>>(istream& is, VectorGraph& vectorGraph)
    {
        return is;
    }

};

