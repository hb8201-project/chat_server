// onlistadd.c
// 在线用户添加
// 1. 在线用户链表
// 2. 用户名
// 3. 套接字描述符
#include "my.h"

void onlistadd(OnList *l, char *n, int fd)
{
    OnNode *node = malloc(sizeof(OnNode));
    if (node == NULL)
    {
        perror("在线用户节点分配失败\n");
        return;
    }
    strcpy(node->name, n);
    node->fd = fd;
    node->next = NULL;
    l->r->next = node;
    l->r = node;

    return ;
}