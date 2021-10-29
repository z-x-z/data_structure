#ifndef GRAPH_ALGORITHM_H
#define GRAPH_ALGORITHM_H

#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_set>
#include<set>
#include "VectorGraph.h"
#include "GraphTools.h"

#include "../chapter6 (heap)/BinaryHeap.h"
#include "../chapter8 (disjoint set)/unionFindSet.h"

/// 拓扑排序算法
void topologySort(const VectorGraph &graph)
{
    int vertexNum = graph.size();
    std::queue<int> zero_indegree_v;
    vector<int> in_degrees(vertexNum, 0);
    // 遍历图，确认每个点的入度
    for (auto &edges : graph)
        for (auto &edge : edges)
            in_degrees[edge.first]++;
    // 存储拓扑排序的序列
    vector<int> indice(vertexNum);
    for (int i = 0; i < vertexNum; i++)
        if (in_degrees[i] == 0)
            zero_indegree_v.push(i);
    for (int i = 0; i < vertexNum; i++)
    {
        if (zero_indegree_v.empty())
        {
            cout << "The graph haven't a topology sort(circular)!";
            return;
        }
        int index = zero_indegree_v.front();
        indice[i] = index;
        zero_indegree_v.pop();
        // 遍历该节点的所有邻接点，并使其入度减一，
        // 若减一后入度为0，则入队列。
        for (auto &edge : graph[index])
        {
            int j = edge.first;
            in_degrees[j]--;
            if (in_degrees[j] == 0)
                zero_indegree_v.push(j);
        }
    }
    // 输出最后的序列
    for (int i = 0; i < vertexNum; i++)
    {
        std::cout << indice[i] << " ";
    }
}

/// BFS算法
/*
    单源无权图的最短路径算法
*/
void minDistanceSingalSourceUnWeighted(const VectorGraph &graph,
int startVertex)
{
    int vertexNum = graph.size();
    vector<int> pv(vertexNum + 1);
    vector<int> distances(vertexNum + 1, INFINITE);
    distances[startVertex] = 0;
    std::queue<int> vertexQueue;
    vertexQueue.push(startVertex);
    while (!vertexQueue.empty())
    {
        int v = vertexQueue.front();
        vertexQueue.pop();
        for (auto &edge : graph[v])
        {
            int i = edge.first;
            // v -> i邻接，s -> i距离为INFINITE
            if (distances[i] == INFINITE)
            {
                distances[i] = distances[v] + 1;
                pv[i] = v;
                vertexQueue.push(i);
            }
        }
    }
    // 打印最终结果
    printf("Start vertex: %d\n", startVertex);
    for (int i = 1; i <= vertexNum; i++)
    {
        if (distances[i] == INFINITE)
        {
            printf("Dis(%2d)= INF", i);
            continue;
        }
        else
            printf("Dis(%2d)=%3d: ", i, distances[i]);
        // 打印路径
        stack<int> pVertex;
        int t = i;
        while (t != startVertex)
        {
            pVertex.push(t);
            t = pv[t];
        }
        printf("%2d", startVertex);
        while (!pVertex.empty())
        {
            printf(" -> %2d", pVertex.top());
            pVertex.pop();
        } //
        printf("\n");
    } //
}

void minDistanceSingalSourceUnWeightedAllPath(const VectorGraph& graph,
int startVertex, int endVertex)
{
    int vertexNum = graph.size();
    vector<vector<int> > pvs(vertexNum + 1);
    vector<int> visitedLevel(vertexNum + 1, INFINITE);
    int level = 1;
    visitedLevel[startVertex] = level;
    std::queue<int> vertexQueue;
    vertexQueue.push(startVertex);
    while (!vertexQueue.empty())
    {
        int levelVertexNum = vertexQueue.size();
        for (int i = 0; i < levelVertexNum; i++)
        {
            int vertex = vertexQueue.front();
            vertexQueue.pop();
            if(vertex!=endVertex)
            {
                for (auto edge: graph[vertex])
                {
                    int v = edge.first;
                    // 只有visitedLevel小于等于当前level的节点才能访问
                    if(visitedLevel[v]>level)
                    {
                        if(visitedLevel[v]!=level+1)
                            vertexQueue.push(v);
                        visitedLevel[v] = level+1;
                        pvs[v].push_back(vertex);
                        // nvs[vertex].push_back(vertex);
                    }
                }
            }
        }
    }
}

