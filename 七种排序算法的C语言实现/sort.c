#include "sort.h"

void Test(char *prompt, int R[], int answer[], int n, void (*Sort)(int R[], int n))
{
    int i;
    clock_t start, finish;
    double time;

    start = clock();
    Sort(R, n);
    finish = clock();

    time = (double)(finish - start) / (double)CLOCKS_PER_SEC;
    printf("%16s: %7.4f\n", prompt, time);

    for (i = 0; i < n; i++)
    {
        if (R[i] != answer[i])
        {
            printf("ERROR : index %d\n", i);
            exit(i);
        }
    }
}

/**
 * 选择排序
 * 每一趟挑选出最小的元素，与第一个元素交换
 * 第0趟：从n个元素中选择最小的元素与第0个元素交换
 * 第1趟：从n-1个元素中选择最小的元素与第1个元素交换
 * 第n-2趟：从2个元素中选择最小的元素与第n-2个元素交换
 * 排序需要n-1趟
 * 
 * 时间复杂度：最好O(n^2)最坏O(n^2)平均O(n^2)
 * 空间复杂度：O(1)
 * 稳定性：×
 */
void SelectSort(int R[], int n)
{
    int i, j, m;//m为最值的角标

    for (i = 0; i < n; i++)//趟
    {
        //寻找最值
        m = i;
        for (j = i + 1; j < n; j++)
            if (R[j] < R[m])//<升序>降序
                m = j;

        SWAP(R[i], R[m]);
    }
}

/**
 * 堆排序
 * 将数组看成是一棵完全二叉树，按层序序列编号
 * 二叉树的结点满足：结点的值比其左孩子和右孩子的值都大（大顶堆）
 *                  结点的值比其左孩子和右孩子的值都小（小顶堆）
 * 每次将堆顶元素拿出来放在数组末尾
 * 即数组第一个元素与最后一个元素交换
 * 然后调整堆，再把堆顶元素放在倒数第二个位置，以此循环
 * 
 * 时间复杂度：最好O(nlogn)最坏O(nlogn)平均O(nlogn)
 * 空间复杂度：O(1)
 * 稳定性：×
 */
static void HeapAjdust(int R[], int n, int root)
{
    /**
     * 堆调整算法
     * 从根节点开始，查看根节点以及其左右孩子
     * 若根节点最大，则无需调整（以其左右子树都已经调整好为前提）
     * 若左（右）孩子最大，则根节点和左（右）孩子互换
     * 然后以左（右）孩子为根节点再次查看是否调整好
     */
    int temp, i;
    int lchild, rchild, m;//m是左孩子和右孩子中的最值的角标

    temp = R[root];//先拷贝出一份，此时根节点为空
    for (i = root; 2 * i + 1 < n; i = m)//i代表空位
    {
        lchild = 2 * i + 1;
        rchild = lchild + 1;
        
        if (rchild < n && R[rchild] > R[lchild])//>大顶堆，升序<小顶堆，降序
            m = rchild;
        else
            m = lchild;
        
        if (temp > R[m])//>大顶堆，升序<小顶堆，降序
            //此时说明拷贝出的数据满足堆的条件，无需调整，跳出循环
            break;
        
        R[i] = R[m];
    }
    R[i] = temp;//把拷贝出来的填到空位上
}

void HeapSort(int R[], int n)
{
    int i;

    for (i = n / 2 - 1; i >= 0; i--)
    {
        //初始化堆
        //n/2-1是从右往左数第一个有孩子的结点
        //比n/2-1大的结点都是叶子结点，不需要调整
        HeapAjdust(R, n, i);
    }

    for (i = n - 1; i > 0; i--)
    {
        //每一趟把堆顶元素（最大的元素）换到最后，然后调整堆
        SWAP(R[0], R[i]);
        HeapAjdust(R, i, 0);
        //注：从堆顶开始进行调整，所以root是0
        //    需要调整的元素个数不再是n个，而是i个，因为交换后需要调整的元素个数会-1
    }
}

/**
 * 冒泡排序（交换排序的一种）
 * 设有n个元素参加排序
 * 第0趟：从第0个记录开始到第n-2个记录，对n-1对相邻的两个记录关键字进行比较，若与排序要求相逆，则将二者交换。
 * 一趟之后，具有最大关键字的记录交换到了R[n-1]，
 * 第1趟：从第0个记录开始到第n?3个记录继续进行第二趟冒泡。
 * 两趟之后，具有次最大关键字的记录交换到了R[n-2]。
 * 如此重复
 * 
 * 时间复杂度：最好O(n)最坏O(n^2)平均O(n^2)
 * 空间复杂度：O(1)
 * 稳定性：√
 */
void BubbleSort(int R[], int n)
{
    int i, j;

    for (i = n - 1; i > 0; i--)
    {
        //一共走n-1趟
        for (j = 0; j < i; j++)
        {
            //每一趟从前向后比较两个元素，将最大（小）的放到后面
            if (R[j] > R[j + 1])//>升序；<降序
                SWAP(R[j], R[j + 1]);
        }
    }
}

/**
 * 快速排序（交换排序的一种）
 * 首先以第0个元素为“支点”建立划分。比支点小的在左边，比支点大的在右边。
 * 然后分别以划分的左边和右边为整体，在此建立划分。
 * 直到划分为一个元素的时候，数组为有序数组。
 * 注：首先将中间元素和第0个元素交换可以提高对原本有序的数组进行排序的效率
 * 
 * 时间复杂度：最好O(nlogn)最坏O(n^2)平均O(nlogn)
 * 空间复杂度：O(nlogn)
 * 稳定性：×
 */
