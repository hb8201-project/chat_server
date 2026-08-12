// sendofflinemsg.c
// 补发指定用户的离线消息
#include "my.h"

void sendofflinemsg(int fd, char *name)
{
    OffNode *node1 = offlist.head;
    OffNode *node2 = offlist.head->next;
    while (node2 != NULL)
    {
        if (strcmp(node2->js, name) == 0)
        {
            char offline_msg[MMAX + NMAX + 30];
            snprintf(offline_msg, sizeof(offline_msg), "[离线消息]%s：%s", node2->fs, node2->message);
            xie(fd, offline_msg);
            // 删除该节点
            node1->next = node2->next;
            if (node2->next == NULL)
            {
                offlist.r = node1;
            }
            OffNode *node3= node2;
            node2 = node2->next;
            free(node3);
        }
        else
        {
            node1 = node2;
            node2 = node2->next;
        }
    }
}