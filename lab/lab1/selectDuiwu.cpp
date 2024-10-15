#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int y;
    int score;
    int id;
    int overYear;
    struct node *next;
} node;

void chushihua(node **L)
{
    *L = (node *)malloc(sizeof(node));
    (*L)->next = NULL;
}

void addLast(node *L, int y, int score, int id, int m)
{
    node *p = L;
    node *s = (node *)malloc(sizeof(node));

    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = s;
    s->next = NULL;
    s->y = y;
    s->id = id;
    s->score = score;
    s->overYear = y + m;
}


int select(node *L, int now) {
    node *p = L;
    int max = 0;
    int returnId = 0;
    while(p->next != NULL) {
        p = p->next;
        if(p->y <= now && p->overYear > now) {
            if(p->score > max) {
                max = p->score;
                returnId = p->id;
            }
        }
    }
    return returnId;
}

int main() {
    /**
     * n-> 队伍数
     * m-> 在役时间
     * a-> 比赛起始年份
     * b-> 比赛结束年份
     */
    int a,m,n,b;
    scanf("%d %d %d %d",&n, &m, &a, &b);
    node *L;
    chushihua(&L);
    for(int i = 0; i < n; i++){
        /**
         * y-> 入学年份
         * score-> 能力评分
         * id-> 队伍编号
         */
        int y,score,id;
        scanf("%d %d %d", &y, &score ,&id);
        addLast(L, y, score, id,m);
    }
    for(int startYear = a; startYear <= b; startYear++) {
        int id = select(L,startYear);
        printf("%d\n",id);
    }
}