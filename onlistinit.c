// onlistinit.c
// 在线用户链表初始化
#include "my.h"

void onlistinit(OnList *l)
{
    l->head = malloc(sizeof(OnNode));
    l->head->next = NULL;
    l->r = l->head;

    return;
}