#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include<functional>
#include<stack>
#include<vector>
using namespace std;

template<typename Comparable>
class BinaryHeap
{
private:
    int capacity;
    int size;
    vector<Comparable> elements;

    void increaseCapicity()
    {
        int newCapicity = 2*capacity;
        elements.resize(newCapicity+1);
        capacity = newCapicity;
    }

    // 在index处向上调整堆，指导value赋值给合适的位置为止
    void percolateUp(int index, const Comparable& value)
    {
        for (; index>1&&elements[index/2]>value; index/=2)
            elements[index] = elements[index/2];
        elements[index] = value;
    }

    // 在index处向下调整堆
    void percolateDown(int index)
    {
        Comparable tmp = elements[index];
        int hole = index;
        for (int child; hole*2 <= size; hole=child)
        {
            child = hole*2;
            // 选择子节点中的更小者（如果存在）
            if(child+1<=size&&elements[child+1]<elements[child])
                child++;
            // 直到子节点都小于minValue时
            if(tmp<elements[child]) break;
            elements[hole] = elements[child];
        }
        elements[hole] = tmp;
    }

    void build()
    {
        for (int i = size/2; i >= 1; i--)
            percolateDown(i);
    }
public:
    BinaryHeap(int initCapicity= 10)
    : capacity(initCapicity), size(0),elements(initCapicity+1) {}

    BinaryHeap(const vector<Comparable>& comparables)
    : capacity(comparables.size()), size(comparables.size()), elements(capacity+1)
    {
        for (int i = 0; i < size; i++)
            // 实际堆的元素的下标从1开始
            elements[i+1] = comparables[i];
        build();
    }

    bool isEmpty()
    {
        return size==0;
    }

    void insert(Comparable&& value)
    {
        if(size>=capacity) increaseCapicity();
        percolateUp(++size, value);
    }

    void insert(const Comparable& value)
    {
        if(size>=capacity) increaseCapicity();
        percolateUp(++size, value);
    }
    void deleteMin()
    {
        assert(size>0);
        elements[1] = elements[size--];
        percolateDown(1);
    }

    const Comparable& getMin()
    {
        return elements[1];
    }
};

#endif