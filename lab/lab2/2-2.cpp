// Ackerman函数
// 非递归实现

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

typedef struct stack
{
    int number;
    struct stack *next;
} Stack;
// 栈初始化
Stack *InitStack()
{
    Stack *l = (Stack *)malloc(sizeof(Stack));
    l->next = NULL;
    l->number = 0;
    return l;
}
// 入栈
void push(Stack *l, int number)
{
    Stack *p = (Stack *)malloc(sizeof(Stack));
    p->next = l->next;
    p->number = number;
    l->next = p;
}
// 出栈
void pop(Stack *l)
{
    Stack *p = l->next;
    l->next = p->next;
    free(p);
}
//函数实现
int akm(int m, int n)
{
    Stack *l = InitStack();
    push(l,m);
    push(l,n);
    while (l->next->next != NULL)
    {
        int n = l->next->number;
        pop(l);
        int m = l->next->number;
        pop(l);
        if (m == 0)
        {
            push(l, n + 1);
        }
        if (m != 0 && n == 0)
        {
            push(l, m - 1);
            push(l, 1);
        }
        if (m != 0 && n != 0)
        {
            push(l, m - 1); 
            push(l, m);
            push(l, n - 1);
        }
    }
    int result = l->next->number;
    free(l);
    return result;
}
int main() {
    int m,n;
    cin >> m >> n;
    cout << akm(m,n);
    return 0;
}