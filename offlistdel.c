// offlistdel.c
// 离线消息删除(删除链表首个节点)
#include "my.h"

void offlistdel(OffList *l)
{
    OffNode *node = l->head->next;
    if (l->head->next != NULL)
    {
        l->head->next = node->next;
        if (node->next == NULL)
        {
            l->r = l->head;
        }
        free(node);
    }
    return;
}