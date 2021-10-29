#ifndef GRAPH_TOOLS_H
#define GRAPH_TOOLS_H

#include"VectorGraph.h"
#include<iostream>
#include<fstream>
using namespace std;

VectorGraph readVectorGraphByStream(istream& is, bool isWeighted= false, bool isDirected= true)
{
    int vertexNum;
    is>>vertexNum;
    //下标从1开始
    VectorGraph vectorGraph(vertexNum+1, Edges());
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

VectorGraph readVectorGraphByStream(ifstream& ifs, bool isWeighted= false, bool isDirected= true)
{
    istream is(ifs.rdbuf());
    return readVectorGraphByStream(is, isWeighted, isDirected);
}

void writeVectorGraphToStream(ostream& os, const VectorGraph& graph)
{
    int vertexNum = graph.size()-1; // 下标从1(1~vertexNum)
    for (int i = 1; i <= vertexNum; i++)
    {
        printf("%3d:  ", i);
        for(auto edge: graph[i])
        {
            os<<"->"<<setw(3)<<edge.first<<"("<<setw(5)<<edge.second<<")  ";
        }
        os<<endl;
    }
}

void writeVectorGraphToStream(ofstream& ofs, const VectorGraph& graph)
{
    ostream os(ofs.rdbuf());
    return writeVectorGraphToStream(os, graph);
}
#endif