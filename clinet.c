// // clinet.c
// // 客户端
// #include "my.h"

// int main(int argc, char const *argv[])
// {
//     /* code */
//     return 0;
// }


#include "my.h"

int main(int argc, char const *argv[])
{
    // 协议族：TCP/IP，套接字类型：流 TCP
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    // 服务器地址
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);    // 主机字节序转网络字节序：小端 -> 大端
    // 主机字节序到网络字节序的转换
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);    // 将 "127.0.0.1" 写到 addr.sin_addr

    // 0 成功
    connect(fd, (struct sockaddr *)&addr, sizeof(addr));

    // 读写：业务逻辑、协议规则
    // Telnet
    char buf[1024];

    char msg[1024];
    int n;
    for (int i = 0; i < 2;i++)
    {
        memset(msg, 0, sizeof(msg));
        n = read(fd, msg, sizeof(msg));
        if (n < 0)
        {
            printf("短裤来\n");
            close(fd);
            exit(1);
        }
        printf("%s", msg);
    }

        while (1)
        {
            memset(buf, 0, sizeof(buf));
            // 从标准输入 stdin 获取数据写入 buf
            fgets(buf, sizeof(buf), stdin);
            // 发送，写的长度：字符串大小？buf大小
            write(fd, buf, strlen(buf));

            memset(msg, 0, sizeof(msg));
            n = read(fd, msg, sizeof(msg)-1);
            if (n < 0)
        {
            printf("短裤来\n");
            close(fd);
            exit(1);
        }
        if (strcmp(msg, "ok\n") == 0)
        {
            break;
        }
        printf("%s", msg);

    }

    // 关闭套接字
    close(fd);

    return 0;
}
