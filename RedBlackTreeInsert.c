#include "RedBlackTreeInsert.h"

// 插入后调整代码
void insertFixup(redBlackTree *root, redBlackTree p) {
    // 2.插入节点的父节点为黑色
    while (p->parent != NULL &&
           p->color == RED &&
           p->parent->color == RED) {
        if (p->parent == p->parent->parent->lchild &&
            (p->parent->parent->rchild == NULL ||
            p->parent->parent->rchild->color == BLACK)) {

            // 祖父节点染红
            p->parent->parent->color = RED;
            /* 3.插入节点的父节点为红色,
               叔叔节点为黑色（即为空）,
               LL情况：父节点为祖父节点的左节点，
               插入节点为父节点的左节点 */
            if (p == p->parent->lchild) {
                // 父节点染黑
                p->parent->color = BLACK;
                // 祖父节点右旋
                R_Rotate(root, p->parent->parent);
                /* 4.插入节点的父节点为红色,
                     叔叔节点为黑色（即为空）,
                     RL情况：父节点为祖父节点的左节点，
                     插入节点为父节点的右节点 */
            } else if (p ==p->parent->rchild) {
                // 插入节点染黑
                p->color = BLACK;
                L_Rotate(root, p->parent);
                R_Rotate(root, p->parent);
            }
            break;
        } else if (p->parent == p->parent->parent->rchild &&
                   (p->parent->parent->lchild == NULL
                   || p->parent->parent->lchild->color == BLACK)) {
            // 祖父节点染红
            p->parent->parent->color = RED;
            /* 5.插入节点的父节点为红色,
               叔叔节点为黑色（即为空）,
               RR情况：父节点为祖父节点的右节点，
               插入节点为父节点的右节点 */
            if (p == p->parent->rchild) {
                // 父节点染黑
                p->parent->color = BLACK;
                // 祖父节点左旋
                L_Rotate(root, p->parent->parent);
                /* 6.插入节点的父节点为红色,
                   叔叔节点为黑色（即为空）,
                   RL情况：父节点为祖父节点的右节点，
                   插入节点为父节点的左节点 */
            } else if (p == p->parent->lchild) {
                // 插入节点染黑
                p->color = BLACK;
                R_Rotate(root, p->parent);
                L_Rotate(root, p->parent);
            }
            break;
        } else {
            // 7.插入节点的父节点为红色, 叔叔节点为红色
            // 父节点叔叔节点染黑，祖父节点染红
            p->parent->parent->lchild->color = BLACK;
            p->parent->parent->rchild->color = BLACK;
            if (p->parent->parent->parent != NULL)
                p->parent->parent->color = RED;
            p = p->parent->parent;
        }
    }
}

// 插入节点
Status insertNode(redBlackTree *root, RBTElemType data) {
    // node: 需插入节点  cur: 当前节点  last: 当前节点的上一节点
    redBlackTree node, cur, last;
    node = createNode(data);

    // 1.只有根节点的情况下，将根节点改为黑色
    if (*root == NULL) {
        node->color = BLACK;
        *root = node;
        return OK;
    }

    // 找到插入节点的父节点
    cur = *root;
    while (cur != NULL) {
        last = cur;
        // 插入值已存在，插入失败
        if (cur->data == data) return ERROR;
        else if (cur->data > data) cur = cur->lchild;
        else cur = cur->rchild;
    }
    if (last->data > data) last->lchild = node;
    else last->rchild = node;

    node->parent = last;

    insertFixup(root, node);
    return OK;    // 插入成功
}