#include "TreeVision.h"

// ȫ�ֱ�����������Ψһ��NULL�ڵ��ʶ��
int nullNodeCounter = 0;

// ����Ψһ��NULL�ڵ��ʶ��
int generateNullNodeID() {
    return ++nullNodeCounter;
}

void rbtree_fprint_node(redBlackTree t,FILE *fp){
    if(t->color == BLACK){
        fprintf(fp,"node[shape=record,style=filled,"
                "color=black,fontcolor=white,"
                "fontname=\"Arial\", "
                "fontsize=16];\n");
    }else{
        fprintf(fp,"node[shape=record,style=filled,"
                "color=red,fontcolor=white,"
                "fontname=\"Arial\","
                " fontsize=16];\n");
    }
    fprintf(fp,"%d[label=\"<f0> | <f1> %d | <f2> \"];\n",
            t->data,t->data);
}

void rbtree_fprint_tree(redBlackTree t,FILE *fp,bool printNullNode){
    if(NULL == t) return;
    if(t->parent == NULL){//root
        rbtree_fprint_node(t,fp);
    }

    if(t->lchild != NULL){
        rbtree_fprint_node(t->lchild,fp);
        fprintf(fp,"%d:f0:sw->%d:f1;\n",t->data,t->lchild->data);
    }else {
        if (printNullNode){
            int nullNodeID = generateNullNodeID();
            fprintf(fp, "null%d[label=\"NULL\", "
                        "shape=plaintext,color=black,"
                        "fontcolor=white,"
                        "fontname=\"Arial\", "
                        "fontsize=16];\n", nullNodeID);
            fprintf(fp, "%d:f0:sw->null%d;\n",
                    t->data, nullNodeID);
        }

    }

    if(t->rchild != NULL){
        rbtree_fprint_node(t->rchild,fp);
        fprintf(fp,"%d:f2:se->%d:f1;\n",
                t->data,t->rchild->data);
    }else {
        if (printNullNode){
            int nullNodeID = generateNullNodeID();
            fprintf(fp, "null%d[label=\"NULL\", "
                        "shape=plaintext,color=black,"
                        "fontcolor=white,fontname=\"Arial\", "
                        "fontsize=16];\n", nullNodeID);
            fprintf(fp, "%d:f2:se->null%d;\n",
                    t->data, nullNodeID);
        }
    }

    rbtree_fprint_tree(t->lchild,fp,printNullNode);
    rbtree_fprint_tree(t->rchild,fp,printNullNode);
}

void getTreeImg(redBlackTree root){
    // �������ڽ����ɺ����ͼƬ��.dot�ļ�
    FILE *fp;
    fp = fopen("./tree.dot","w+");
    fprintf(fp,"digraph G{\n");
    rbtree_fprint_tree(root,fp,TRUE);
    fprintf(fp,"}");
    fclose(fp);

    // ִ�� dot ����������ͼ��
    system(".\\Graphviz\\bin\\dot -Tpng ./tree.dot -o ./tree.png");
}

