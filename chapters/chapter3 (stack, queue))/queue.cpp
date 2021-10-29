#include<iostream>
// #include<queue>
using namespace std;

/* template<typename T> cpp version*/
typedef int T;
struct Queue
{
    T* elements;
    int capacity;
    int _size;
    int head;
    int rear;
    // (front) head <- -> rear (back)
    Queue(int _capicity = 10): capacity(_capicity), elements(new T[_capicity]),
    _size(0), head(1), rear(0){}
    void incrementCapicity()
    {
        int newCapicity = capacity*2;
        T* newElements = (T*) malloc(newCapicity*sizeof(Queue));
        /* T* newElements = new T[newCapicity]; cpp version*/
        int j = 0;
        for (int i = head; i < capacity; i++)
            newElements[j++]= elements[i];
        head = 0;
        for (int i = 0; j < capacity; i++)
            newElements[j++]= elements[i];
        rear = j-1;
        /* delete[] elements; cpp version*/
        free(elements);
        elements = newElements;
        capacity = newCapicity;
    }
    bool isFull()
    {
        return _size>= capacity;
    }
    bool isEmpty()
    {
        return _size<=0;
    }
    int size()
    {
        return _size;
    }
    void push_back(T element)
    {
        if(isFull()) incrementCapicity();
        if(++rear>=capacity) rear = 0;
        elements[rear] = element;
        _size++;
    }
    void push_front(T element)
    {
        if(isFull()) incrementCapicity();
        if(--head<0) head = capacity-1;
        elements[head] = element;
        _size++;
    }
    void pop_back()
    {
        assert(!isEmpty());
        if(--rear<0) rear = capacity-1;
        _size--;
    }
    void pop_front()
    {
        assert(!isEmpty());
        if(++head>=capacity) head = 0;
        _size--;
    }
    T back()
    {
        return elements[rear];
    }
    T front()
    {
        return elements[head];
    }
};
int main()
{
    Queue myQueue = Queue(3);
    for (int i = 0; i < 10; i++)
    {
        myQueue.push_front(i+1);
        for (int i = 0; i < myQueue.capacity; i++)
        {
            printf("%d ", myQueue.elements[i]);
        }
        printf("\nhead: %d, rear: %d\n", myQueue.head, myQueue.rear);    
    }
}