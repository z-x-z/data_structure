#include "rb_tree.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#define rb_parent(n)        ((n)->parent)
#define rb_set_parent(n, p) ((n)->parent = p)
#define rb_color(n)         ((n)->color)
#define rb_is_red(n)        ((n)->color == RED)
#define rb_is_black(n)      (!(rb_is_red(n)))
#define rb_set_color(n, c)      \
        do {                    \
                (n)->color = c; \
        } while (0)
#define rb_set_red(n)             \
        do {                      \
                (n)->color = RED; \
        } while (0)
#define rb_set_black(n)             \
        do {                        \
                (n)->color = BLACK; \
        } while (0)

/*  创建一颗红黑树
*/
rb_tree *rb_create()
{
        rb_tree *tree = (rb_tree *)malloc(sizeof(rb_tree));
        tree->root = NULL;
        return tree;
}
/* static void _rb_swap_node(rb_node* a, rb_node* b){
        rb_node* son, parent;
        tmp = a->left;

} */
static rb_node *_rb_create_node(key_type key, value_type val, color_type color,
                                rb_node *parent, rb_node *left, rb_node *right)
{
        rb_node *node = (rb_node *)malloc(sizeof(rb_node));
        node->key = key;
        node->val = val;
        node->color = color;
        node->parent = parent;
        node->left = left;
        node->right = right;
        return node;
}
/* 迭代搜索版本 */
static rb_node *_rb_node_search(rb_node *root, key_type key)
{
        rb_node *node = root;
        while (node && node->key != key) {
                node = key < node->key ? node->left : node->right;
        }
        return node;
}
/* 在红黑树中查找相应的键(迭代版本)的节点
   查找成功返回该节点，失败返回NULL
 */
rb_node *rb_search(rb_tree *tree, key_type key)
{
        return tree != NULL ? _rb_node_search(tree->root, key) : NULL;
}

/* 摧毁整颗红黑树 
*/
/* 递归摧毁红黑树 */
static void _rb_node_destory(rb_node *root)
{
        if (root) {
                _rb_node_destory(root->left);
                _rb_node_destory(root->right);
                free(root); /* 后序摧毁 */
        }
}
void rb_destory(rb_tree *tree)
{
        if (tree)
                _rb_node_destory(tree->root);
}

static void _rb_preorder(rb_node *root)
{
        if (root) {
                printf("%d(%c) ", root->key, rb_is_red(root) ? 'r' : 'b');
                _rb_preorder(root->left);
                _rb_preorder(root->right);
        }
}

/* 前序遍历红黑树 */
void rb_preorder(rb_tree *tree)
{
        if (tree)
                return _rb_preorder(tree->root);
}
/* 中序遍历红黑树 */
void rb_inorder(rb_tree *tree)
{
        /* TO DO */
}
/* 后序遍历红黑树 */
void rb_postorder(rb_tree *tree)
{
        /* TO DO */
}

static void _rb_tojson_levelorder(rb_node* node){
        
        rb_node* t = node;
        while (t)
        {
                
        }
}
void rb_tojson_levelorder(rb_tree* tree){
        printf("[");
        _rb_tojson_levelorder(tree->root);
        printf("]");
}
/* 查询红黑树键最大的节点
   查询成功返回对应节点，失败返回NULL
 */
static rb_node *_rb_node_maximum(rb_node *root)
{
        if (root) {
                rb_node *node = root;
                while (node->right)
                        node = node->right;
                return node;
        } else
                return NULL;
}
rb_node *rb_maximum(rb_tree *tree)
{
        return tree != NULL ? _rb_node_maximum(tree->root) : NULL;
}

/* 查询红黑树键最小的节点
   查询成功返回对应节点，失败返回NULL
 */
static rb_node *_rb_node_minimum(rb_node *root)
{
        if (root) {
                rb_node *node = root;
                while (node->left)
                        node = node->left;
                return node;
        } else
                return NULL;
}
rb_node *rb_minimum(rb_tree *tree)
{
        return tree != NULL ? _rb_node_minimum(tree->root) : NULL;
}

