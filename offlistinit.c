// offlistinit.c
// 离线消息链表初始化
#include "my.h"

void offlistinit(OffList *l)
{
    l->head = malloc(sizeof(OffNode));
    l->head->next = NULL;
    l->r = l->head;

    return;
}