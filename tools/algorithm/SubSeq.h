#ifndef SUB_SEQ_H
#define SUB_SEQ_H


#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

/*
    从v1中寻找v2的子串
    时间复杂度 O(MN)，空间复杂度 O(1)
 */
template  <typename ElementType>
int findSubSeq(const vector<ElementType> &v1, const vector<ElementType> &v2)
{

    int length1 = v1.size(), length2 = v2.size();
    for (int startI = 0, i; startI <= length1 - length2; startI++)
    {
        for (i = 0; i < length2; i++)
            if (v1[startI + i] != v2[i])
                break;
        if (i==length2)
            return startI;
    }
    return -1;
}

#endif