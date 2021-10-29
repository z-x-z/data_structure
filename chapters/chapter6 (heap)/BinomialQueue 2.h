//
// Created by zxz on 2020/4/10.
//
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

#ifndef DATASTRUCTURE_BINOMIALQUEUE_H
#define DATASTRUCTURE_BINOMIALQUEUE_H

template<typename Comparable>
class BinomialQueue
{
public:
    BinomialQueue();
    BinomialQueue(const Comparable& comparable);
    BinomialQueue(const BinomialQueue& rhs);
    ~BinomialQueue();

    bool isEmpty() const;
    const Comparable& findMin() const;
    int size() const;

    void insert(const Comparable& item);
    void deleteMin();

    void makeEmpty();
    void merge(BinomialQueue & rhs);

    BinomialQueue& operator=(const BinomialQueue& rhs);


private:
    struct BinomialNode
    {
        Comparable element;
        BinomialNode* nextSibling;
        BinomialNode* leftChild;
        explicit BinomialNode(const Comparable& theElement, BinomialNode* sibling= nullptr, BinomialNode* child= nullptr):
                element(theElement), nextSibling(sibling), leftChild(child){}
    };

    vector<BinomialNode*> binomialForest;
    int currentSize; // the total number of the elements in queue

    // t1->t2
    BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2)
    {
        if(t1->element>t2->element) return combineTrees(t2, t1);
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
        return t1;
    }
    void makeEmpty(BinomialNode* & t);

    int findMinIndex() const;
    int capacity() const;

    BinomialNode* cloneTree(const BinomialNode* t) const
    {
        if(t== nullptr)
            return nullptr;
        else
            return new BinomialNode(t->element, cloneTree(t->nextSibling), cloneTree(cloneTree(t->leftChild)));
    }
    void clearTree(BinomialNode* t)
    {
        if(t!= nullptr)
        {
            clearTree(t->nextSibling);
            clearTree(t->leftChild);
            delete t;
            t = nullptr;
        }
    }

};

// public
template<typename Comparable>
BinomialQueue<Comparable>::BinomialQueue()
{
    currentSize = 0;
}

template<typename Comparable>
BinomialQueue<Comparable>::BinomialQueue(const BinomialQueue& rhs)
:binomialForest(rhs.binomialForest.size()), currentSize(rhs.currentSize)
{
    for(int i = 0; i < binomialForest.size(); ++i)
        binomialForest[i] = cloneTree(rhs.binomialForest[i]);
}

template<typename Comparable>
BinomialQueue<Comparable>::BinomialQueue(const Comparable& comparable)
{
    binomialForest.push_back(new BinomialNode(comparable));
    currentSize = 1;
}

template<typename Comparable>
bool BinomialQueue<Comparable>::isEmpty() const
{
    return currentSize==0;
}

template<typename Comparable>
BinomialQueue<Comparable>::~BinomialQueue()
{
    makeEmpty();
}

template<typename Comparable>
const Comparable& BinomialQueue<Comparable>::findMin() const
{
    return binomialForest[findMinIndex()]->element;
}

template<typename Comparable>
int BinomialQueue<Comparable>::size() const
{
    return currentSize;
}

template<typename Comparable>
void BinomialQueue<Comparable>::insert(const Comparable& item)
{
    BinomialQueue<Comparable> newQueue(item);
    merge(newQueue);
}

template<typename Comparable>
void BinomialQueue<Comparable>::deleteMin()
{
    assert(!isEmpty());
    // separate min tree form the forest
    int minIndex = findMinIndex();
    BinomialNode* minRoot = binomialForest[minIndex];
    BinomialNode* newTree = minRoot->leftChild;
    binomialForest[minIndex] = nullptr;
    delete minRoot;

    // delete min node form the min tree to form a new forest(queue)
    BinomialQueue newQueue;
    newQueue.binomialForest.resize(minIndex);
    for(int i = minIndex-1; i >=0 ; i--)
    {
        newQueue.binomialForest[i] = newTree;
        newTree = newTree->nextSibling;
        newQueue.binomialForest[i]->nextSibling = nullptr;
    }

    // merge
    newQueue.currentSize = (1 << minIndex) -1;
    currentSize-= newQueue.currentSize+1;
    merge(newQueue);
}

