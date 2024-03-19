/*stack.h -- 栈ADT*/
#ifndef STACK_H_
#define STACK_H_

typedef int Item;
typedef struct node
{
    Item item;
    struct node * next;
} Node;
typedef Node * Stack;

// 判断是否为空，是则返回0值
int Stack_isEmpty(Stack S);
// 创建栈的头指针
void Stack_init(Stack * pS);
// 释放当前栈
void Stack_free(Stack * pS);
// 向栈中添加元素至栈顶
void Stack_push(Stack * pS, Item item);
// 弹出栈顶的元素
Item Stack_pop(Stack * pS);
// 查看当前栈顶的元素
Item Stack_top(Stack S);

#endif