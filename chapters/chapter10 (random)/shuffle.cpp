#include<iostream>
#include<vector>
#include<random>
#include<ctime>
using namespace std;


/*
    思想：每次从原数组中睡觉选取一个数放入结果中，并将该数从原数组中删除。
*/
template<typename T>
vector<T> Fisher_Yates_Shuffle(vector<T>& arr)
{
    srand(time(nullptr));
    int size = arr.size();
    vector<T> result(size);
    for (int i = 0; i < size; i++)
    {
        int k = rand() % size;
        result.push_back(arr[k]);
        arr.erase(arr.begin()+k);
    }
    return result;
}

/*
    每次随机选取一个未处理的数字，并将与未处理数据范围的最后一个位置的数字进行交换
*/
template<typename T>
vector<int> Knuth_Durstenfeld_Shuffle(const vector<T>& arr) 
{
    srand(time(nullptr));
    int size = arr.size();
    // vector<T> result(arr.begin(), arr.end()); 错误，此时arr == result(指向同一个vector)
    vector<T> result(size);
    copy(arr.begin(), arr.end(), result.begin());
    for (int i = size-1; i > 0; i--)
    {
        int k = rand() % (i+1);
        T tmp = result[k];
        result[k] = result[i];
        result[i] = tmp;
    }
    return result;
}

int main()
{
    int num = 20;
    vector<int> arr(20);
    for (int i = 0; i < num; i++)
        arr[i] = i+1;
        // arr.push_back(i+1); push_back()是在已有空间的尾部在添加元素
    vector<int> result = Knuth_Durstenfeld_Shuffle<int>(arr);
    for (int i = 0; i < num; i++)
        printf("%d ", result[i]);
    
    
}

