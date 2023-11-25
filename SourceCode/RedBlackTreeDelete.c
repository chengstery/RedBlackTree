#include "RedBlackTreeDelete.h"

// 删除节点
Status deleteNode(redBlackTree *root, RBTElemType data){
    redBlackTree t, leaf;
    // 获取要删除值的指针
    t = findNode(*root, data);

    // 删除值不存在
    if (t == NULL)
        return ERROR;

    // 将要删除节点替换到叶子节点(左子树的最右节点或右子树的最左节点)
    if (t->lchild != NULL ||
        t->rchild != NULL){
        if (t->lchild != NULL){
            leaf = t->lchild;
            while (leaf->rchild != NULL)
                leaf = leaf->rchild;
        } else{
            leaf = t->rchild;
            while(leaf->lchild != NULL)
                leaf = leaf->lchild;
        }
        t->data = leaf->data;
        leaf->data = data; // 可写可不写，因为最后都会被删去
        t = leaf;
    }

    // 1.删除红色节子点,无影响
    if (t->color == RED) {
        if (t->parent->lchild == t)
            freeMemory(&(t->parent->lchild));
        else
            freeMemory(&(t->parent->rchild));
        // 2.删除黑色节子点 的兄弟节点为红色（根据红黑树定义必有两个黑色子节点）
    }else{
        if (t->parent != NULL){
            // 一个用于删除节点的开关
            bool k = TRUE;
            do{if((t->parent->lchild == t &&
               t->parent->rchild->color == RED) ||
              (t->parent->rchild == t &&
               t->parent->lchild->color == RED)){
                // 删除节点是左子树或右子树情况
                if(t->parent->lchild == t &&
                   t->parent->rchild->color == RED){
                    // 被删节点的兄弟节点染黑，被删节点的兄弟节点的左孩子染红
                    t->parent->rchild->color = BLACK;
                    t->parent->rchild->lchild->color = RED;
                    // 左旋被删节点父节点
                    L_Rotate(root, t->parent);
                    if (k) freeMemory(&(t->parent->lchild));
                } else{
                    // 被删节点的兄弟节点染黑，被删节点的兄弟节点的左孩子染红
                    t->parent->lchild->color = BLACK;
                    t->parent->lchild->rchild->color = RED;
                    // 右旋被删节点父节点
                    R_Rotate(root, t->parent);
                    if (k) freeMemory(&(t->parent->rchild));
                } // 3.删除黑色节子点 的兄弟节点也为黑色 且子节点为黑色。
            } else if((t->parent->lchild == t &&
                      (t->parent->rchild->lchild == NULL ||
                       t->parent->rchild->lchild->color == BLACK) &&
                      (t->parent->rchild->rchild == NULL ||
                       t->parent->rchild->rchild->color == BLACK)) ||
                      (t->parent->rchild == t &&
                      (t->parent->lchild->lchild == NULL ||
                       t->parent->lchild->lchild->color == BLACK) &&
                      (t->parent->lchild->rchild == NULL ||
                       t->parent->lchild->rchild->color == BLACK))){
                // 记住父节点和父节点的开始颜色
                redBlackTree p;
                int pcolor = t->parent->color;
                p = t->parent;
                t->parent->color = BLACK;

                // 删除节点是左子树或右子树情况
                if (t->parent->lchild == t &&
                    t->parent->rchild->lchild == NULL &&
                    t->parent->rchild->rchild == NULL) {
                    t->parent->rchild->color = RED;
                    if (k) freeMemory(&(t->parent->lchild));
                }else{
                    t->parent->lchild->color = RED;
                    if (k) freeMemory(&(t->parent->rchild));
                }

                // 继续循环调整
                if (pcolor == BLACK){
                    k = FALSE;
                    t = p;
                    continue;
                }
                /* 4.删除黑色节子点 的兄弟节点也为黑色
                且有两个子节点（根据红黑树定义这两个子节点为红色）。*/
            }else if((t->parent->lchild == t &&
                      t->parent->rchild->lchild != NULL &&
                      t->parent->rchild->rchild != NULL) ||
                     (t->parent->rchild == t &&
                      t->parent->lchild->lchild != NULL &&
                      t->parent->lchild->rchild != NULL)){
                // 删除节点是左子树或右子树情况
                if(t->parent->lchild == t &&
                   t->parent->rchild->lchild != NULL &&
                   t->parent->rchild->rchild != NULL){
                    // 交换被删节点父节点和兄弟节点的颜色,兄弟节点的右孩子染黑
                    t->parent->rchild->color = t->parent->color;
                    t->parent->rchild->rchild->color = BLACK;
                    L_Rotate(root, t->parent);
                    if (k) freeMemory(&(t->parent->lchild));
                } else{
                    // 交换被删节点父节点和兄弟节点的颜色,兄弟节点的右孩子染黑
                    t->parent->lchild->color = t->parent->color;
                    t->parent->lchild->lchild->color = BLACK;
                    R_Rotate(root, t->parent);
                    if (k) freeMemory(&(t->parent->rchild));
                }
                t->parent->color = BLACK;
            }else{
                // 删除节点是左子树或右子树情况
                /*5.删除黑色节子点 的兄弟节点也为黑色
                且仅有左或右孩子（根据红黑树定义这个孩子节点为红色）。*/
                if(t->parent->lchild == t &&
                   t->parent->rchild->lchild != NULL){
                    // 交换被删节点父节点和兄弟左子节点的颜色
                    t->parent->rchild->lchild->color = t->parent->color;
                    // 右旋被删节点兄弟节点
                    R_Rotate(root, t->parent->rchild);
                    // 左旋被删节点父节点
                    L_Rotate(root, t->parent);
                    if (k) freeMemory(&(t->parent->lchild));
                }else if(t->parent->rchild == t &&
                         t->parent->lchild->lchild != NULL){
                    // 被删节点父节点和兄弟左子节点的颜色染黑
                    // 兄弟节点变成父节点颜色
                    t->parent->lchild->color = t->parent->color;
                    t->parent->lchild->lchild->color = BLACK;
                    // 右旋被删节点父节点
                    R_Rotate(root, t->parent);
                    if (k) freeMemory(&(t->parent->rchild));
                }else if (t->parent->lchild == t &&
                          t->parent->rchild->rchild != NULL){
                    // 被删节点父节点和兄弟右子节点的颜色染黑
                    // 兄弟节点变成父节点颜色
                    t->parent->rchild->color = t->parent->color;
                    t->parent->rchild->rchild->color = BLACK;
                    //
                    L_Rotate(root, t->parent);
                    if (k) freeMemory(&(t->parent->lchild));
                } else if (t->parent->rchild == t &&
                           t->parent->lchild->rchild != NULL){
                    // 交换被删节点父节点和兄弟右子节点的颜色
                    t->parent->lchild->rchild->color = t->parent->color;
                    // 左旋被删节点兄弟节点
                    L_Rotate(root, t->parent->lchild);
                    // 右旋被删节点父节点
                    R_Rotate(root, t->parent);
                    if (k) freeMemory(&(t->parent->rchild));
                }
                t->parent->color = BLACK;
            }
                break;
            }while (t != *root && t->color == BLACK);
            // 4.删除黑色节子点为根节点
        }else freeMemory(root);
    }

    return OK;
}