/// dijkstra算法
/*
    单源有权图的最短路径算法
*/
void dijkstra(const VectorGraph &graph, int startVertex)
{
    int vertexNum = graph.size();
    vector<int> pv(vertexNum + 1, startVertex);
    vector<int> distances(vertexNum + 1, INFINITE);
    vector<bool> know(vertexNum + 1, false);
    // 初始化距离
    for (auto &edge : graph[startVertex])
        distances[edge.first] = edge.second;
    distances[startVertex] = 0;
    know[startVertex] = true;
    while (true)
    {
        // 寻找还未访问的节点中，距离最小的
        int minV = -1;
        int minDis = INT_MAX - 1;
        for (int i = 1; i <= vertexNum; i++)
        {
            if (!know[i] && distances[i] < minDis)
            {
                minDis = distances[i];
                minV = i;
            }
        }
        know[minV] = true;
        if (minV == -1)
            break; //
        // 更新距离
        for (auto &edge : graph[minV])
        {
            int i = edge.first;
            if (!know[i] &&
                (distances[i] == INFINITE || distances[minV] + edge.second < distances[i]))
            {
                distances[i] = distances[minV] + edge.second;
                pv[i] = minV;
            }
        } //
    }
    // 打印最终结果
    printf("Start vertex: %d\n", startVertex);
    for (int i = 1; i <= vertexNum; i++)
    {
        if (distances[i] == INFINITE)
        {
            printf("Dis(%2d)= INF", i);
            continue;
        }
        else
            printf("Dis(%2d)=%3d: ", i, distances[i]);
        // 打印路径
        std::stack<int> pVertex;
        int t = i;
        while (t != startVertex)
        {
            pVertex.push(t);
            t = pv[t];
        }
        printf("%2d", startVertex);
        while (!pVertex.empty())
        {
            printf(" -> %2d", pVertex.top());
            pVertex.pop();
        } //
        printf("\n");
    }
}

//// 有权无向图最小生成树算法
/*
    生成树：由一个图中所有的点与部分的边组成的一个图，该图保证所有节点联通，同时没有圈
    最小生成树：所有生成树中边权重之和最小的一颗生成树
    prime算法
    kruskal算法
*/

/// prime算法
/*
    算法与dijkstra算法基本一致
*/
void prime(const VectorGraph &graph)
{
    int vertexNum = graph.size() - 1;
    vector<bool> know(vertexNum + 1, false);
    int startVertex = 1;
    vector<int> pv(vertexNum + 1, startVertex);
    vector<int> distances(vertexNum + 1, INFINITE);
    for (auto &edge : graph[startVertex])
        distances[edge.first] = edge.second;
    distances[startVertex] = 0;
    know[startVertex] = true;
    // 循环vertexNum-1次以访问所有的点
    for (int i = 0; i < vertexNum - 1; i++)
    {
        // 寻找还未访问的节点中，距离最小的
        int minV = -1;
        int minDis = INT_MAX - 1;
        for (int i = 1; i <= vertexNum; i++)
        {
            if (!know[i] && distances[i] < minDis)
            {
                minDis = distances[i];
                minV = i;
            }
        }
        know[minV] = true;
        if (minV == -1)
        {
            printf("The graph is circular!\n");
            return;
        } //
        // 更新距离
        for (auto &edge : graph[minV])
        {
            int i = edge.first;
            // 此处与dijkstra算法略有不同
            if (!know[i] &&
                (distances[i] == INFINITE || edge.second < distances[i]))
            {
                distances[i] = edge.second;
                pv[i] = minV;
            }
        } //
    }
    // 打印最小生成树的组成边
    printf("The minimal spining tree is consisted of theres edge:\n");
    printf("  v1   v2 weight\n");
    // 最小生成树一共由vertexNum-1条边组成
    int totalWeight = 0;
    for (int i = startVertex + 1; i <= vertexNum; i++)
    {
        printf("%4d %4d %6d\n", pv[i], i, distances[i]);
        totalWeight += distances[i];
    }
    printf("The total weight is %d\n", totalWeight);
}

/// kruskal算法
/*
    使用并查集实现。
*/
void kruskal(const VectorGraph &graph)
{
    struct EdgeNode
    {
        int v, u;
        int weight;
        EdgeNode() {}
        EdgeNode(int _v, int _u, int _weight)
            : v(_v), u(_u), weight(_weight) {}
        bool operator<(const EdgeNode &e)
        {
            return weight < e.weight;
        }
    };

    vector<EdgeNode> edges;
    int vertexNum = graph.size() - 1; // 下标从1开始
    for (int i = 1; i <= vertexNum; i++)
    {
        for (auto e : graph[i])
        {
            // 去除无向图中的重复边
            if (e.first >= i)
                edges.push_back(EdgeNode(i, e.first, e.second));
        }
    }
    unionFindSet ufSet(vertexNum);
    BinaryHeap<EdgeNode> edgeHeap(edges);
    int exceptedEdgeNum = 0;
    vector<EdgeNode> selectedEdges(vertexNum - 1);
    // 期待的边数为vertexNum-1
    while (!edgeHeap.empty() && exceptedEdgeNum < vertexNum - 1)
    {
        // 此处千万不要用引用类型!!
        EdgeNode edge = edgeHeap.getMin();
        edgeHeap.deleteMin();
        int uSet = ufSet.Find(edge.u);
        int vSet = ufSet.Find(edge.v);
        if (uSet != vSet)
        {
            selectedEdges[exceptedEdgeNum] = edge;
            ufSet.Union(uSet, vSet);
            exceptedEdgeNum++;
        }
    }

    if (exceptedEdgeNum < vertexNum - 1)
        printf("The graph is not connected!");
    else
    {
        printf("The minimal spining tree is consisted of theres edge:\n");
        printf("  v1   v2 weight\n");
        int totalWeight = 0;
        for (const auto &edge : selectedEdges)
        {
            printf("%4d %4d %6d\n", edge.u, edge.v, edge.weight);
            totalWeight += edge.weight;
        }
        printf("The total weight is %d\n", totalWeight);
    }
}

