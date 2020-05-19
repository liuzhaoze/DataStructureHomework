#include <stdio.h>
#include <stdlib.h>

#define m 6  //迷宫实际行数
#define n 8  //迷宫实际列数
#define N (m * n)

//"1"表示迷宫的墙，"0"表示迷宫可走的路，"2"表示已经走过的路
//n+3是为了给'\0'留位置
char maze[m+2][n+3] = {
    "1111111111",
    "1011101101",
    "1101010101",
    "1010110011",
    "1011011011",
    "1100110001",
    "1011101101",
    "1111111111"
};

//声明移动方向结构体
struct Move {int x; int y;};
//定义八个移动方向
struct Move Dir[8] = {
    {0,  1}, { 1,  1}, {1,  0}, { 1, -1},
    {0, -1}, {-1, -1}, {-1, 0}, {-1,  1}
};
//定义八个移动方向的名字，与上面八个移动方向对应
char *DirName[8] = {
    "正东", "东南", "正南", "西南",
    "正西", "西北", "正北", "东北"
};

//声明位置信息结构体，(x, y)表示当前所处位置，dir表示将要去但还没去的方向
struct Location
{
    int x;
    int y;
    int dir;
};
//定义一个以位置信息为元素的栈
struct Location Stack[N];
int top = 0;//定义栈顶
//以下是与堆栈有关的函数
void Push(struct Location t)//入栈
{
    if(top == N)
    {
        printf("Stack overflow!\n");
        exit(-2);//上溢
    }
    Stack[top++] = t;
}

struct Location Pop(void)//出栈
{
    if(top == 0)
    {
        printf("Stack underflow!\n");
        exit(-3);//下溢
    }
    return Stack[--top];
}

int StackIsEmpty(void)//判断栈是否为空
{
    return top == 0;
}

//主函数
int main()
{
    struct Location ToWalk = {1, 1, 0}, next;
    Push(ToWalk);
    //注：压入栈的是要走但还没走的步
    while(!StackIsEmpty())
    {
        ToWalk = Pop();//从栈顶弹出要走的步的信息

        if(ToWalk.dir == 0)//dir=0说明是第一次走这个位置，需要将0置2
        {
            if(maze[ToWalk.x][ToWalk.y] != '0')//要走的位置是墙或者已经走过
                continue;//跳过本次循环
            maze[ToWalk.x][ToWalk.y] = '2';//将0置2，标记已经来到此位置
            if(ToWalk.x == m && ToWalk.y == n)//已经走到迷宫的出口
                exit(0);//0表示走出去了，1表示没走出去
        }

        //来到此位置之后，配置下一个要走的步的参数
        next.x = ToWalk.x + Dir[ToWalk.dir].x;
        next.y = ToWalk.y + Dir[ToWalk.dir].y;
        next.dir = 0;

        if(++ToWalk.dir < 8)//在这个位置的八个方向没有全部尝试完
            Push(ToWalk);//将 当回到该位置时，下一次应该尝试的方向 压入栈中

        Push(next);//把下一步的参数压入栈中
    }

    //栈空代表所有可能都尝试了
    printf("No Path.\n");

    return 1;//0表示走出去了，1表示没走出去
}
