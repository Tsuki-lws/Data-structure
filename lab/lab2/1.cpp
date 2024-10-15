//判断栈的转换
#include<iostream>
#include<cstdio>
#include <vector>

using namespace std;

typedef struct stack {
    int number;
    struct stack *next;
}Stack;
//栈初始化
Stack *InitStack() {
    Stack *l = (Stack *)malloc(sizeof(Stack));
    l->next = NULL;
    l->number = 0;
    return l;
}
//入栈
void push(Stack *l,int number) {
    Stack *p = (Stack *)malloc(sizeof(Stack));
    p->next = l->next;
    p->number = number;
    l->next = p;
}
//出栈
void pull(Stack *l) {
    Stack *p = l->next;
    l->next = p->next;
    free(p);
}
//判断是否符合出栈顺序
bool isValidPop(vector<int> arr1,vector<int> arr2) {
    Stack *l = InitStack();
    int j = 0;  //指向arr2
    for(int i = 0; i < arr1.size(); i++) {
        push(l,arr1[i]);
        while(l->next != NULL && l->next->number == arr2[j]) {
            pull(l);
            j++;
        }
    }
    if(l->next == NULL) {
        return true;
    }
    return false;
}
//主函数
int main() {
    vector<int> arr1, arr2;
    string line;
    getline(cin,line);
    for(int i = 0; i < line.size(); i++) {
        if(line[i] == ' ')
            continue;
        arr1.push_back(line[i] - '0');
    }
    getline(cin,line);
    for(int i = 0; i < line.size(); i++) {
        if(line[i] == ' ')
            continue;
        arr2.push_back(line[i] - '0');
    }
    if(isValidPop(arr1,arr2)) {
        cout << "Yes" ;
        return 0;
    }
    cout << "No";
    return 0;
}
