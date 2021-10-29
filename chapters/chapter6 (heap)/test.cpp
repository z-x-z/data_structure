#include"BinaryHeap.h"
#include<iostream>


int main()
{
    vector<int> nums{1, 3, 5, 4, 2, 7, 9};
    BinaryHeap<int> heap(nums);
    cout<<heap.getMin()<<" ";
    heap.deleteMin();
    heap.insert(10); // int&&
    heap.insert(11);
    heap.insert(0);
    int a = 17;
    heap.insert(a); // const int &
    heap.insert(a); // const int &
    while (!heap.empty())
    {
        cout<<heap.getMin()<<" ";
        heap.deleteMin();
    }
}