/*      px                              px
*     /                               /
*    x                               y
*   /  \      --(左旋)-->           /   \
*  lx   y                          x     ry     
*     /   \                       / \
*   (ly)  (ry)                (lx)  (ly)
*/
static rb_node *_rb_left_rotate(rb_tree *tree, rb_node *x)
{
        rb_node *px = x->parent;
        rb_node *y = x->right;
        /* 将ly链接到x的右边 */
        x->right = y->left;
        if (y->left)
                y->left->parent = x;
        /* 将x链接到y的左边 */
        if (!px) { /* 若原来x为树的根节点 */
                tree->root = y;
        } else {
                if (x == px->left) /* 将y链接到px相应的子节点上 */
                        px->left = y;
                else
                        px->right = y;
        }
        y->parent = px;
        y->left = x;
        x->parent = y;
        return y; /* 返回当前的相对根节点 */
}
/* 与左旋转成镜像对称 */
static rb_node *_rb_right_rotate(rb_tree *tree, rb_node *x)
{
        rb_node *px = x->parent;
        rb_node *y = x->left;
        /* 将ly链接到x的右边 */
        x->left = y->right;
        if (y->right)
                y->right->parent = x;
        /* 将x链接到y的左边 */
        if (!px) { /* 若原来x为树的根节点 */
                tree->root = y;
        } else {
                if (x == px->left) /* 将y链接到px相应的子节点上 */
                        px->left = y;
                else
                        px->right = y;
        }
        y->parent = x->parent;
        y->right = x;
        x->parent = y;
        return x; /* 返回当前的相对根节点 */
}
/* 将键插入对应红黑树中
   插入成功返回1，失败返回0
 */
