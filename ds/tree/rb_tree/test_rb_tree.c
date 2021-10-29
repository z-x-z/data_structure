/*
 * @Description  : 
 * @Author       : CagedBird
 * @Date         : 2021-03-07 21:49:32
 * @FilePath     : /dataStructure/ds/tree/rb_tree/test_rb_tree.c
 */

#include<stdio.h>
#include<stdlib.h>

#include "rb_tree.h"

int main(int argc, const char **argv)
{
        rb_tree *tree = rb_create();
        /* int arr[] = {10, 40, 491, 124, 101, 30, 60, 2139, 90, 12, 213, 0, 70, 120, 15, 20, 45, 50, 35, 130, 80};
        int len = sizeof(arr) / sizeof(arr[0]);
        for (int i = 0; i < len; i++) {
                rb_insert(tree, arr[i]);
                printf("Insert: %d, tree: ", arr[i]);
                rb_preorder(tree);
                printf("\n");
        } */
        int random_nums = 50;
        if(argc>1)
                random_nums = atoi(argv[1]);
        for (int i = 0; i < random_nums; i++)
        {
                rb_insert(tree, rand());
        }
        FILE* fp = stdout;
        if(argc>2)
                fp = fopen(argv[2], "w");
        printf("%d node tree json:\n", random_nums);
        rb_tojson_levelorder(tree, fp);
        fprintf(fp, "\n");
        /* for (int i = 0; i < len; i++) {
                rb_remove(tree, arr[i]);
                printf("Remove: %d, tree: ", arr[i]);
                rb_preorder(tree);
                printf("\n");
        } */
        fclose(fp);
        return 0;
}