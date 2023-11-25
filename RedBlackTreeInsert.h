#ifndef RBTREE_REDBLACKTREEINSERT_H
#define RBTREE_REDBLACKTREEINSERT_H

#include "DefAndFun.h"

void insertFixup(redBlackTree *root, redBlackTree p);
Status insertNode(redBlackTree *root, RBTElemType data);


#endif //RBTREE_REDBLACKTREEINSERT_H
