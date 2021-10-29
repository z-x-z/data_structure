#ifndef TRIE_H
#define TRIE_H
#include"../DescException.h"
#include<string>
#include<vector>
using namespace std;

class Trie
{
    struct TrieNode
    {
        bool isWordEnd;
        vector<TrieNode*> next;
        TrieNode():
        isWordEnd(false), next(26, nullptr)
        {}
    };
    private:
    TrieNode* root;
    int wordSize;
    public:
    Trie():
    root(new TrieNode()), wordSize(0)
    {}

    int size()
    {
        return wordSize;
    }

    void insert(string s) // s应当全部由小写字母组成
    {
        TrieNode* curPos = root;
        for (int i = 0; i < s.size(); i++)
        {
            int ch = s[i]-'a';
            if(ch>=26||ch<0)
                throw IllegalOperationException();
            if(!curPos->next[ch])
                curPos->next[ch] = new TrieNode();
            curPos = curPos->next[ch];
        }
        if(!curPos->isWordEnd)
            wordSize++;
        curPos->isWordEnd = true;
    }

    bool have(string s)
    {
        TrieNode* curPos = root;
        for (int i = 0; i < s.size(); i++)
        {
            int ch = s[i]-'a';
            if(ch>=26||ch<0)
                throw IllegalOperationException();
            if(!curPos->next[ch])
                return false;
            curPos = curPos->next[ch];
        }
        return curPos->isWordEnd;
    }
};


#endif