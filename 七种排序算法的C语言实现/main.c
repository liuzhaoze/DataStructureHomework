#include "sort.h"

int Compare(const void *p1, const void *p2)
{
    int *a = (int *)p1;
    int *b = (int *)p2;

    if (*a == *b)
        return 0;
    return *a > *b ? 1 : -1;//1:-1升序 -1:1降序
    //返回值等于零：a,b位置不确定
    //返回值大于零：a在b的右边
    //返回值小于零：a在b的左边
}

int main(int argc, char **argv)
{
    int i, n, *R, *answer;
    clock_t start, finish;
    double time;

    if (argc > 1)
        n = atoi(argv[1]);
    else
        n = 3;
    
    R = (int *)malloc(sizeof(int) * n);
    answer = (int *)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)//输入数据
        scanf("%d", &R[i]);
    for (i = 0; i < n; i++)//复制一份数据做参考
        answer[i] = R[i];
    printf("n = %d\n", i);//打印数据数量

    start = clock();
    qsort(answer, n, sizeof(int), Compare);
    finish = clock();
    time = (double)(finish - start) / (double)CLOCKS_PER_SEC;
    printf("%16s: %7.4f\n", "qsort", time);

    //Test("堆排序", R, answer, n, HeapSort);
    //Test("快速排序", R, answer, n, QuickSort);
    //Test("直接插入排序", R, answer, n, DirectInsertionSort);
    //Test("希尔排序", R, answer, n, ShellSort);
    //Test("归并排序", R, answer, n, MergeSort);
    Test("选择排序", R, answer, n, SelectSort);
    //Test("冒泡排序", R, answer, n, BubbleSort);

    return 0;
}
