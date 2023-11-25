#include "TreeVision.h"

int main(){

//  ��ʼ�������
    redBlackTree root;
    initRBTree(&root);

    int choice;
    int data;

    while (1) {
        printMenu();
        printf("��ѡ�����������Ĺ���: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("����������ֵ: ");
            scanf("%d", &data);
            if (insertNode(&root, data)) printf(ANSI_COLOR_GREEN "%d ����ɹ�\n" ANSI_COLOR_RESET, data);
            else printf(ANSI_COLOR_RED "%d �Ѵ���, ����ʧ��\n" ANSI_COLOR_RESET, data);
        } else if (choice == 2) {
            printf("������Ҫɾ����ֵ: ");
            scanf("%d", &data);
            if (deleteNode(&root, data)) printf(ANSI_COLOR_GREEN "%d ɾ���ɹ�\n" ANSI_COLOR_RESET, data);
            else printf(ANSI_COLOR_RED "%d ������, ɾ��ʧ��\n" ANSI_COLOR_RESET, data);
        } else if (choice == 3) {
            printf("������Ҫ������ֵ:  ");
            scanf("%d", &data);
            if (findNode(root, data)) printf(ANSI_COLOR_GREEN "%d �����ں����\n" ANSI_COLOR_RESET, data);
            else printf(ANSI_COLOR_RED "%d �������ں����\n" ANSI_COLOR_RESET, data);
        } else if (choice == 4) {
            getTreeImg(root);
            printf(ANSI_COLOR_YELLOW "���ڵ�ǰ�ļ�������tree.png�ļ�\n" ANSI_COLOR_RESET);
            fflush(stdout);
        } else if (choice == 5) {
            printf("��ǰ�������ֵ��: ");
            inorderTraversal(root);
            printf("\n");
        } else if (choice == 6) {
            if (isBST(root)) printf(ANSI_COLOR_GREEN "��ǰ�������ǵ�����\n" ANSI_COLOR_RESET);
            else printf(ANSI_COLOR_RED "��ǰ���������ǵ�����!!!\n" ANSI_COLOR_RESET);
        } else if (choice == 7) {
            if (isRedBlackTree(root)) printf(ANSI_COLOR_GREEN "��ǰ������������������\n" ANSI_COLOR_RESET);
            else printf(ANSI_COLOR_RED "��ǰ��������������������!!!\n" ANSI_COLOR_RESET);
        } else if (choice == 0) {
            printf("�˳�����!\n");
            destroyRBTree(&root);
            break;
        } else {
            printf(ANSI_COLOR_RED "��Ч���֣���ѡ����Ч����!!!\n" ANSI_COLOR_RESET);
        }
    }

    return 0;
}