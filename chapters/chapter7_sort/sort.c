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
        for (size_t i = len - 1; i > 0; i--) {
                for (size_t j = 0; j < i; j++) {
                        if (cmp(arr[j], arr[j + 1]) > 0) {
                                swap(arr, j, j + 1);
                        }
                }
        }
}
void select_sort(element_type* arr, size_t len) {
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
        element_type to_be_insert;
        for (size_t i = 0; i < len - 1; i++) {
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
        element_type* tmp_arr = malloc(sizeof(arr[0]) * len);
        _merge_sort(arr, tmp_arr, 0, len - 1);
}

// Median 3
size_t _quick_sort_median3_pivot(element_type* arr, size_t left, size_t right) {
        size_t mid = (left + right) / 2;
        // make sure arr[left] < arr[mid]
        if (cmp(arr[left], arr[mid]) > 0) {
                swap(arr, left, mid);
        }
        // make sure arr[left] < arr[right]
        if (cmp(arr[left], arr[right]) > 0) {
                swap(arr, left, right);
        }
        // make sure arr[mid] < arr[right]
        if (cmp(arr[mid], arr[right]) > 0) {
                swap(arr, mid, right);
        }
        // Now we have arr[left] < arr[mid] (pivot) < arr[right]
        // hidden pivot to arr[right-1]
        swap(arr, mid, right - 1);
        return arr[right - 1];
}
const size_t quick_cutoff = 5;
void _quick_sort(element_type* arr, size_t left, size_t right) {
        element_type pivot;
        size_t i, j;
        // When length of arr is too small, just call insert sort.
        if (left + quick_cutoff < right) {
                pivot = _quick_sort_median3_pivot(arr, left, right);
                // We have arr[left] < pivot = arr[right-1] < arr[right]
                i = left;
                j = right - 1;
                while (1) {
                        while (arr[++i] < pivot);
                        while (arr[--j] > pivot);
                        if (i < j) {
                                swap(arr, i, j);
                        } else {
                                break;
                        }
                }
                // restore pivot
                swap(arr, right - 1, i);
                _quick_sort(arr, left, i - 1);
                _quick_sort(arr, i + 1, right);
        } else {
                insert_sort(arr + left, right - left + 1);
        }

}
void quick_sort(element_type* arr, size_t len) {
        _quick_sort(arr, 0, len - 1);
}
void heap_sort(element_type* arr, size_t len) {
        printf("heap sort\n");
        // TODO
}
void bucket_sort(element_type* arr, size_t len) {
        printf("bucket sort\n");
        // TODO
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
        printf("\n%s\n", is_sorted(arr, len) == 0 ? "Non sorted" : "Sorted");

        sort(arr, len);
        printf("\nAfter sort:\n");
        print_arr(arr, len);
        printf("\n%s\n", is_sorted(arr, len) == 0 ? "Non sorted" : "Sorted");
}

/**
 * @return 0: non-sorted, 1: ascending, -1: descending.
 */
int is_sorted(element_type* arr, size_t len) {
        int sign;
        size_t i, j;
        sign = 1;
        // ascending
        for (i = 0; i < len - 1; i++) {
                if (cmp(arr[i], arr[i + 1]) > 0) {
                        sign = 0;
                        break;
                }
        }
        // descending
        if (sign == 0) {
                sign = -1;
                for (i = 0; i < len - 1; i++) {
                        if (cmp(arr[i], arr[i + 1]) < 0) {
                                sign = 0;
                        }
                }
        }
        return sign;
}