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
        if (du(fd, 0, buf) == -1)
        {
            close(fd);
            return -1;
        }
        if (strcmp(buf, "登录账号请输1，注册账号请输2：") == 0)
        {
            printf("登录账号请输1，注册账号请输2：");
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);

            if (strcmp(msg, "1") == 0)
            {
                cdenglu(fd);
                break;
            }
            else if (strcmp(msg, "2") == 0)
            {
                czhuce(fd);
                continue;
            }
            else
            {
                printf("%s\n", buf);
            }
        }
        // else if (strcmp(buf, "请输入有效消息，登录账号请输1，注册账号请输2：") == 0)
        //     printf("%s\n", buf);

        // else if (strcmp(buf, "现在已登录，可以发送消息（只是演示）") == 0)
        // {
        //     printf("登录成功，进入消息模式（exit退出）\n");
        //     // 消息循环
        //     while (1)
        //     {
        //         printf("> ");
        //         fgets(msg, sizeof(msg), stdin);
        //         msg[strcspn(msg, "\r\n")] = '\0';
        //         xie(fd, msg);
        //         if (strcmp(msg, "exit") == 0)
        //             break;
        //         if (du(fd, 1, buf) == -1)
        //         {
        //             close(fd);
        //             return -1;
        //         }
        //     }
        //     break;
        // }
        else
        {
            // 其他情况
            printf("%s\n", buf);
        }
    }
    
    close(fd);

    return 0;
}



