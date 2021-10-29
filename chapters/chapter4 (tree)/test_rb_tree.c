/*
 * @Description  : 
 * @Author       : CagedBird
 * @Date         : 2021-03-07 21:49:32
 * @FilePath     : /dataStructure/chapters/chapter4 (tree)/test_rb_tree.c
 */

#include<stdio.h>
#include "rb_tree.h"

int main(int argc, const char** argv)
{
        int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        int len = sizeof(arr) / sizeof(arr[0]);
        rb_tree* tree = rb_create();
        for (int i = 0; i < len; i++)
        {
                rb_insert(tree, arr[i]);
                printf("Insert: %d, tree: ", arr[i]);
                rb_preorder(tree);
                printf("\n");
        }
        return 0;
}