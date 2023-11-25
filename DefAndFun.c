#include "DefAndFun.h"

// ����������ڵ�
redBlackTree createNode(RBTElemType data) {
    redBlackTree node;

    node = (redBlackTree) malloc(sizeof(redBlackNode));
    if (NULL == node) return NULL;       // �ڴ����ʧ��

    node->data = data;
    node->parent = NULL;
    node->lchild = NULL;
    node->rchild = NULL;
    node->color = RED;   // �²���Ľڵ�Ĭ��Ϊ��ɫ

    return node;        // ���ش����Ľڵ�ָ��
}

// ��������
void L_Rotate (redBlackTree *root, redBlackTree p) {
    // prc����ת�ڵ���Һ���
    redBlackTree prc = p->rchild;

    prc->parent = p->parent;

    // �Ƿ���Ҫ�ı��Һ��ӵ�����������
    if (NULL != prc->lchild){
        p->rchild = prc->lchild;
        p->rchild->parent = p;
    } else p->rchild = NULL;

    prc->lchild = p;
    p->parent = prc;

    if (prc->parent == NULL) *root = prc;  // p Ϊ���ڵ�ʱ
    else if(prc->parent->lchild == p) prc->parent->lchild = prc;
    else if(prc->parent->rchild == p) prc->parent->rchild = prc;
}

// ��������
void R_Rotate (redBlackTree *root, redBlackTree p) {
    // plc����ת�ڵ������
    redBlackTree plc = p->lchild;

    plc->parent = p->parent;

    // �Ƿ���Ҫ�ı����ӵ�����������
    if (NULL != plc->rchild){
        p->lchild = plc->rchild;
        p->lchild->parent = p;
    } else p->lchild = NULL;

    plc->rchild = p;
    p->parent = plc;

    if (plc->parent == NULL) *root = plc;   // p Ϊ���ڵ�ʱ
    else if(plc->parent->lchild == p) plc->parent->lchild = plc;
    else if(plc->parent->rchild == p) plc->parent->rchild = plc;
}

// ������������
void inorderTraversal(redBlackTree root) {
    if (root != NULL) {
        inorderTraversal(root->lchild);
        printf("%d ", root->data);  // ��ӡ�ڵ�ֵ
        inorderTraversal(root->rchild);
    }
}

void printnode(redBlackTree node) {
    printf("\ncur:%d ", node->data);
    if (node->parent != NULL) printf("parent:%d ", node->parent->data);
    if (node->lchild != NULL) printf("lchild:%d ", node->lchild->data);
    if (node->rchild != NULL) printf("rchild:%d ", node->rchild->data);
}

// ��ʼһ�����ڵ�
void initRBTree(redBlackTree *root){
    *root = NULL;
}

// ���ҽ��
redBlackTree findNode(redBlackTree root, RBTElemType data){
    // δ�ҵ�����NULL
    if (root == NULL) return NULL;

    // �ҵ���ֱ�ӷ�������ָ��
    if (root->data == data) return root;
    else if(root->data > data) findNode(root->lchild, data);
    else findNode(root->rchild, data);
}

// �����������
void inorderTraversal_isBST(redBlackTree root, int* values, int* index) {
    if (root == NULL) {
        return;
    }

    // �ݹ����������
    inorderTraversal_isBST(root->lchild, values, index);

    // ����ǰ�ڵ�ֵ���浽������
    values[(*index)++] = root->data;

    // �ݹ����������
    inorderTraversal_isBST(root->rchild, values, index);
}

// �ж϶������Ƿ����
bool isBST(redBlackTree root) {
    // �����Ϊ�գ���Ϊ�ǵ�����
    if (root == NULL) {
        return TRUE;
    }

    // ��ȡ����������
    int* values = (int*)malloc(sizeof(int) * 1000); // ���費����1000���ڵ�
    int index = 0;
    inorderTraversal_isBST(root, values, &index);

    // ��������������Ƿ����
    for (int i = 1; i < index; i++) {
        if (values[i] <= values[i - 1]) {
            free(values);
            return FALSE;  // ���ǵ�����
        }
    }

    free(values);
    return TRUE;  // �ǵ�����
}

// �ж��Ƿ��Ǻ����
// ���ڼ��Ӹ��ڵ㵽Ҷ�ӽڵ�ĺ�ɫ�ڵ������Ƿ���ͬ
int checkBlackNodeCount(redBlackNode* root, int currentCount, bool* result) {
    if (root == NULL) {
        // ����Ҷ�ӽڵ㣬���ص�ǰ·���ϵĺ�ɫ�ڵ�����
        return currentCount + 1;
    }

    // �����ǰ�ڵ��Ǻ�ɫ��������ӽڵ�ĺ�ɫ�ڵ������Ƿ���ͬ
    if (root->color == RED &&
       (root->lchild != NULL &&
        root->lchild->color == RED ||
        root->rchild != NULL &&
        root->rchild->color == RED)) {
        *result = FALSE;  // ��ɫ�ڵ㲻���к�ɫ�ӽڵ�
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

    // ������������ĺ�ɫ�ڵ������Ƿ���ͬ
    if (leftCount != rightCount) {
        *result = FALSE;
    }

    return leftCount;  // ���ص�ǰ·���ϵĺ�ɫ�ڵ�����
}

// ���ڼ����������
bool isRedBlackTree(redBlackTree root) {
    if (root == NULL) {
        // ����������������
        return TRUE;
    }

    // ��ʼ����£����ڵ�����Ǻ�ɫ
    if (root->color != BLACK) {
        return FALSE;
    }

    // Ĭ��Ϊ������������
    bool result = TRUE;

    // ���Ӹ��ڵ㵽Ҷ�ӽڵ�ĺ�ɫ�ڵ������Ƿ���ͬ
    checkBlackNodeCount(root, 0, &result);

    return result;
}

void printMenu() {
    printf("\033[1;32m==================== Red-Black Tree ����ѡ�� ====================\n");
    printf("1. \033[1;34m����ڵ�\n");
    printf("2. \033[1;34mɾ���ڵ�\n");
    printf("3. \033[1;34m�����ڵ�\n");
    printf("4. \033[1;34m�����������ӻ�ͼƬ\n");
    printf("5. \033[1;34m����������������Ĺؼ���\n");
    printf("6. \033[1;34m�жϵ�ǰ�������Ƿ����\n");
    printf("7. \033[1;34m�жϵ�ǰ�������Ƿ�������������\n");
    printf("0. \033[1;31m�˳�\n");
    printf("\033[1;32m=================================================================\n\033[0m");
}

// �ͷ��ڴ�
void freeMemory(redBlackTree *t){
    *t = NULL;
    free(*t);
}

void destroyRBTree(redBlackTree *root) {
    if (*root == NULL) {
        return;
    }

    // �ݹ��ͷ�������
    destroyRBTree(&((*root)->lchild));

    // �ݹ��ͷ�������
    destroyRBTree(&((*root)->rchild));

    // �ͷŵ�ǰ�ڵ�
    freeMemory(root);
}


