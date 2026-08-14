// offlistadd.c
// 离线消息添加
// 1. 离线消息链表
// 2. 发送者
// 3. 接收者
// 4. 消息内容
#include "my.h"

void offlistadd(OffList *l, char *c1, char *c2, char *c3)
{
    OffNode *node = malloc(sizeof(OffNode));
    if (node == NULL)
    {
        perror("离线消息节点分配失败\n");
        return;
    }
    strcpy(node->fs, c1);
    strcpy(node->js, c2);
    strcpy(node->message, c3);
    node->next = NULL;
    l->r->next = node;
    l->r = node;

    return;
}