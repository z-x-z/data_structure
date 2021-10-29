#ifndef Matrix_GRAPH_H
#define Matrix_GRAPH_H

#define INFINITE INT_MAX
// 1<<31 -> INT_MIN
// (1<<31)-1 -> INT_MAX
#include<iostream>
#include<fstream>
#include<queue>
#include<stack>

class MatrixGraph
{
private:
    int vertexNum;
    // 默认为有向无权图
    bool isDirected; // true
    bool isWeighted; // false
    int ** weights;
    void initWeights(int** _weights= nullptr)
    {
        weights = new int*[vertexNum+1];
        if(_weights==nullptr)
        {
            for (int i = 1; i <= vertexNum; i++)
            {
                weights[i] = new int[vertexNum+1];
                for (int j = 1; j <= vertexNum; j++)
                    weights[i][j] = INFINITE;
            }
        }
        else 
        {
            for (int i = 1; i <= vertexNum; i++)
            {
                weights[i] = new int[vertexNum+1];
                for (int j = 1; j <= vertexNum; j++)
                    weights[i][j] = _weights[i][j];
            }
        }
    }
    void deleteWeights()
    {
        for (int i = 1; i <= vertexNum; i++)
            delete[] weights[i];
        delete[] weights;
        vertexNum = 0;
    }
public:
    explicit MatrixGraph(const MatrixGraph& rhs)
    : vertexNum(rhs.vertexNum), isDirected(rhs.isDirected), isWeighted(rhs.isWeighted)
    {
        initWeights(rhs.weights);
    }
    explicit MatrixGraph(const int _vertexNum, bool _isWeighted= false, bool _isDirected= true)
    : vertexNum(_vertexNum), isDirected(_isDirected), isWeighted(_isWeighted)
    {
        initWeights();
    }
    // 流对象不能通过拷贝赋值， 必须通过引用
    explicit MatrixGraph(std::ifstream& f, bool _isWeighted= false, bool _isDirected= true )
    : isDirected(_isDirected), isWeighted(_isWeighted)
    {
        f>>vertexNum;
        initWeights();

        int edgeNum;
        f>>edgeNum;
        for (int i = 0; i < edgeNum; i++)
        {
            int v1, v2;
            int weight = 1;
            f>>v1>>v2;
            // 有权图
            if(isWeighted)
                f>>weight;
            // 有向图
            if(isDirected)
                weights[v1][v2] = weight;
            else
                weights[v1][v2] = weights[v2][v1] = weight;
        }   
    }

    const MatrixGraph& operator =(const MatrixGraph& rhs)
    {
        if(this!=&rhs)
        {
            if(vertexNum==rhs.vertexNum)
                for(int i=1;i<=vertexNum;i++)
                    for (int j = 1; j <= vertexNum; j++)
                        weights[i][j] = rhs.weights[i][j];
            else
            {
                deleteWeights();
                vertexNum = rhs.vertexNum;
                initWeights();
            }
            isDirected = rhs.isDirected;
            isWeighted = rhs.isWeighted;
        }
        return *this;
    }

    ~MatrixGraph()
    {
        deleteWeights();
    }

    int getVertexNum()
    {
        return vertexNum;
    }

    int* operator[](int i)
    {
        return weights[i];
    }

    void print()
    {
        for (int i = 1; i <= vertexNum; i++)
        {
            for (int j = 1; j <= vertexNum; j++)
            {
                if(weights[i][j]!=INFINITE)
                    printf("%5d ", weights[i][j]);
                else 
                    printf("  INF ");
            }
            printf("\n");
        }
    }

    void printFormat()
    {
        printf("    D2");
        for (int i = 1; i <= vertexNum; i++)
            printf("%4d: ", i);
        printf("\n  D1");
        for (int i = 1; i <= vertexNum; i++)
        {
            printf("\n%3d:  ", i);
            int t = isDirected ?  vertexNum : i;
            for (int j = 1; j <= t; j++)
            {
                if(weights[i][j]!=INFINITE)
                    printf("%5d ", weights[i][j]);
                else
                    printf("  INF ");
            }
            printf("\n");
        }
    }

