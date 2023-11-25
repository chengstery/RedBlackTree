#ifndef RBTREE_DEFANDFUN_H
#define RBTREE_DEFANDFUN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ANSI颜色码
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// 函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
typedef int Status;  // 用作函数值类型，表示函数结果状态
typedef int bool;  // 用布尔值类型
typedef int RBTElemType;  // 定义红黑树的元素类型为整型

typedef enum {
    RED,
    BLACK
} Color;

// 红黑树节点结构
typedef struct redBlackNode {
    RBTElemType data;                                // 数据域
    struct redBlackNode
            *parent, *lchild, *rchild;   // 双亲、左、右节点指针域
    Color color;
    // 节点颜色，0表示黑色，1表示红色
} redBlackNode, *redBlackTree;


redBlackTree createNode(RBTElemType data);
void L_Rotate (redBlackTree *root, redBlackTree p);
void R_Rotate (redBlackTree *root, redBlackTree p);
void inorderTraversal(redBlackTree root);
void printnode(redBlackTree node);
void initRBTree(redBlackTree *root);
redBlackTree findNode(redBlackTree root, RBTElemType data);
void inorderTraversal_isBST(redBlackTree root, int* values, int* index);
bool isBST(redBlackTree root);
int checkBlackNodeCount(redBlackNode* root, int currentCount, bool* result);
bool isRedBlackTree(redBlackTree root);
void printMenu();
void freeMemory(redBlackTree *t);
void destroyRBTree(redBlackTree *root);

#endif //RBTREE_DEFANDFUN_H
