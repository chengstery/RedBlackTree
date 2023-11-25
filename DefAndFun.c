#include "DefAndFun.h"

// 创建红黑树节点
redBlackTree createNode(RBTElemType data) {
    redBlackTree node;

    node = (redBlackTree) malloc(sizeof(redBlackNode));
    if (NULL == node) return NULL;       // 内存分配失败

    node->data = data;
    node->parent = NULL;
    node->lchild = NULL;
    node->rchild = NULL;
    node->color = RED;   // 新插入的节点默认为红色

    return node;        // 返回创建的节点指针
}

// 左旋调整
void L_Rotate (redBlackTree *root, redBlackTree p) {
    // prc：旋转节点的右孩子
    redBlackTree prc = p->rchild;

    prc->parent = p->parent;

    // 是否需要改变右孩子的左子树连接
    if (NULL != prc->lchild){
        p->rchild = prc->lchild;
        p->rchild->parent = p;
    } else p->rchild = NULL;

    prc->lchild = p;
    p->parent = prc;

    if (prc->parent == NULL) *root = prc;  // p 为根节点时
    else if(prc->parent->lchild == p) prc->parent->lchild = prc;
    else if(prc->parent->rchild == p) prc->parent->rchild = prc;
}

// 右旋调整
void R_Rotate (redBlackTree *root, redBlackTree p) {
    // plc：旋转节点的左孩子
    redBlackTree plc = p->lchild;

    plc->parent = p->parent;

    // 是否需要改变左孩子的右子树连接
    if (NULL != plc->rchild){
        p->lchild = plc->rchild;
        p->lchild->parent = p;
    } else p->lchild = NULL;

    plc->rchild = p;
    p->parent = plc;

    if (plc->parent == NULL) *root = plc;   // p 为根节点时
    else if(plc->parent->lchild == p) plc->parent->lchild = plc;
    else if(plc->parent->rchild == p) plc->parent->rchild = plc;
}

// 中序遍历红黑树
void inorderTraversal(redBlackTree root) {
    if (root != NULL) {
        inorderTraversal(root->lchild);
        printf("%d ", root->data);  // 打印节点值
        inorderTraversal(root->rchild);
    }
}

void printnode(redBlackTree node) {
    printf("\ncur:%d ", node->data);
    if (node->parent != NULL) printf("parent:%d ", node->parent->data);
    if (node->lchild != NULL) printf("lchild:%d ", node->lchild->data);
    if (node->rchild != NULL) printf("rchild:%d ", node->rchild->data);
}

// 初始一个根节点
void initRBTree(redBlackTree *root){
    *root = NULL;
}

// 查找结点
redBlackTree findNode(redBlackTree root, RBTElemType data){
    // 未找到返回NULL
    if (root == NULL) return NULL;

    // 找到了直接返回所在指针
    if (root->data == data) return root;
    else if(root->data > data) findNode(root->lchild, data);
    else findNode(root->rchild, data);
}

// 中序遍历函数
void inorderTraversal_isBST(redBlackTree root, int* values, int* index) {
    if (root == NULL) {
        return;
    }

    // 递归遍历左子树
    inorderTraversal_isBST(root->lchild, values, index);

    // 将当前节点值保存到数组中
    values[(*index)++] = root->data;

    // 递归遍历右子树
    inorderTraversal_isBST(root->rchild, values, index);
}

// 判断二叉树是否递增
bool isBST(redBlackTree root) {
    // 如果树为空，认为是递增的
    if (root == NULL) {
        return TRUE;
    }

    // 获取中序遍历结果
    int* values = (int*)malloc(sizeof(int) * 1000); // 假设不超过1000个节点
    int index = 0;
    inorderTraversal_isBST(root, values, &index);

    // 检查中序遍历结果是否递增
    for (int i = 1; i < index; i++) {
        if (values[i] <= values[i - 1]) {
            free(values);
            return FALSE;  // 不是递增的
        }
    }

    free(values);
    return TRUE;  // 是递增的
}

// 判断是否是红黑树
// 用于检查从根节点到叶子节点的黑色节点数量是否相同
int checkBlackNodeCount(redBlackNode* root, int currentCount, bool* result) {
    if (root == NULL) {
        // 遇到叶子节点，返回当前路径上的黑色节点数量
        return currentCount + 1;
    }

    // 如果当前节点是红色，检查其子节点的黑色节点数量是否相同
    if (root->color == RED &&
       (root->lchild != NULL &&
        root->lchild->color == RED ||
        root->rchild != NULL &&
        root->rchild->color == RED)) {
        *result = FALSE;  // 红色节点不能有红色子节点
    }

    int leftCount = checkBlackNodeCount(
                    root->lchild,
                    currentCount +
                    (root->color == BLACK),
                    result);
    int rightCount = checkBlackNodeCount(
                    root->rchild,
                    currentCount +
                    (root->color == BLACK),
                    result);

    // 检查左右子树的黑色节点数量是否相同
    if (leftCount != rightCount) {
        *result = FALSE;
    }

    return leftCount;  // 返回当前路径上的黑色节点数量
}

// 用于检查红黑树性质
bool isRedBlackTree(redBlackTree root) {
    if (root == NULL) {
        // 空树满足红黑树性质
        return TRUE;
    }

    // 初始情况下，根节点必须是黑色
    if (root->color != BLACK) {
        return FALSE;
    }

    // 默认为满足红黑树性质
    bool result = TRUE;

    // 检查从根节点到叶子节点的黑色节点数量是否相同
    checkBlackNodeCount(root, 0, &result);

    return result;
}

void printMenu() {
    printf("\033[1;32m==================== Red-Black Tree 功能选择 ====================\n");
    printf("1. \033[1;34m插入节点\n");
    printf("2. \033[1;34m删除节点\n");
    printf("3. \033[1;34m搜索节点\n");
    printf("4. \033[1;34m输出红黑树可视化图片\n");
    printf("5. \033[1;34m中序遍历输出红黑树的关键字\n");
    printf("6. \033[1;34m判断当前二叉树是否递增\n");
    printf("7. \033[1;34m判断当前二叉树是否满足红黑树特性\n");
    printf("0. \033[1;31m退出\n");
    printf("\033[1;32m=================================================================\n\033[0m");
}

// 释放内存
void freeMemory(redBlackTree *t){
    *t = NULL;
    free(*t);
}

void destroyRBTree(redBlackTree *root) {
    if (*root == NULL) {
        return;
    }

    // 递归释放左子树
    destroyRBTree(&((*root)->lchild));

    // 递归释放右子树
    destroyRBTree(&((*root)->rchild));

    // 释放当前节点
    freeMemory(root);
}


