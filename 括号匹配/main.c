#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128

//声明堆栈元素：储存左括号的类型和位置
struct brackets
{
    char ch;
    int position;
};

struct brackets stack[MAX]; //定义栈
int top = 0;                //定义栈顶且初始化
int IsPaired;               //定义配对标志位

void push(char bracket, int pos)
{
    if (top == MAX)
    {
        printf("Stack overflow.\n");
        exit(-2);//上溢
    }
    stack[top].ch = bracket;
    stack[top].position = pos;
    top++;
}

struct brackets pop(void)
{
    if (top == 0)
    {
        printf("Stack underflow.\n");
        exit(-3);//下溢
    }
    return stack[--top];
}

char *MarkInit(int size)//标记字符串初始化函数
{
    char *mark, *p;
    mark = (char *)malloc(sizeof(char) * size);

    for (p = mark; (p - mark) < (size - 1); p++)
        *p = ' ';
    *p = '\0';

    return mark;
}

int DetectMark(char *mark)//检测标记函数
{
    for (; *mark != '\0'; mark++)
    {
        if (*mark == '^')
            return 1;
    }
    return 0;
}

int main(void)
{
    char str[MAX];
    char *mark, *p;
    struct brackets cmp;//用于储存出栈的元素
    
    printf("Enter:\n");
    scanf("%[^\n]", str);
    mark = MarkInit(strlen(str) + 1);//定义标记字符串

    for (p = str; *p != '\0'; p++)
    {
        if (*p == '[' || *p == '(')
            push(*p, p - str);

        if (*p == ')')
        {
            IsPaired = 0;
            while (top > 0)//右圆括号只弹出一个
            {
                cmp = pop();
                if (cmp.ch != '(')
                {
                    push(cmp.ch, cmp.position);//将未匹配的括号（中括号）压回栈中
                    mark[p - str] = '^';//标记此处右括号无配对
                    break;
                }
                else
                {
                    IsPaired = 1;
                    break;
                }
            }
            if (top == 0 && IsPaired == 0)//未找到左圆括号与之匹配
            {
                mark[p - str] = '^';//标记右圆括号
            }
        }

        if (*p == ']')
        {
            IsPaired = 0;
            while(top > 0)
            {
                cmp = pop();
                if (cmp.ch != '[')
                {
                    mark[cmp.position] = '^';//标记中括号内未匹配的圆括号
                }
                else
                {
                    IsPaired = 1;
                    break;
                }
            }
            if (top == 0 && IsPaired == 0)//未找到左中括号与之匹配
            {
                mark[p - str] = '^';//标记右中括号
            }
        }
    }

    while (top != 0)//标记栈中所有未配对的括号
            mark[pop().position] = '^';

    if (DetectMark(mark))
        printf("%s\nNot paired.\n", mark);
    else
        printf("Paired.\n");

    system("pause");
    return 0;
}
