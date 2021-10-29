/*
 * @FilePath     : /dataStructure/chapters/chapter7_sort/sort.c
 * @Author       : CagedBird
 * @Date         : 2021-10-26 10:25:43
 * @Description  :
 */
#include<stdio.h>
#include "sort.h"

void default_swap(element_type* arr, size_t i, size_t j) {
        element_type tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
}

int default_cmp(element_type a, element_type b) {
        return a - b;
}

swap_fun swap = &default_swap;
cmp_fun cmp = &default_cmp;

void bubble_sort(element_type* arr, size_t len) {
        printf("bubble sort\n");
        for (size_t i = len - 1; i > 0; i--) {
                for (size_t j = 0; j < i; j++) {
                        if (cmp(arr[j], arr[j + 1]) > 0) {
                                swap(arr, j, j + 1);
                        }
                }
        }
}
void select_sort(element_type* arr, size_t len) {
        printf("select sort\n");
        size_t min_i;
        for (size_t i = 0; i < len; i++) {
                min_i = i;
                for (size_t j = i; j < len; j++) {
                        if (cmp(arr[j], arr[min_i]) < 0) {
                                min_i = j;
                        }
                }
                swap(arr, i, min_i);
        }
}
void insert_sort(element_type* arr, size_t len) {
        printf("insert sort\n");
        element_type to_be_insert;
        for (size_t i = 1; i < len - 1; i++) {
                // [0 ~ i] is sorted.
                to_be_insert = arr[i + 1];
                for (size_t j = i; j >= 0 && cmp(to_be_insert, arr[j]) < 0; j--) {
                        swap(arr, j, j + 1);
                }
        }

}
void shell_sort(element_type* arr, size_t len) {
        printf("shell sort\n");
        for (size_t increment = len / 2; increment > 0; increment /= 2) {
                for (size_t j = 0; j < len; j++) {
                        // TODO
                }
        }
}

void _merge_sort(element_type* arr, element_type* tmp_arr, size_t left, size_t right) {
        size_t mid;
        size_t i, li, ri;
        if (right - left > 0) {
                mid = (right + left) / 2;
                _merge_sort(arr, tmp_arr, left, mid);
                _merge_sort(arr, tmp_arr, mid + 1, right);
                i = li = left;
                ri = mid + 1;
                while (li <= mid && ri <= right) {
                        if (arr[li] < arr[ri]) {
                                tmp_arr[i++] = arr[li++];
                        } else {
                                tmp_arr[i++] = arr[ri++];
                        }
                }
                while (li <= mid) {
                        tmp_arr[i++] = arr[li++];
                }
                while (ri <= right) {
                        tmp_arr[i++] = arr[ri++];
                }
                for (i = left; i <= right; i++) {
                        arr[i] = tmp_arr[i];
                }
        }
}
void merge_sort(element_type* arr, size_t len) {
        printf("merge sort\n");
        element_type* tmp_arr = malloc(sizeof(arr[0]) * len);
        _merge_sort(arr, tmp_arr, 0, len - 1);
}

// Median 3
size_t _quick_sort_pivot(element_type* arr, size_t left, size_t right) {
        return (arr[left] + arr[(left + right) / 2] + arr[right]) / 3;
}
void _quick_sort(element_type* arr, size_t left, size_t right) {
        element_type pivot;
        size_t i, j;
        pivot = _quick_sort_pivot(arr, left, right);
        i = left;
        j = right - 1;
        while (1) {
                while (arr[i++] < pivot);
                while (arr[j--] > pivot);
                if (i < j){
                        swap(arr, i, j);
                }
                else{
                        break;
                }
        }
        _quick_sort(arr, left, i - 1);
        _quick_sort(arr, i + 1, right);
}
void quick_sort(element_type* arr, size_t len) {
        printf("quick sort\n");
        _quick_sort(arr, 0, len - 1)
}
void heap_sort(element_type* arr, size_t len) {
        printf("heap sort\n");
}
void bucket_sort(element_type* arr, size_t len) {
        printf("bucket sort\n");
}

void print_ele(element_type ele) {
        printf("%4d", ele);
}

void print_arr(element_type* arr, size_t len) {
        for (size_t i = 0; i < len; i++) {
                print_ele(arr[i]);
                if (i != len - 1) {
                        if ((i + 1) % 10 == 0) {
                                printf("\n");
                        } else {
                                printf(",");
                        }
                }
        }
}

void test_sort(sort_fun sort, element_type* arr, size_t len) {
        printf("Before sort:\n");
        print_arr(arr, len);
        printf("\nAfter sort:\n");
        sort(arr, len);
        print_arr(arr, len);
}
