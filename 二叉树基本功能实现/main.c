#include "binary_tree.h"

int main()
{
    extern char traversal_result[SIZE_bt];
    char traversal[SIZE_bt], in[SIZE_bt];//traversal为除中序遍历以外的任意遍历
    struct bt *tree1, *tree2;

    printf("Enter level-order traversal:");
    scanf("%s", traversal);
    getchar();
    printf("Enter in-order    traversal:");
    scanf("%s", in);
    getchar();
    putchar('\n');

    tree1 = LevelInBuild(traversal, in);
    tree2 = CopyTree(tree1);
    ExchangeLRChild(tree2);

    printf("Tree 1:\n");
    PreOdTraversal(tree1, traversal_result);
    printf("Pre-order   traversal:%s\n", traversal_result);
    InOdTraversal(tree1, traversal_result);
    printf("In-order    traversal:%s\n", traversal_result);
    PostOdTraversal(tree1, traversal_result);
    printf("Post-order  traversal:%s\n", traversal_result);
    LevelOdTraversal(tree1, traversal_result);
    printf("Level-order traversal:%s\n", traversal_result);
    printf("Height:%d\n", Height(tree1));
    printf("Have quality:%s\n", IsRootSmallest(tree1) ? "YES." : "NO.");

    printf("\nTree 2:\n");
    PreOdTraversal(tree2, traversal_result);
    printf("Pre-order   traversal:%s\n", traversal_result);
    InOdTraversal(tree2, traversal_result);
    printf("In-order    traversal:%s\n", traversal_result);
    PostOdTraversal(tree2, traversal_result);
    printf("Post-order  traversal:%s\n", traversal_result);
    LevelOdTraversal(tree2, traversal_result);
    printf("Level-order traversal:%s\n", traversal_result);

    printf("\nEnter a node to cut:");
    Cut(tree1, getchar());
    printf("Tree 1(after cut):\n");
    PreOdTraversal(tree1, traversal_result);
    printf("Pre-order   traversal:%s\n", traversal_result);
    InOdTraversal(tree1, traversal_result);
    printf("In-order    traversal:%s\n", traversal_result);
    PostOdTraversal(tree1, traversal_result);
    printf("Post-order  traversal:%s\n", traversal_result);
    LevelOdTraversal(tree1, traversal_result);
    printf("Level-order traversal:%s\n", traversal_result);

    DestroyTree(tree1);
    DestroyTree(tree2);

    system("pause");
    return 0;
}
