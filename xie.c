// xie.c
// 向服务器或者客户端发送消息
#include "my.h"

void xie(int fd, char *msg)
{
    if (write(fd, "#", 1) != 1)
    {
        perror("#发送失败");
        return;
    }
    int len = strlen(msg);
    if (write(fd, msg, len) != len)
    {
        perror("msg发送失败");
        return;
    }
    if (write(fd, "\n", 1) != 1)
    {
        perror("\n发送失败");
        return;
    }
}