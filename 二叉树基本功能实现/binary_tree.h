#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.h"

#define SIZE_bt 1024

struct bt
{
    char data;
    struct bt *lchild, *rchild;
};

struct bt *PreInBuild(char *pre, char *in);//以先序序列和中序序列构造二叉树
struct bt *LevelInBuild(char *level, char *in);//以层序序列和中序序列构造二叉树
void PreOdTraversal(struct bt *t, char *result);//先序遍历
void InOdTraversal(struct bt *t, char *result);//中序遍历
void PostOdTraversal(struct bt *t, char *result);//后序遍历
void LevelOdTraversal(struct bt *t, char *result);//层序遍历
int Height(struct bt *t);//求二叉树高度
bool IsRootSmallest(struct bt *t);//验证这个二叉树是否具备这样的性质：任何一个子树中的结点集合，树根结点的值总是最小。（按字母序）
struct bt *CopyTree(struct bt *source);//拷贝二叉树
void ExchangeLRChild(struct bt *t);//将二叉树左右子树交换
void DestroyTree(struct bt *t);//销毁二叉树
void Cut(struct bt *t, char x);//删除值为x的节点及其全部子孙

#endif /* __BINARY_TREE_H__ */