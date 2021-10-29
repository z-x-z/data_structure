#include <iostream>
using namespace std;
struct AVLNode;
typedef AVLNode *Position;
typedef AVLNode *AVLTree;

typedef int ElementType;

struct AVLNode {
        ElementType element;
        AVLTree left;
        AVLTree right;
        int height;

        AVLNode(int elementVal) : element(elementVal), left(NULL), right(NULL), height(0) {}

        static int getHeight(AVLTree tree) { return tree != NULL ? tree->height : -1; }

        static void updateHeightFromChildren(AVLTree tree) { tree->height = 1 + max(getHeight(tree->left), getHeight(tree->right)); }

        static AVLTree Insert(ElementType elementVal, AVLTree tree)
        {
                if (tree == NULL) {
                        tree = new AVLNode(elementVal);
                        assert(tree != NULL);
                } else if (elementVal < tree->element) {
                        tree->left = Insert(elementVal, tree->left);
                        if (getHeight(tree->left) - getHeight(tree->right) >= 2) {
                                // LL Rotate
                                if (elementVal < tree->left->element)
                                        tree = LLRotate(tree);
                                else
                                        tree = LRRotate(tree);
                        }
                } else if (elementVal > tree->element) {
                        tree->right = Insert(elementVal, tree->right);
                        if (getHeight(tree->right) - getHeight(tree->left) >= 2) {
                                if (elementVal > tree->right->element)
                                        tree = RRRotate(tree);
                                else
                                        tree = RLRotate(tree);
                        }
                }
                updateHeightFromChildren(tree);
                // tree->height = 1 + max(getHeight(tree->left), getHeight(tree->right));
                return tree;
        }

        // 单旋转会改变树的结构及一些节点的高度，所以需要及时更新newRoot左右节点的高度
        // tree必须有左子节点，而tree左子节点的左子节点不一定存在
        static AVLTree LLRotate(AVLTree tree)
        {
                AVLTree newRoot = tree->left;
                tree->left = newRoot->right;
                newRoot->right = tree;
                if (newRoot->left)
                        updateHeightFromChildren(newRoot->left);
                updateHeightFromChildren(newRoot->right);
                return newRoot;
        }

        static AVLTree RRRotate(AVLTree tree)
        {
                AVLTree newRoot = tree->right;
                tree->right = newRoot->left;
                newRoot->left = tree;
                updateHeightFromChildren(newRoot->left);
                if (newRoot->right)
                        updateHeightFromChildren(newRoot->right);
                return newRoot;
        }

        static AVLTree LRRotate(AVLTree tree)
        {
                tree->left = RRRotate(tree->left);
                return LLRotate(tree);
        }

        static AVLTree RLRotate(AVLTree tree)
        {
                tree->right = LLRotate(tree->right);
                return RRRotate(tree);
        }

        static void postOrder(AVLTree tree)
        {
                if (!tree)
                        return;
                printf("%d ", tree->element);
                postOrder(tree->left);
                postOrder(tree->right);
        }
};

struct AVL {
        AVLTree tree;
        AVL() : tree(NULL) {}
        void Insert(ElementType element)
        {
                tree = AVLNode::Insert(element, tree);
        }

        int getHeight() { return AVLNode::getHeight(tree); }

        void postOrder()
        {
                printf("PostOrder: ");
                AVLNode::postOrder(tree);
        }
};
