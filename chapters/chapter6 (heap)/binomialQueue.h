#include<iostream>
#include<vector>

using namespace std;
#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

template<typename Comparable>
class BinomialQueue
{
    public:
    BinomialQueue();
    BinomialQueue(const BinomialQueue& rhs);
    ~BinomialQueue();

    bool isEmpty() const;
    const Comparable& findMin() const;
    int size() const;

    void insert(const Comparable& item);
    void deleteMin();

    void makeEmpty();
    void merge(BinomialQueue & rhs);

    const BinomialQueue& operator=(const BinomialQueue& rhs);


    private:
    struct BinomialNode
    {
        Comparable element;
        BinomialNode* leftSibling;
        BinomialNode* nextChild;
        BinomialNode(const Comparable& theElement, BinomialNode* sibling= nullptr, BinomialNode* child= nullptr):
        element(theElement), leftSibling(sibling), nextChild(child){}
    };

    vector<BinomialNode*> binomialForest;
    int currentSize; // the total number of the elements in queue

    BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2);
    void makeEmpty(BinomialNode* & t);
    BinomialNode* clone(const BinomialNode* t) const;


}

#endif