static int Partition(int R[], int n)
{
    int temp, low = 0, high = n - 1;

    SWAP(R[0], R[n / 2]);//提高对有序序列排序的效率

    temp = R[0];//将第一个元素抄出来，此时原位置为空位置

    while (low < high)
    {
        while (low < high && R[high] > temp)
            high--;//此时high将停留在比temp小的元素的位置
        
        if (low < high)
            R[low++] = R[high];//将high的元素移动到low处，此时high为空位置

        while (low < high && R[low] < temp)
            low++;//此时low将停留在比temp大的元素的位置
        
        if (low < high)
            R[high--] = R[low];//将low的元素移动到high处，此时low为空位置
    }

    //执行到此划分完毕，low = high
    R[low] = temp;

    return low;
}

void QuickSort(int R[], int n)
{
    int k;
    
    if (n < 2)
        return;//划分部分中只有一个元素，无需排序，递归出口

    k = Partition(R, n);//进行划分，k为最后支点的角标

    //对划分左右两部分进行递归快速排序
    QuickSort(R, k);
    QuickSort(&R[k + 1], n - k - 1);
}

/**
 * 直接插入排序
 * 假设有n个元素则一共进行n趟
 * 第i趟表示前i个元素已经排好顺序，将第i+1个元素按顺序插入前i个元素中
 * 
 * 时间复杂度：最好O(n)最坏O(n^2)平均O(n^2)
 * 空间复杂度：O(1)
 * 稳定性：√
 */
void DirectInsertionSort(int R[], int n)
{
    int i, j, temp;

    for (i = 1; i < n; i++)
    {
        //第0号元素已经排好序，从第1号元素开始插入
        temp = R[i];//将已经排好序的序列(共i-1个元素)后面的元素(第i个元素)抄出来

        for (j = i; j > 0; j--)//j为要插入的位置
        {
            if (temp > R[j - 1])//要插入的位置的前一个元素比要插入的元素小，停止移动
                break;

            R[j] = R[j - 1];//元素抄出来之后已经排好序的元素统一向后移动一位
        }

        R[j] = temp;//插入元素
    }
}

/**
 * 希尔排序
 * 
 * 时间复杂度：平均O(n^1.3)
 * 空间复杂度：O(1)
 * 稳定性：×
 */
void ShellSort(int R[], int n)
{
    int tmp, d, i, j, s;
    
    /* 求s=log(n) */
    for (s = 1; (1 << (s + 1)) < n; s++);
    
    /* 增量d序列为: 2的s次方减一(s从log(n)递减到1) */
    for (; s > 0; s--)
    {
        d = (1 << s) - 1;//d为2的s次方减一
        for (i = d; i < n; i++)
        {
            tmp = R[i];
            for (j = i; j >= d; j -= d)
            {
                if (R[j - d] <= tmp)
                    break;
                R[j] = R[j - d];
            }
            R[j] = tmp;
        }               
    }  
}

/**
 * 归并排序
 * 只有1个元素的表总是有序的，所以将排序表R看作是n个长度为1的有序子表。
 * 对相邻的两个有序子表两两合并，使之生成表长2的有序表。
 * 再进行两两合并……
 * 这个过程需要「log2n」趟。
 * src源，dst目标
 * 
 * 时间复杂度：最好O(nlogn)最坏O(nlogn)平均O(nlogn)
 * 空间复杂度：O(n)
 * 稳定性：√
 */
void Merge(int src[], int dst[], int head, int mid, int tail)
{
    /**
     * 函数功能：
     * 将src数组中head到mid；mid到tail两个有序片段
     * 合并成一个有序片段
     * 并储存到dst数组的head到tail处
     */
    int i, j, k;

    i = head;//指向src数组第一个有序序列头
    j = mid;//指向src数组第二个有序序列头
    k = head;//指向dst数组的头

    while (i < mid && j < tail)
    {
        //src两个片段都有数，从两个片段中挑小的放到dst中
        if (src[i] <= src[j])
            dst[k++] = src[i++];
        else
            dst[k++] = src[j++];
    }

    while (i < mid)//只剩下第一个序列有数
        dst[k++] = src[i++];//直接粘贴到dst后面
    
    while (j < tail)//只剩下第二个序列有数
        dst[k++] = src[j++];//直接粘贴到dst后面
}

void MergePass(int src[], int dst[], int len, int n)
{
    /**
     * 函数功能：
     * Merge函数是执行两个片段之间的合并
     * MergePass是执行在一趟操作中，对每对片段分别进行合并
     * len为要合并的片段的长度
     * n为数组的总长度
     */
    int seq1, seq2, tail;

    for (seq1 = 0; seq1 < n; seq1 = tail)
    {
        //从头开始合并片段
        seq2 = (seq1 + len) > n ? n : (seq1 + len);//确定第二个片段的起始位置，超出总长度n就按n算（也是第一个片段的结束位置）
        tail = (seq2 + len) > n ? n : (seq2 + len);//确定第二个片段的结束位置，超出总长度n就按n算
        Merge(src, dst, seq1, seq2, tail);
    }
}

void MergeSort(int R[], int n)
{
    int *temp = (int *)malloc(sizeof(int) * n);
    int len = 1;

    while (len < n)
    {
        /**
         * 每次循环拷贝两次
         * 拷贝过去再拷贝回来
         * 每拷贝一次，片段的长度是原来的2倍
         */
        MergePass(R, temp, len, n);
        len *= 2;
        MergePass(temp, R, len, n);
        len *= 2;
    }
    free(temp);
}