#include<iostream>
#include<functional>
#include<stack>
#include<vector>
using namespace std;

template<typename T>
struct BinaryHeap
{
    int capacity;
    int size;
    T* elements;
    BinaryHeap(int initCapicity= 10): capacity(initCapicity), size(0),
    elements(new T[capacity+1]) {}

    void increaseCapicity()
    {
        int newCapicity = 2*capacity;
        T* newElements = new T[newCapicity+1];
        for (int i = 1; i <= size; i++)
            newElements[i] = elements[i];
        assert(newElements!=nullptr);
        capacity = newCapicity;
        delete[] elements;
        elements = newElements;

    }

    void insert(T value)
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

    void deleteElement(int index)
    {
        assert(index>=1&&index<=size);
        elements[index] = elements[size--];
        percolateDown(index);
    }

    const T& getMin()
    {
        return elements[1];
    }

    void percolateUp(int i, int value)
    {
        for (; i>1&&elements[i/2]>value; i/=2)
            elements[i] = elements[i/2];
        elements[i] = value;
    }

    void percolateDown(int i)
    {
        T tmp = elements[i];
        int hole = i, child;
        for (; hole*2 <= size; hole=child)
        {
            child = hole*2;
            // 选择子节点中的更小者（如果存在）
            if(child+1<=size&&elements[child+1]<elements[child])
                child++;
            // 直到子节点都小于minValue时
            if(tmp<=elements[child]) break;
            elements[hole] = elements[child];
        }
        elements[hole] = tmp;
    }

    static BinaryHeap buildByArray(const vector<T> & arr)
    {
        int size = arr.size();
        BinaryHeap heap(size);
        for (int i = 1; i <= size; i++)
            heap.elements[i] = arr[i-1];
        heap.size = 20;
        for (int i = size/2; i >= 1; i--)
            heap.percolateDown(i);
        return heap;
    }
};