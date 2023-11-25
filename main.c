#include "TreeVision.h"

int main(){

//  初始化红黑树
    redBlackTree root;
    initRBTree(&root);

    int choice;
    int data;

    while (1) {
        printMenu();
        printf("请选择操作红黑树的功能: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("请输入插入的值: ");
            scanf("%d", &data);
            if (insertNode(&root, data)) printf(ANSI_COLOR_GREEN "%d 插入成功\n" ANSI_COLOR_RESET, data);
            else printf(ANSI_COLOR_RED "%d 已存在, 插入失败\n" ANSI_COLOR_RESET, data);
        } else if (choice == 2) {
            printf("请输入要删除的值: ");
            scanf("%d", &data);
            if (deleteNode(&root, data)) printf(ANSI_COLOR_GREEN "%d 删除成功\n" ANSI_COLOR_RESET, data);
            else printf(ANSI_COLOR_RED "%d 不存在, 删除失败\n" ANSI_COLOR_RESET, data);
        } else if (choice == 3) {
            printf("请输入要搜索的值:  ");
            scanf("%d", &data);
            if (findNode(root, data)) printf(ANSI_COLOR_GREEN "%d 存在于红黑树\n" ANSI_COLOR_RESET, data);
            else printf(ANSI_COLOR_RED "%d 不存在于红黑树\n" ANSI_COLOR_RESET, data);
        } else if (choice == 4) {
            getTreeImg(root);
            printf(ANSI_COLOR_YELLOW "已在当前文件夹生成tree.png文件\n" ANSI_COLOR_RESET);
            fflush(stdout);
        } else if (choice == 5) {
            printf("当前红黑树中值有: ");
            inorderTraversal(root);
            printf("\n");
        } else if (choice == 6) {
            if (isBST(root)) printf(ANSI_COLOR_GREEN "当前二叉树是递增的\n" ANSI_COLOR_RESET);
            else printf(ANSI_COLOR_RED "当前二叉树不是递增的!!!\n" ANSI_COLOR_RESET);
        } else if (choice == 7) {
            if (isRedBlackTree(root)) printf(ANSI_COLOR_GREEN "当前二叉树满足红黑树特性\n" ANSI_COLOR_RESET);
            else printf(ANSI_COLOR_RED "当前二叉树不满足红黑树特性!!!\n" ANSI_COLOR_RESET);
        } else if (choice == 0) {
            printf("退出程序!\n");
            destroyRBTree(&root);
            break;
        } else {
            printf(ANSI_COLOR_RED "无效数字，请选择有效数字!!!\n" ANSI_COLOR_RESET);
        }
    }

    return 0;
}