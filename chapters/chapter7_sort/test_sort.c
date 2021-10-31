/*
 * @FilePath     : /dataStructure/chapters/chapter7_sort/test_sort.c
 * @Author       : CagedBird
 * @Date         : 2021-10-26 11:30:13
 * @Description  :
 */

#include"sort.h"
#include <stdlib.h>
#include <time.h>

int main() {
        // int arr[] = {1, 17, 15, 11, 5, 14, 19, 4, 3, 16, 10, 20, 18, 8, 9, 2, 13, 7, 6, 12};
        size_t arr_len = 100;
        srand(time(NULL));
        int* arr = malloc(arr_len * sizeof(int));
        for (size_t i = 0; i < arr_len; i++) {
                arr[i] = rand() % 1000;
        }
        test_sort(quick_sort, arr, arr_len);
        
}