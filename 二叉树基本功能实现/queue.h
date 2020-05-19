#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE_queue 1024

typedef void * datatype;

struct queue
{
    datatype data[SIZE_queue];
    int front, rear;
};

struct queue *InitQueue(void);
bool IsEmptyQueue(struct queue *q);
void InQueue(struct queue *q, datatype data);
datatype OutQueue(struct queue *q);
datatype FrontQueue(struct queue *q);
void DestroyQueue(struct queue *q);

#endif /* __QUEUE_H__ */