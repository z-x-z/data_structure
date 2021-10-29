// #include<iostream>
// #include<vector>
 #include"tree/Trie.h"
#include<iostream>

int main()
{
    Trie trie;
    trie.insert("zhang");
    trie.insert("xiong");
    trie.insert("zhen");
    cout<<trie.size()<<endl;
    cout<<trie.have("zhang")<<endl;;
    cout<<trie.have("zhan")<<endl;;
    cout<<trie.have("xiong")<<endl;;
    cout<<trie.have("xion")<<endl;;
    cout<<trie.have("xiongg")<<endl;;
    cout<<trie.have("zhen")<<endl;;
}