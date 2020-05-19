#include "binary_tree.h"

char traversal_result[SIZE_bt];//用于存储遍历结果

struct bt *PreInBuild(char *pre, char *in)
{
    int in_len;
    char *c, *d;
    char *lin, *rin, *lpre, *rpre;
    struct bt *root;

    root = (struct bt *)malloc(sizeof(struct bt));
    if (root == NULL)
        exit(-1);//内存不足
    root->lchild = NULL;
    root->rchild = NULL;

    if (*pre == '\0' && *in == '\0')
        return NULL;
    if (*pre == '\0' || *in == '\0')
        exit(2);//未知错误
    
    root->data = *pre;
    in_len = strlen(in);//截断in之前先记录其长度
    for (c = in; *c != '\0'; c++)
        if (*c == root->data)//分割左、右子树的中序序列
        {
            *c = '\0';
            break;
        }
    if ((c - in) == in_len)
        exit(1);//中序序列中未出现根节点
    
    lin = in;
    rin = c + 1;
    //拷贝左子树的前序序列
    lpre = (char *)malloc(strlen(lin) + 1);
    d = lpre;
    for (c = pre + 1; (c - pre - 1) < strlen(lin); c++)
        *d++ = *c;
    *d = '\0';
    rpre = c;
    
    root->lchild = PreInBuild(lpre, lin);
    root->rchild = PreInBuild(rpre, rin);

    return root;
}

struct bt *LevelInBuild(char *level, char *in)
{
    int in_len;
    char *c, *d, *e, *f;//遍历字符串需要的指针
    char *lin, *rin, *llevel, *rlevel;
    struct bt *root;

    root = (struct bt *)malloc(sizeof(struct bt));
    if (root == NULL)
        exit(-1);//内存不足
    root->lchild = NULL;
    root->rchild = NULL;

    if (*level == '\0' && *in == '\0')
        return NULL;
    if (*level == '\0' || *in == '\0')
        exit(2);//未知错误

    root->data = *level;
    in_len = strlen(in);//截断in之前先记录其长度
    for (c = in; *c != '\0'; c++)
        if (*c == root->data)
        {
            *c = '\0';
            break;
        }
    if ((c - in) == in_len)
        exit(1);//中序序列中未出现根节点
    
    lin = in;
    rin = c + 1;
    llevel = (char *)malloc(strlen(lin) + 1);
    rlevel = (char *)malloc(strlen(rin) + 1);
    //把层序序列中左子树和右子树的部分按原来的顺序分离开
    d = lin;
    e = llevel;
    f = rlevel;
    for (c = level + 1; *c != '\0'; c++)
    {
        for (d = lin; *d != '\0'; d++)
            if (*d == *c)
            {
                *e++ = *c;
                break;
            }

        if (*d == '\0')
        //说明遍历完左子树的所有元素都没有找到与c相同的元素，说明c在右子树中
            *f++ = *c;
    }
    *e = '\0';
    *f = '\0';
    //分离完毕

    root->lchild = LevelInBuild(llevel, lin);
    root->rchild = LevelInBuild(rlevel, rin);

    return root;
}

static void PreOrder(struct bt *t, char *result, int *p)
{
    if (t == NULL)
        return;
    if (*p == SIZE_bt)
        exit(-1);//储存遍历结果的数组溢出
    
    result[(*p)++] = t->data;
    PreOrder(t->lchild, result, p);
    PreOrder(t->rchild, result, p);
}

void PreOdTraversal(struct bt *t, char *result)
{
    int pos = 0;
    //为了避免函数在递归调用时记录位置信息的变量被反复初始化，需要将递归部分单独写为一个函数
    PreOrder(t, result, &pos);
    result[pos] = '\0';
}

static void InOrder(struct bt *t, char *result, int *p)
{
    if (t == NULL)
        return;
    if (*p == SIZE_bt)
        exit(-1);//储存遍历结果的数组溢出
    
    InOrder(t->lchild, result, p);
    result[(*p)++] = t->data;
    InOrder(t->rchild, result, p);
}

void InOdTraversal(struct bt *t, char *result)
{
    int pos = 0;
    //为了避免函数在递归调用时记录位置信息的变量被反复初始化，需要将递归部分单独写为一个函数
    InOrder(t, result, &pos);
    result[pos] = '\0';
}

static void PostOrder(struct bt *t, char *result, int *p)
{
    if (t == NULL)
        return;
    if (*p == SIZE_bt)
        exit(-1);//储存遍历结果的数组溢出
    
    PostOrder(t->lchild, result, p);
    PostOrder(t->rchild, result, p);
    result[(*p)++] = t->data;
}

