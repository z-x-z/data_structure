/*
 * @FilePath     : /dataStructure/chapters/chapter7_sort/sort.h
 * @Author       : CagedBird
 * @Date         : 2021-10-26 10:31:06
 * @Description  : 
 */
#ifndef SORT_H
#define SORT_H

#include<stdlib.h>

typedef int element_type;
typedef void (*sort_fun) (element_type*, size_t) ;
typedef void (*swap_fun) (element_type*, size_t, size_t);
typedef int (*cmp_fun) (element_type, element_type);


void test_sort(sort_fun sort, element_type* arr, size_t len);

void bubble_sort(element_type* arr, size_t len);
void select_sort(element_type* arr, size_t len);
void insert_sort(element_type* arr, size_t len);
void shell_sort(element_type* arr, size_t len);
void merge_sort(element_type* arr, size_t len);
void quick_sort(element_type* arr, size_t len);
void heap_sort(element_type* arr, size_t len);
void bucket_sort(element_type* arr, size_t len);

#endif