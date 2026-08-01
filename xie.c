// xie.c
// 向服务器或者客户端发送消息
#include "my.h"

void xie(int fd, char *msg)
{
    int len = strlen(msg);
    int new_len = htonl(len);
    if (write(fd, &new_len, MSG_HEAD_LEN) != MSG_HEAD_LEN)
    {
        perror("发送长度头失败\n");
        return;
    }

    if (len > 0)
    {
        int n = write(fd, msg, len);
        if (n != len)
        {
            perror("发送消息失败\n");
            return;
        }
    }
}