template<typename Comparable>
void BinomialQueue<Comparable>::makeEmpty()
{
    for(auto tree: binomialForest)
        clearTree(tree);
    currentSize = 0;
}

template<typename Comparable>
void BinomialQueue<Comparable>::merge(BinomialQueue& rhs)
{
    currentSize+=rhs.currentSize;
    if(currentSize>capacity())
    {
        auto oldForestSize = binomialForest.size();
        int newForestSize = max(oldForestSize, rhs.binomialForest.size())+1;
        binomialForest.resize(newForestSize);
        for(int i = oldForestSize; i < newForestSize; ++i)
            binomialForest[i] = nullptr;
    }
    BinomialNode* carry = nullptr;
    for(int i = 0, forestSize = binomialForest.size(); i < forestSize; ++i)
    {
        BinomialNode* t1 = binomialForest[i];
        BinomialNode* t2 = i < rhs.binomialForest.size() ? rhs.binomialForest[i] : nullptr;
        switch((t1 != nullptr) + (t2 != nullptr) * 2 + (carry != nullptr) * 4)
        {
            case 0: //
            case 1: // t1
                break; // do noting
            case 2: // only t2 isn't nullptr
                binomialForest[i] = t2;
                break;
            case 4: // only carry isn't nullptr
                binomialForest[i] = carry;
                carry = nullptr;
                break;
            case 3: // t1, t2 isn't nullptr
                carry = combineTrees(t1, t2);
                binomialForest[i]= nullptr;
//               binomialForest[i]= rhs.binomialForest[i] = nullptr;
//               fatal error! 可能会对rhs.binomialForest进行超出范围的下标访问
                break;
            case 5: // t1, carry
                carry = combineTrees(t1, carry);
                binomialForest[i] = nullptr;
//                binomialForest[i]= rhs.binomialForest[i] = nullptr;
                break;
            case 6: // t2, carry
                carry = combineTrees(t2, carry);
                break;
            case 7: // t1, t2, carry
                binomialForest[i] = carry;
                carry = combineTrees(t1, t2);
                break;
        }
    }
    for(auto& tree: rhs.binomialForest)
        tree = nullptr;
    rhs.currentSize = 0;
}

template<typename Comparable>
BinomialQueue<Comparable>& BinomialQueue<Comparable>::operator=(const BinomialQueue& rhs)
{
    if(this!=rhs)
    {
        makeEmpty();
        for(auto binomialTree: rhs.binomialForest)
            binomialForest.push_back(cloneTree(binomialTree));
        currentSize = rhs.size();
    }
    return *this;
}


template<typename Comparable>
void BinomialQueue<Comparable>::makeEmpty(BinomialQueue::BinomialNode*& t)
{
    binomialForest.clear(); // 删除vector
    currentSize = 0;
}

template<typename Comparable>
int BinomialQueue<Comparable>::findMinIndex() const
{
    assert(!isEmpty());
    int mini;
    for(mini = 0; binomialForest[mini] == nullptr; ++mini) ;
    Comparable tmp = binomialForest[mini]->element;
    for(int i = mini+1; i < binomialForest.size(); ++i)
    {
        if(binomialForest[i]!= nullptr&&binomialForest[i]->element<tmp)
        {
            tmp = binomialForest[i]->element;
            mini = i;
        }
    }
    return mini;
}

template<typename Comparable>
int BinomialQueue<Comparable>::capacity() const
{
    return (1<<binomialForest.size()) -1;
}




// private

#endif //DATASTRUCTURE_BINOMIALQUEUE_H
