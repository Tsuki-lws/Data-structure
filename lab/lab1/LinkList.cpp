#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int num;
    struct node *next;
} node;
//初始化
void chushihua(node **L)
{
    *L = (node *)malloc(sizeof(node));
    (*L)->next = NULL;
}
//添加到最后
void addLast(node *L, int num)
{
    node *p = L;
    node *s = (node *)malloc(sizeof(node));

    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = s;
    s->next = NULL;
    s->num = num;
}
//添加到为indexNum的值后
void addIndex(node *L, int num, int indexNum)
{
    node *p = L;
    node *s = (node *)malloc(sizeof(node));

    while (p->next != NULL && p->num != indexNum)
    {
        p = p->next;
    }
    s->next = p->next;
    s->num = num;
    p->next = s;
}
//删除indexNum的值
void deleteIndex(node *L, int indexNum)
{
    node *p = L;
    node *s;
    while (p->next != NULL && p->next->num != indexNum)
    {
        p = p->next;
    }
    s = p->next;
    p->next = p->next->next;
    free(s);
}
void printLinkList(node *L)
{
    node *p = L;
    if (p->next == NULL)
    {
        printf("None\n");
    }
    while (p->next != NULL)
    {
        p = p->next;
        printf("%d ", p->num);
    }
}

int main()
{
    node *L;
    chushihua(&L);
    while (1)
    {
        int indexNum;
        int result = scanf("%d", &indexNum);
        if (result != 1)
            break;
        addLast(L, indexNum);
    }

    char a[10];
    while (fgets(a, sizeof(a), stdin) != NULL)
    {
        // 去掉输入中的换行符
        int len = strlen(a);
        if (len > 0 && a[len - 1] == '\n') {
            a[len - 1] = '\0';
        }
        char *token = strtok(a, " ");
        if(strcmp(token,"add") == 0){
            token = strtok(NULL, " ");
            int indexNum = token[0] - '0';
            token = strtok(NULL, " ");
            int num = token[0] - '0';
            addIndex(L, num, indexNum);
            break;
        }else if(strcmp(token,"delete") == 0) {
            token = strtok(NULL, " ");
            int indexNum = token[0] - '0';
            deleteIndex(L, indexNum);
        }
        getchar();
    }
    printLinkList(L);
}