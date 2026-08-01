// clinet.c
// 客户端
#include "my.h"

int main(int argc, char const *argv[])
{
    // TCP套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    // 服务器地址
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr); // 将 "127.0.0.1" 写到 addr.sin_addr
    // 向服务器发起连接
    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        printf("连接发送失败\n");
        close(fd);
        return -1;
    }
    char buf[1024];
    char msg[1024];
    if (du(fd, 1, buf) == -1)
    {
        close(fd);
        return -1;
    }
    while (1)
    {
        printf("登录账号请输1，注册账号请输2：");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\r\n")] = '\0';
        xie(fd, msg);
        if (strncmp(msg, "1", 1) == 0)
        {
printf("4");
            cdenglu(fd);
            break;
        }
        else if (strncmp(msg, "2", 1) == 0)
        {
printf("3");
            czhuce(fd);
            continue;;
        }
        else
        {
            printf("输入无效，请重新输入\n");
        }
    }
    
    close(fd);

    return 0;
}



