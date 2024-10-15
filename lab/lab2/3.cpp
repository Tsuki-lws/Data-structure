// 中缀表达式转后缀表达式

#include <cstdio>
#include <iostream>

using namespace std;

typedef struct stack
{
    char a;
    struct stack *next;
} Stack, Queue, LinkList;
// 栈初始化
Stack *InitStack()
{
    Stack *l = (Stack *)malloc(sizeof(Stack));
    l->next = NULL;
    return l;
}
// 入栈
void pushS(Stack *l, char a)
{
    Stack *p = (Stack *)malloc(sizeof(Stack));
    p->next = l->next;
    p->a = a;
    l->next = p;
}
// 出栈
char pullS(Stack *l)
{
    Stack *p = l->next;
    l->next = p->next;
    char a = p->a;
    free(p);
    return a;
}
// 查看栈顶元素
char top(Stack *l)
{
    if (l->next != NULL)
    {
        return l->next->a;
    }
    return '\0';
}
// 队列初始化
Queue *InitQueue()
{
    Queue *p = (Queue *)malloc(sizeof(Queue));
    p->next = NULL;
    return p;
}
// 入队列
void pushQ(Queue *l, char a)
{
    Queue *p = (Queue *)malloc(sizeof(Queue));
    Queue *q = l;
    while (q->next != NULL)
    {
        q = q->next;
    }
    q->next = p;
    p->a = a;
    p->next = NULL;
}
// 出队列
void pullQ(Queue *l)
{
    Queue *p = l->next;
    l->next = p->next;
    free(p);
}
// 打印元素
void print(LinkList *l)
{
    LinkList *p = l->next;
    while (p != NULL)
    {
        cout << p->a;
        p = p->next;
    }
}

// 判断优先级
int precedence(char a)
{
    switch (a)
    {
    case '(':
    case ')':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return -1;
    }
}
// 前缀表达式转后缀表达式
void conversion(string str)
{
    Stack *l = InitStack();
    Queue *q = InitQueue();
    for (int i = 0; i < str.size(); i++)
    {
        char a = str[i];
        int num = precedence(a);
        if (num == -1)
        {
            pushQ(q, a);
        }
        else if (a == '(')
        {
            pushS(l, a);
        }
        else if (a == ')')
        {
            while (top(l) != '(')
            {
                pushQ(q, pullS(l));
            }
            pullS(l);
        }
        else
        {
            while (l->next != NULL && num <= precedence(l->next->a))
            {
                pushQ(q, pullS(l));
            }
            pushS(l, a);
        }
    }
    while (top(l) != '\0')
    {
        pushQ(q, pullS(l));
    }
    print(q);
    free(l);
    free(q);
}

int main()
{
    string str;
    getline(cin, str);
    conversion(str);
    return 0;
}
