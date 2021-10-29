#include<iostream>
#include<vector>
using namespace std;

struct BucketNode;

typedef BucketNode* Bucket;
typedef BucketNode* Position;
typedef int ElementType;

const int radix = 10;

struct BucketNode
{
    ElementType element;
    Position next;
    BucketNode(ElementType _element = -1): element(_element), next(NULL){}
    void insert (ElementType insertVal)
    {
        Position p = this;
        while (p->next) p = p->next;
        p->next = new BucketNode(insertVal);
    }
};

int getRadix(int num, int index)
{
    for (int i = 0; i < index-1; i++) num = num/radix;
    return num % radix;
}

void radixSort(vector<ElementType> nums)
{
    Bucket* heads = new Bucket[radix];
    for(int num : nums) heads[getRadix(num, 1)]->insert(num);
    int maxRadixNum = radix;
    
}

int main()
{

}