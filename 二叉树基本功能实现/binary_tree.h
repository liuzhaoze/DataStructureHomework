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

struct bt *PreInBuild(char *pre, char *in);//���������к��������й��������
struct bt *LevelInBuild(char *level, char *in);//�Բ������к��������й��������
void PreOdTraversal(struct bt *t, char *result);//�������
void InOdTraversal(struct bt *t, char *result);//�������
void PostOdTraversal(struct bt *t, char *result);//�������
void LevelOdTraversal(struct bt *t, char *result);//�������
int Height(struct bt *t);//��������߶�
bool IsRootSmallest(struct bt *t);//��֤����������Ƿ�߱����������ʣ��κ�һ�������еĽ�㼯�ϣ���������ֵ������С��������ĸ��
struct bt *CopyTree(struct bt *source);//����������
void ExchangeLRChild(struct bt *t);//��������������������
void DestroyTree(struct bt *t);//���ٶ�����
void Cut(struct bt *t, char x);//ɾ��ֵΪx�Ľڵ㼰��ȫ������

#endif /* __BINARY_TREE_H__ */