void PostOdTraversal(struct bt *t, char *result)
{
    int pos = 0;
    //为了避免函数在递归调用时记录位置信息的变量被反复初始化，需要将递归部分单独写为一个函数
    PostOrder(t, result, &pos);
    result[pos] = '\0';
}

static void LevelOrder(struct bt *t, struct queue *q, char *result, int *p)
{
    struct bt *m;

    InQueue(q, t);

    while (!IsEmptyQueue(q))
    {
        if (*p == SIZE_bt)
            exit(-1);//储存遍历结果的数组溢出

        m = OutQueue(q);
        if (m != NULL)
        {
            result[(*p)++] = m->data;
            InQueue(q, m->lchild);
            InQueue(q, m->rchild);
        }
    }
}

void LevelOdTraversal(struct bt *t, char *result)
{
    int pos = 0;
    struct queue *q;

    q = InitQueue();
    LevelOrder(t, q, result, &pos);
    DestroyQueue(q);
    result[pos] = '\0';
}

int Height(struct bt *t)
{
    int height, lheight, rheight;

    if (t == NULL)
        return 0;
    
    lheight = Height(t->lchild);
    rheight = Height(t->rchild);

    return (lheight > rheight ? lheight : rheight) + 1;
}

static void ChangeRootSmallestFlag(struct bt *t, bool *flag)
{
    if (*flag == false)
        return;
    if (t == NULL)
        return;
    
    if (t->lchild == NULL && t->rchild == NULL)
        return;
    else if (t->lchild == NULL)
    {
        if (t->data > t->rchild->data)
        {
            *flag = false;
            return;
        }
    }
    else if (t->rchild == NULL)
    {
        if (t->data > t->lchild->data)
        {
            *flag = false;
            return;
        }
    }
    else if (t->data > t->lchild->data || t->data > t->rchild->data)
    {
        *flag = false;
        return;
    }

    ChangeRootSmallestFlag(t->lchild, flag);
    ChangeRootSmallestFlag(t->rchild, flag);
}

bool IsRootSmallest(struct bt *t)
{
    bool root_smallest_flag = true;
    ChangeRootSmallestFlag(t, &root_smallest_flag);
    return root_smallest_flag;
}

struct bt *CopyTree(struct bt *source)
{
    //利用源二叉树的先序和中序序列构造目标二叉树，达到拷贝二叉树的目的
    char *pre, *in;
    struct bt *dest;

    PreOdTraversal(source, traversal_result);
    pre = (char *)malloc(strlen(traversal_result) + 1);
    strcpy(pre, traversal_result);

    InOdTraversal(source, traversal_result);
    in = (char *)malloc(strlen(traversal_result) + 1);
    strcpy(in, traversal_result);

    dest = PreInBuild(pre, in);

    free(pre);
    free(in);

    return dest;
}

void ExchangeLRChild(struct bt *t)
{
    struct bt *temp;

    if (t == NULL)
        return;
    
    temp = t->lchild;
    t->lchild = t->rchild;
    t->rchild = temp;

    ExchangeLRChild(t->lchild);
    ExchangeLRChild(t->rchild);
}

void DestroyTree(struct bt *t)
{
    //通过层序遍历销毁二叉树
    struct bt *m;
    struct queue *q;

    q = InitQueue();
    InQueue(q, t);

    while (!IsEmptyQueue(q))
    {
        m = OutQueue(q);
        if (m != NULL)
        {
            InQueue(q, m->lchild);
            InQueue(q, m->rchild);
            free(m);
        }
    }
    DestroyQueue(q);
}

void Cut(struct bt *t, char x)
{
    struct bt *to_destory;

    if (t == NULL)
        return;
    
    if (t->lchild == NULL && t->rchild == NULL)
        return;
    else if (t->lchild == NULL)
    {
        if (t->rchild->data == x)
        {
            to_destory = t->rchild;
            t->rchild = NULL;
            DestroyTree(to_destory);
        }
    }
    else if (t->rchild == NULL)
    {
        if (t->lchild->data == x)
        {
            to_destory = t->lchild;
            t->lchild = NULL;
            DestroyTree(to_destory);
        }
    } 
    else if (t->lchild->data == x)
    {
        to_destory = t->lchild;
        t->lchild = NULL;
        DestroyTree(to_destory);
    }
    else if (t->rchild->data == x)
    {
        to_destory = t->rchild;
        t->rchild = NULL;
        DestroyTree(to_destory);
    }

    Cut(t->lchild, x);
    Cut(t->rchild, x);
}