    /**
     * 拓扑排序
     *  定义：使得最终的节点序列始终满足后面节点没有指向前者节点的边
     *  实现：
     *  1.首先访问初始状态下的图，获得哪些入度点为0的节点的队列。
     *  2.依次访问该队列的头节点，并将其从队列中删除至最终的序列中。
     *  3.访问该头结点所有的邻接点，并使该节点的入度减一，若减一后的入度为0，则将该节点入队列。
     *  4.重复2-3操作vertexNum次，若循环结束前队列已为0，则说明该图存在圈（circle）
    */
    void topologySort()
    {
        std::queue<int> indegreeZero;
        int indegrees[vertexNum];
        for (size_t i = 1; i <= vertexNum; i++)
        {
            indegrees[i] = 0;
            for (int j = 1; j <= vertexNum; j++)
                if(weights[j][i]!=INFINITE)
                    indegrees[i]++;
            if(indegrees[i]==0)
                indegreeZero.push(i);
        }
        int indice[vertexNum];
        for (int i = 0; i < vertexNum; i++)
        {
            if(indegreeZero.empty())
            {
                std::cout<<"The graph haven't a topology sort(circular)!";
                return ;
            }
            int index = indegreeZero.front();
            indice[i] = index;
            indegreeZero.pop();
            for (int j = 1; j <= vertexNum; j++)
            {
                if(weights[index][j]!=INFINITE)
                {
                    indegrees[j]--;
                    if(indegrees[j]==0)
                        indegreeZero.push(j);
                }
            }
        }
        // 输出最后的序列
        for (int i = 0; i < vertexNum; i++)
        {
            std::cout<<indice[i]<<" ";
        }
    }

    void minDistanceSingalSourceUnWeighted(int startVertex)
    {
        int pv[vertexNum+1];
        int distances[vertexNum+1];
        for (int i = 1; i <= vertexNum; i++)
            distances[i] = INFINITE;
        distances[startVertex] = 0;
        std::queue<int> vertexQueue;
        vertexQueue.push(startVertex);
        while (!vertexQueue.empty())
        {
            int v = vertexQueue.front();
            vertexQueue.pop();
            for (int i = 1; i <= vertexNum; i++)
            {
                // v -> i邻接，s -> i距离为INFINITE
                if(weights[v][i]!=INFINITE&&distances[i]==INFINITE)
                {
                    distances[i] = distances[v]+1;
                    pv[i] = v;
                    vertexQueue.push(i);
                }
            }
        }
        // 打印最终结果
        printf("Start vertex: %d\n", startVertex);
        for (int i = 1; i <= vertexNum; i++)
        {
            if(distances[i]==INFINITE)
            {
                printf("Dis(%2d)= INF", i);
                continue;
            }
            else 
                printf("Dis(%2d)=%3d: ",i, distances[i]);
            // 打印路径
            std::stack<int> pVertex;
            int t = i;
            while (t!=startVertex)
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

    void dijkstra(int startVertex)
    {
        int pv[vertexNum+1];
        int distances[vertexNum+1];
        bool know[vertexNum+1];
        for (int i = 1; i <= vertexNum; i++)
        {
            distances[i] = weights[startVertex][i];
            know[i] = false;
            pv[i] = startVertex;
        }
        distances[startVertex] = 0;
        know[startVertex] = true;
        while (true)
        {
            // 寻找还未访问的节点中，距离最小的
            int minV = -1;
            int minDis = INT_MAX-1;
            for (int i = 1; i <= vertexNum; i++)
            {
                if(!know[i]&&distances[i]<minDis)
                {
                    minDis = distances[i];
                    minV = i;
                }
            }
            know[minV] = true;
            if(minV==-1)
                break; //
            // 更新距离
            for (int i = 1; i <= vertexNum; i++)
            {
                if(!know[i]&&weights[minV][i]!=INFINITE)
                {
                    if(distances[i]==INFINITE||
                    distances[minV]+weights[minV][i]<distances[i])
                    {
                        distances[i] = distances[minV]+weights[minV][i];
                        pv[i] = minV;
                    }     
                }
            } //
        }
        // 打印最终结果
        printf("Start vertex: %d\n", startVertex);
        for (int i = 1; i <= vertexNum; i++)
        {
            if(distances[i]==INFINITE)
            {
                printf("Dis(%2d)= INF", i);
                continue;
            }
            else 
                printf("Dis(%2d)=%3d: ",i, distances[i]);
            // 打印路径
            std::stack<int> pVertex;
            int t = i;
            while (t!=startVertex)
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
    void fun()
    {
        
    }
};



#endif