static void _rb_insert_fixup(rb_tree *tree, rb_node *node)
{
        rb_node *parent;
        /* 若父节点存在且父节点为红色的 */
        while ((parent = node->parent) != NULL && rb_is_red(node->parent)) {
                rb_node *grandpa = parent->parent;
                if (grandpa == NULL) /* 若不存祖父节点则直接退出 */
                        break;
                if (parent == grandpa->left) { /* 若父节点为祖父节点的左子节点 */
                        rb_node *uncle = grandpa->right;
                        if (uncle && rb_is_red(uncle)) {
                                /* Case 1 叔叔为红色 */
                                rb_set_black(parent); /* 1.1 改变颜色 */
                                rb_set_black(uncle);
                                rb_set_red(grandpa);
                                node = grandpa; /* 1.2 祖父设置为当前节点 */
                        } else {
                                if (node == parent->right) {
                                        /* case 2. 叔叔为黑色，且当前节点位于父节点右边 */
                                        _rb_left_rotate(tree, parent); /* 2.1 以父节点为支点进行左旋 */
                                        rb_node *tmp = node;           /* 2.2 左旋后，父子节点的位置相互交换 */
                                        node = parent;
                                        parent = tmp; /* 左旋后进入case 3*/
                                }
                                /* case 3. 叔叔为黑色，且当前节点位于父节点左边 */
                                rb_set_black(parent); /* 3.1 颜色改变 */
                                rb_set_red(grandpa);
                                _rb_right_rotate(tree, grandpa); /* 3.2 以祖父节点为支点进行右旋，使得当前的父节点（黑）成为相对根节点 */
                        }
                } else { /* 父节点为祖父节点的右子节点(镜像对称) */
                        rb_node *uncle = grandpa->left;
                        if (uncle && rb_is_red(uncle)) { /* Case 1 叔叔为红色 */
                                rb_set_black(parent);    /* 1.1 改变颜色 */
                                rb_set_black(uncle);
                                rb_set_red(grandpa);
                                node = grandpa; /* 1.2 祖父设置为当前节点 */
                        } else {
                                if (node == parent->left) {             /* case 2. 叔叔为黑色，且当前节点位于父节点左边 */
                                        _rb_right_rotate(tree, parent); /* 2.1 以父节点为支点进行右旋 */
                                        rb_node *tmp = node;            /* 2.2 右旋后，父子节点的位置相互交换 */
                                        node = parent;
                                        parent = tmp; /* 右旋后进入case 3*/
                                }
                                /* case 3. 叔叔为黑色，且当前节点位于父节点左边 */
                                rb_set_black(parent); /* 3.1 颜色改变 */
                                rb_set_red(grandpa);
                                _rb_left_rotate(tree, grandpa); /* 3.2 以祖父节点为支点进行左旋，使得当前的父节点（黑）成为相对根节点 */
                        }
                }
                tree->root->color = BLACK; /* 最后设置根节点的颜色为黑色 */
        }
        rb_set_black(tree->root);
}
static void _rb_node_insert(rb_tree *tree, rb_node *node)
{
        rb_node *t = tree->root;
        rb_node *p = t;                    /* 保存着父节点 */
        while (t && t->key != node->key) { /* 将红黑树类似与一颗二叉查找树进行查找 */
                p = t;
                t = node->key < t->key ? t->left : t->right;
        }
        node->parent = p; /* 设置node的父节点 */
        if (p) {          /* 父节点存在，将器其挂到父节点的相应子节点上 */
                if (node->key < p->key)
                        p->left = node;
                else
                        p->right = node;
        } else { /* 将node设置为tree的根节点 */
                tree->root = node;
        }
        _rb_insert_fixup(tree, node);
}
rb_node *rb_insert(rb_tree *tree, key_type key)
{
        return rb_insert_val(tree, key, key);
}
rb_node *rb_insert_val(rb_tree *tree, key_type key, value_type val)
{
        if (!tree)
                return NULL;
        rb_node *node;
        if ((node = rb_search(tree, key)) != NULL) {
                node->val = val;
                return node;
        } else {
                node = _rb_create_node(key, val, RED, NULL, NULL, NULL);
                _rb_node_insert(tree, node);
                return node;
        }
}

