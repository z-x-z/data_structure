#include <iostream>
#include <vector>
using namespace std;

// arr默认按升序排列
// 若target在arr中，则返回其对应的下标(0 ~ arr.size()-1)。
// 若target不在arr中，则返回将其按升序排序插入后的下标值相反数-1后的结果(-arr.size()-1 ~ -1)。
int BinarySearch(vector<int> sortedArr, int target)
{
    int left = 0, right = sortedArr.size() - 1, mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        if (sortedArr[mid] > target)
            right = mid;
        else if (sortedArr[mid] < target)
            left = mid + 1;
        else
            return mid;
    }
    if (target < sortedArr[left]) // 此时，left等于right
        left = -(left + 1);
    else if (target > sortedArr[left])
        left = -(left + 2);
    return left;
}

int main()
{
    vector<int> arr{1, 3, 5, 7, 9, 11, 14};
    int testNumMax = 15;
    for (int i = 0; i <= testNumMax; i++)
    {
        cout << "Test " << i << ", result: " << BinarySearch(arr, i) << endl;
    }
}