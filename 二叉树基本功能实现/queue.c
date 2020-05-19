#include "queue.h"

struct queue *InitQueue(void)
{
    struct queue *q;

    q = (struct queue *)malloc(sizeof(struct queue));
    if (q == NULL)
        exit(-1);//内存不足

    q->front = 0;
    q->rear = 0;
    return q;
}

bool IsEmptyQueue(struct queue *q)
{
    return q->rear == q->front;
}

void InQueue(struct queue *q, datatype data)
{
    if ((q->rear + 1) % SIZE_queue == q->front)
        exit(-2);//上溢

    q->data[q->rear] = data;
    q->rear = (q->rear + 1) % SIZE_queue;
}

datatype OutQueue(struct queue *q)
{
    datatype data;
    if (q->front == q->rear)
        exit(-3);//下溢

    data = q->data[q->front];
    q->front = (q->front + 1) % SIZE_queue;
    return data;
}

datatype FrontQueue(struct queue *q)
{
    if (q->front == q->rear)
        exit(-4);//队空

    return q->data[q->front];
}

void DestroyQueue(struct queue *q)
{
    free(q);
}