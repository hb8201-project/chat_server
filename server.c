// server.c
// 服务器
#include "my.h"

User user[UMAX]; // 用户信息
int unumber = 0; // 已存用户数量
OnList onlist; // 在线用户链表
OffList offlist; // 离线消息链表

int main(int argc, char const *argv[])
{
    // TCP套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    // 地址复用
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    // 创建服务器地址
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9000);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // 绑定地址
    bind(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    // 监听
    listen(fd, 9);
    printf("服务器启动\n");

    while (1)
    {
        
    }

    return 0;
}
