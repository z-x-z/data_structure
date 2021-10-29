#include<iostream>
struct StackNode;

typedef StackNode* Position;
typedef int ElementType;


struct StackNode
{
    ElementType element;
    Position next;
    StackNode(ElementType _element): element(_element), next(NULL) {};
};

struct Stack
{
    StackNode* header;
    Stack(): header(new StackNode(-1)){}
    bool isEmpty()
    {
        return header->next==NULL;
    }
    void makeEmpty()
    {
        while (!isEmpty())
            pop();
    }
    // 头删法/*  */
    void pop()
    {
        assert(!isEmpty());
        Position p = header->next;
        header->next = p->next;
        delete p;
    }
    // 头插法
    void push(ElementType element)
    {
        Position p = new StackNode(element);
        assert(p!=NULL);
        p->next =  header->next;
        header->next = p;
    }
    ElementType top()
    {
        assert(!isEmpty());
        return header->next->element;
    }
};
int main()
{
    // Stack myStack(); 错误的使用空参构造函数，因为其和一个函数声明相冲突
    // True: 1.Stack myStack;  2.Stack myStack = Stack();
    Stack myStack;
    myStack.push(1);
    myStack.push(2);
    myStack.push(3);
    printf("%d\n", myStack.top());
    myStack.pop();
    printf("%d\n", myStack.top());
    myStack.push(4);
    printf("%d\n", myStack.top());
    printf("%d\n", myStack.isEmpty());
    myStack.pop();
    myStack.pop();
    myStack.pop();
    // myStack.pop();
}