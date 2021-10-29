#include<assert.h>
#include<iostream>
#include<time.h>


struct ListNode;
typedef ListNode* Position;
typedef int ElementType;

struct ListNode
{
    ElementType key;
    Position next;
    ListNode(): next(NULL){}
    ListNode(ElementType _key): key(_key), next(NULL){}
};

int NextPrime(int num)
{
    if (num==2) return 2;
    num += num % 2 == 0 ? 1: 0;
    for (; ; num+=2)
    {
        bool isPrime = true;
        for (int i = 3; i*i <= num; i+=2)
        {
            if(num%i==0) 
            {
                isPrime = false;
                break;
            };
        }
        if(isPrime) return num;
    }
}

typedef Position List;
struct HashTableSC
{
    int tableSize;
    List* lists;

    HashTableSC(int _tableSize)
    {
        tableSize = NextPrime(_tableSize);
        // 初始化表
        lists = new List[tableSize];
        assert(lists!=NULL);
        // 初始化表头
        for (int i = 0; i < tableSize; i++)
        {
            lists[i] = new ListNode;
            assert(lists[i]!=NULL);
        }
    }

    int Hash(int key)
    {
        return key % tableSize;
    }

    Position Find(int key)
    {
        List list = lists[Hash(key)];
        Position p = list->next;
        while (p!=NULL && p->key!=key) p = p->next;
        return p;
    }

    void Insert(int key)
    {
        List list = lists[Hash(key)];
        Position p = list->next;
        while (p!=NULL && p->key!=key) p = p->next;
        if(p==NULL)
        {
            ListNode* newNode = new ListNode(key);
            // 头插法
            newNode->next = list->next;
            list->next = newNode;
        }
    }

};


int main()
{
    // INT_MAX 2147483647 (11位)
    const int num = 100;
    HashTableSC hashTableSC(num);
    int nums[num];
    
    
}