static void _rb_remove_fixup(rb_tree *tree, rb_node *node, rb_node *parent)
{
        rb_node *sibling;

        while ((!node || rb_is_black(node)) && node != tree->root) {
                if (parent->left == node) {
                        sibling = parent->right;
                        if (rb_is_red(sibling)) {
                                // Case 1: x的兄弟w是红色的
                                rb_set_black(sibling);
                                rb_set_red(parent);
                                _rb_left_rotate(tree, parent);
                                sibling = parent->right;
                        }
                        if ((!sibling->left || rb_is_black(sibling->left)) &&
                            (!sibling->right || rb_is_black(sibling->right))) {
                                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                                rb_set_red(sibling);
                                node = parent;
                                parent = rb_parent(node);
                        } else {
                                if (!sibling->right || rb_is_black(sibling->right)) {
                                        // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                                        rb_set_black(sibling->left);
                                        rb_set_red(sibling);
                                        _rb_right_rotate(tree, sibling);
                                        sibling = parent->right;
                                }
                                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                                rb_set_color(sibling, rb_color(parent));
                                rb_set_black(parent);
                                rb_set_black(sibling->right);
                                _rb_left_rotate(tree, parent);
                                node = tree->root;
                                break;
                        }
                } else {
                        sibling = parent->left;
                        if (rb_is_red(sibling)) {
                                // Case 1: x的兄弟w是红色的
                                rb_set_black(sibling);
                                rb_set_red(parent);
                                _rb_right_rotate(tree, parent);
                                sibling = parent->left;
                        }
                        if ((!sibling->left || rb_is_black(sibling->left)) &&
                            (!sibling->right || rb_is_black(sibling->right))) {
                                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                                rb_set_red(sibling);
                                node = parent;
                                parent = rb_parent(node);
                        } else {
                                if (!sibling->left || rb_is_black(sibling->left)) {
                                        // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                                        rb_set_black(sibling->right);
                                        rb_set_red(sibling);
                                        _rb_left_rotate(tree, sibling);
                                        sibling = parent->left;
                                }
                                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                                rb_set_color(sibling, rb_color(parent));
                                rb_set_black(parent);
                                rb_set_black(sibling->left);
                                _rb_right_rotate(tree, parent);
                                node = tree->root;
                                break;
                        }
                }
        }
        if (node)
                rb_set_black(node);
}
static int _rb_node_remove(rb_tree *tree, rb_node *node)
{
        rb_node *child, *parent;
        color_type color;

        // 被删除节点的"左右孩子都不为空"的情况。
        if ((node->left != NULL) && (node->right != NULL)) {
                // 被删节点的后继节点。(称为"取代节点")
                // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
                rb_node *replace = node;
                // 获取后继节点
                replace = replace->right;
                while (replace->left != NULL)
                        replace = replace->left;
                // "node节点"不是根节点(只有根节点不存在父节点)
                if (rb_parent(node)) {
                        if (rb_parent(node)->left == node)
                                rb_parent(node)->left = replace;
                        else
                                rb_parent(node)->right = replace;
                } else
                        // "node节点"是根节点，更新根节点。
                        tree->root = replace;

                // child是"取代节点"的右孩子，也是需要"调整的节点"。
                // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
                child = replace->right;
                parent = rb_parent(replace);
                // 保存"取代节点"的颜色
                color = rb_color(replace);
                // "被删除节点"是"它的后继节点的父节点"
                if (parent == node) {
                        parent = replace;
                } else {
                        // child不为空
                        if (child)
                                rb_set_parent(child, parent);
                        parent->left = child;
                        replace->right = node->right;
                        rb_set_parent(node->right, replace);
                }
                replace->parent = node->parent;
                replace->color = node->color;
                replace->left = node->left;
                node->left->parent = replace;
                if (color == BLACK)
                        _rb_remove_fixup(tree, child, parent);
                free(node);
                return 1;
        }

        if (node->left != NULL)
                child = node->left;
        else
                child = node->right;

        parent = node->parent;
        // 保存"取代节点"的颜色
        color = node->color;

        if (child)
                child->parent = parent;

        // "node节点"不是根节点
        if (parent) {
                if (parent->left == node)
                        parent->left = child;
                else
                        parent->right = child;
        } else
                tree->root = child;

        if (color == BLACK)
                _rb_remove_fixup(tree, child, parent);
        free(node); /* 释放资源 */
        return 1;
}
/* 从红黑树删除对应键值的节点
   删除成功返回1，失败返回0
 */
int rb_remove(rb_tree *tree, key_type key)
{
        rb_node *node;
        if ((node = rb_search(tree, key)) != NULL) {
                _rb_node_remove(tree, node);
                return 1;
        } else { /* 没有查询到该键，返回0 */
                return 0;
        }
}

int main(int argc, const char **argv)
{
        queue* q = queue_create(10);
        queue_push_back(q, 10);
        int arr[] = {10, 40, 491, 124, 101, 30, 60, 2139, 90, 12, 213, 0, 70, 120, 15, 20, 45, 50, 35, 130, 80};
        int len = sizeof(arr) / sizeof(arr[0]);
        rb_tree *tree = rb_create();
        for (int i = 0; i < len; i++) {
                rb_insert(tree, arr[i]);
                printf("Insert: %d, tree: ", arr[i]);
                rb_preorder(tree);
                printf("\n");
        }
        printf("Tree json:\n");
        // rb_tojson(tree);
        printf("\n\n");
        for (int i = 0; i < len; i++) {
                rb_remove(tree, arr[i]);
                printf("Remove: %d, tree: ", arr[i]);
                rb_preorder(tree);
                printf("\n");
        }
        return 0;
}