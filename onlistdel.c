// onlistdel.c
// 在线用户删除(删除指定用户)
#include "my.h"

void onlistdel(OnList *l, char *n)
{
    OnNode *node1 = l->head;
    OnNode *node2 = node1->next;
    while (node2 != NULL)
    {
        if (strcmp(node2->name, n) == 0)
        {
            node1->next = node2->next;
            if (node2->next == NULL)
            {
                l->r = node1;
            }
            free(node2);
            break;
        }
        node1 = node2;
        node2 = node2->next;
    }

    return;
}