#include<iostream>
#include<cstring>
#include<stack>
using namespace std;
typedef char ElementType;
// First in, Last out.
struct Stack
{
    static const int DEFAULT_INIT_CAPICITY = 10;
    static const int EMPTY_TOP_INDEX = -1;
    int stackTopIndex;
    int arrayCapicity;
    ElementType* stackElements;

    Stack(int initCapicity = DEFAULT_INIT_CAPICITY)
    : stackTopIndex(EMPTY_TOP_INDEX), arrayCapicity(initCapicity), stackElements(new ElementType[arrayCapicity])
    {assert(stackElements!=nullptr);}

    void increaseCapicity()
    {
        int newArrayCapicity = 2*arrayCapicity;
        ElementType* newStackElements = new ElementType[newArrayCapicity];
        assert(newStackElements!=nullptr);
        for (int i = 0; i < arrayCapicity; i++)
            newStackElements[i] = stackElements[i];
        delete[] stackElements;
        stackElements = newStackElements;
        arrayCapicity = newArrayCapicity;
    }

    void makeEmpty()
    {
        stackTopIndex = EMPTY_TOP_INDEX;
    }


    bool isEmpty()
    {
        return stackTopIndex == EMPTY_TOP_INDEX;
    }

    bool isFull()
    {
        // stackTopIndex从0开始
        return stackTopIndex+1 >= arrayCapicity;
    }

    void push(ElementType element)
    {
        if(isFull()) increaseCapicity();
        stackElements[++stackTopIndex] = element;
    }

    void pop()
    {
        assert(!isEmpty());
        stackTopIndex--;
    }

    ElementType top()
    {
        assert(!isEmpty());
        return stackElements[stackTopIndex];
    }

    ElementType popWithTop()
    {
        assert(!isEmpty());
        return stackElements[stackTopIndex--];
    }
};

bool isBracketPairing(string str)
{
    int len = str.size();
    Stack bracketStack(len/2+1);
    for (int i = 0; i < len; i++)
    {
        char ch = str[i];
        if(ch=='{'||ch=='['||ch=='(') bracketStack.push(ch);
        else if(ch=='}'||ch==']'||ch==')')
        {
            // 40  (    41  )
            // 91  [    92  \    93  ]
            // 123  {   124  |   125  }
            char leftBracket = ch == ')' ? ch-1 : ch-2;
            if(bracketStack.isEmpty()||bracketStack.popWithTop()!=leftBracket) return false;
        }
    }
    return bracketStack.isEmpty();

}
int main()
{
    
}