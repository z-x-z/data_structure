#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H
#include<fstream>
#include<iostream>


class ListGraph
{
    struct VertexNode;
    typedef VertexNode* VertexList;
    struct VertexNode
    {
        int id;
        int weight;
        VertexNode* next;
        VertexNode()
        {}
        VertexNode(int _id, int _weight= 1):
        id(_id), weight(_weight), next(nullptr){}
        void insert(int _id, int _weight= 1)
        {
            VertexNode* node = this;
            while (node->next!= nullptr)
            {
                // if(node->id==_id)
                //     return;
                node = node->next;
            }
            node->next = new VertexNode(_id, _weight);
        }
        VertexList copy()
        {
            VertexNode* node= this->next;
            VertexNode* newNode = new VertexNode(id);
            VertexNode* tmp = newNode;
            while (node!=nullptr)
            {
                tmp->next = new VertexNode(node->id, node->weight);
                tmp = tmp->next;
                node = node->next;
            }
            return newNode;
        }
        void destroy()
        {
            VertexNode* node = this;
            VertexNode* tmp;
            while (node)
            {
                tmp = node->next;
                delete node;
                node = tmp;
            }
        }

    };


private:
    int vertexNum;
    bool isDirected;
    bool isWeighted;
    VertexList* vertexLists;
    void initLists(VertexList* _vertexLists= nullptr)
    {
        vertexLists = new VertexList[vertexNum+1];
        if(_vertexLists==nullptr)
        {
            for (int i = 1; i <= vertexNum; i++)
                vertexLists[i] = new VertexNode(i);
        }
        else
            for (int i = 1; i <= vertexNum; i++)
                vertexLists[i] = _vertexLists[i]->copy();

    }
    void deleteLists()
    {
        for (int i = 1; i <= vertexNum; i++)
            vertexLists[i]->destroy();
        delete [] vertexLists;
        vertexNum = 0;
    }
public:
    explicit ListGraph(const ListGraph& rhs)
    : vertexNum(rhs.vertexNum), isDirected(rhs.isDirected), isWeighted(rhs.isWeighted)
    {
        initLists(rhs.vertexLists);
    }
    explicit ListGraph(const int _vertexNum, bool _isWeighted= false, bool _isDirected= true)
    : vertexNum(_vertexNum), isDirected(_isDirected), isWeighted(_isWeighted)
    {
        initLists();
    }
    explicit ListGraph(std::ifstream& f, bool _isWeighted= false, bool _isDirected= true )
    : isDirected(_isDirected), isWeighted(_isWeighted)
    {
        f>>vertexNum;
        initLists();
        int edgeNum;
        f>>edgeNum;
        for (int i = 0, v1, v2, weight=1; i < edgeNum; i++)
        {
            f>>v1>>v2;
            if(isWeighted)
                f>>weight;
            if(isDirected)
                vertexLists[v1]->insert(v2, weight);
            else
            {
                vertexLists[v1]->insert(v2, weight);
                vertexLists[v2]->insert(v1, weight);
            }
        }

    }
    const ListGraph& operator=(const ListGraph& rhs)
    {
        if(this!=&rhs)
        {
            if(vertexNum==rhs.vertexNum)
            {
                for (int i = 1; i <= vertexNum; i++)
                {
                    if(vertexLists[i]->next)
                        vertexLists[i]->next->destroy();
                    vertexLists[i]->next = nullptr;
                    if(rhs.vertexLists[i]->next)
                        vertexLists[i]->next = rhs.vertexLists[i]->next->copy();
                }
            }
            else
            {
                deleteLists();
                vertexNum = rhs.vertexNum;
                initLists(rhs.vertexLists);
            }
            isDirected = rhs.isDirected;
            isWeighted = rhs.isWeighted;
        }
        return *this;
    }

    ~ListGraph()
    {
        deleteLists();
    }

    int getVertexNum()
    {
        return vertexNum;
    }

    void insert(int v1, int  v2, int weight= 1)
    {
        if(!isWeighted)
            weight = 1;
        if(isDirected)
            vertexLists[v1]->insert(v2, weight);
        else
            {
                vertexLists[v1]->insert(v2, weight);
                vertexLists[v2]->insert(v1, weight);
            }
    }

    void print()
    {
        for (int i = 1; i <= vertexNum; i++)
        {
            printf("%3d:  ", i);
            VertexNode* node = vertexLists[i]->next;
            while (node!=nullptr)
            {
                if(isWeighted)
                    printf("->%3d(%5d)  ", node->id, node->weight);
                else
                    printf("->%3d  ", node->id);
                node = node->next;
            }
            printf("\n");
        }
    }
};



#endif