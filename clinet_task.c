// clinet_task.c
// 客户端入口函数，持续接收服务器信息并打印
#include "my.h"

void *clinet_task(void *p)
{
    Fd clinet_fd = *(Fd *)p;
    char buf[1024];
    while (clinet_fd.running) {
        if (du(clinet_fd.fd, 0, buf) == -1)
        {
            printf("与服务器断开连接\n");
            clinet_fd.running = 0;
            break;
        }
        printf("%s\n", buf);
    }
    return NULL;
}