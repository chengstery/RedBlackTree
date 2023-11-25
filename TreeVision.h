#ifndef RBTREE_TREEVISION_H
#define RBTREE_TREEVISION_H

#include "RedBlackTreeDelete.h"

int generateNullNodeID();
void rbtree_fprint_node(redBlackTree t,FILE *fp);
void rbtree_fprint_tree(redBlackTree t,FILE *fp,bool printNullNode);
void getTreeImg(redBlackTree root);


#endif //RBTREE_TREEVISION_H
