#include<iostream>
#include<vector>
#include<functional>
using namespace std;

/*
    objects's size > 0
*/
template<typename objectType, typename comparator>
const objectType& findMax(vector<objectType> objects, comparator cmp)
{
    int maxIndex = 0;
    for (int i = 1; i < objects.size(); i++)
        // use function object
        if(cmp(objects[maxIndex], objects[i])<0)
            maxIndex = i;
    return objects[maxIndex];
}
// generalize
template<typename objectType>
const objectType& findMax(vector<objectType> objects)
{
    return findMax(objects, less<objectType>());
}

class functionObject
{
    public:
    int operator()(const string& s1, const string& s2) const
    {
        return strcmp(s1.c_str(), s2.c_str());
    }
};

int main()
{
    vector<string> vec;
    vec.push_back("abc");
    vec.push_back("bbe");
    vec.push_back("cac");
    cout<<findMax(vec, functionObject());
}