//// 欧拉回路与欧拉路径问题
/*
    欧拉回路：存在一条路径使得经过图的所有边且终止与起始点。
    欧拉路径：存在一条路径使得经过图的所有边且终止与非起始点。
*/

/// 判断有向图的欧拉回路是否存在
/*
    所有顶点的出度等于入度，
    可以以任意点起始。
*/
bool isEulerCircuitExited(const VectorGraph &graph)
{
    int vertexNum = graph.size()-1;
    vector<int> indegrees(vertexNum+1, 0);
    vector<int> outdegrees(vertexNum+1, 0);
    for (int i = 1; i <= vertexNum; i++)
    {
        const auto &edges = graph[i];
        outdegrees[i] = edges.size();
        for (const auto &edge : edges)
        {
            indegrees[edge.first]++;
        }
    }
    for (int i = 1; i <= vertexNum; i++)
        if (indegrees[i] != outdegrees[i])
            return false;

    return true;
}
/// 判断有向图的欧拉路径是否存在
/*
    有且仅有两个点的出入度不相等，
    并且其中一者的出度比入度大1（起始点），
    另一者入度比出度大1（终止点）。
*/
bool isEulerPathExited(const VectorGraph &graph, int &startVertex)
{
    int vertexNum = graph.size();
    vector<int> indegrees(vertexNum, 0);
    vector<int> outdegrees(vertexNum, 0);
    for (int i = 1; i <= vertexNum-1; i++)
    {
        const auto &edges = graph[i];
        outdegrees[i] = edges.size();
        for (const auto &edge : edges)
        {
            indegrees[edge.first]++;
        }
    }
    bool pDiff = false, nDiff = false;
    for (int i = 1; i <= vertexNum; i++)
        switch (indegrees[i] - outdegrees[i])
        {
        case 1:
            if (pDiff)
                return false;
            pDiff = true;
            break;
        // outdegree > indegree
        case -1:
            if (nDiff)
                return false;
            nDiff = true;
            startVertex = i;
            break;
        case 0:
            // do noting
            break;
        default:
            return false;
            break;
        }
    return pDiff && nDiff;
}

void dfsSearchEulerCircuitHelper(const VectorGraph &graph, const int startVertex, vector<int> &vertexVector,
                                 set<pair<int, int> > &edgeSet)
{
    for (auto &edge : graph[startVertex])
    {
        auto pair = make_pair(startVertex, edge.first);
        if (!edgeSet.count(pair))
        {
            edgeSet.insert(pair);
            dfsSearchEulerCircuitHelper(graph, edge.first, vertexVector, edgeSet);
        }
    }
    vertexVector.push_back(startVertex);
}
/// 欧拉回路 DFS搜索方法
void dfsSearchEulerCircuit(const VectorGraph &graph)
{
    if (!isEulerCircuitExited(graph))
    {
        cout<<"The graph has no euler circuit!";
        return;
    }

    vector<int> vertexVector;
    // unordered_set<pair<int, int> > edgeSet;
    // unordered_set不能直接使用pair作为键值，需要自己传入hash函数
    set<pair<int, int> > edgeSet;

    dfsSearchEulerCircuitHelper(graph, 1, vertexVector, edgeSet);
    for (int i = vertexVector.size()-1; i >= 0; i--)
    {
        cout<<vertexVector[i]<<" ";
    }
}

void dfsSearchEulerPath(const VectorGraph& graph)
{
    int startVertex;
    if(!isEulerPathExited(graph, startVertex))
    {
        cout<<"The graph has no euler path!";
        return;
    }
    vector<int> vertexVector;
    set<pair<int, int> > edgeSet;
    dfsSearchEulerCircuitHelper(graph, startVertex, vertexVector, edgeSet);
    for (int i = vertexVector.size()-1; i >= 0; i--)
    {
        cout<<vertexVector[i]<<" ";
    }
}
#endif