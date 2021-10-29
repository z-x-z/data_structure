/*
 * @Description  : Red black tree c implemention
 * @Author       : CagedBird
 * @Date         : 2021-03-07 13:35:37
 * @FilePath     : /dataStructure/ds/tree/rb_tree/include/rb_tree.h
 */

#ifndef RB_TREE_H
#define RB_TREE_H
#include<stdio.h>

typedef int key_type;
typedef int value_type;

/* 红黑树节点对象 */

struct  _rb_node;
typedef struct _rb_node rb_node;

/* 红黑树对象 */
struct  _rb_tree;
typedef struct  _rb_tree rb_tree;

/*  创建一颗红黑树
*/
rb_tree* rb_create();
/* 在红黑树中查找相应的键(迭代版本)的节点
   查找成功返回该节点，失败返回NULL
 */
rb_node* rb_search(rb_tree* tree, key_type key);
/* 将键插入对应红黑树中
   查找成功返回该节点，失败返回NULL
 */
rb_node* rb_insert(rb_tree* tree, key_type key);
rb_node* rb_insert_val(rb_tree* tree, key_type key, value_type val);

/* 从红黑树删除对应键值的节点
   删除成功返回1，失败返回0
 */
int rb_remove(rb_tree* tree, key_type key);

/* 摧毁整颗红黑树 
*/
void rb_destory(rb_tree* tree);

/* 前序遍历红黑树 */
void rb_preorder(rb_tree* tree);
/* 中序遍历红黑树 */
void rb_inorder(rb_tree* tree);
/* 后序遍历红黑树 */
void rb_postorder(rb_tree* tree);
/* 层序遍历 */
void rb_tojson_levelorder(rb_tree* tree, FILE* fp);

/* 查询红黑树键最大的节点
   查询成功返回对应节点，失败返回NULL
 */
rb_node* rb_maximum(rb_tree* tree);
/* 查询红黑树键最小的节点
   查询成功返回对应节点，失败返回NULL
 */
rb_node* rb_minimum(rb_tree* tree);


#endif