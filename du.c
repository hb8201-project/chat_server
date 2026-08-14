// du.c
// 从服务器或者客户端读取信息选择是否打印出来
// 1. 文件描述符
// 2. 是否打印读取到的内容 1 打印
// 3. 存放读取内容
#include "my.h"

int du(int fd, int n, char *buf)
{   
    char ch;
    int i = 0;

    // 读取 #
    while (1)
    {
        if (read(fd, &ch, 1) != 1)
            return -1;
        if (ch == '#')
            break;
    }
    // 一直读到\n
    while (1)
    {
        if (read(fd, &ch, 1) != 1)
            return -1;
        if (ch == '\n')
        {
            buf[i] = '\0';
            break;
        }
        if (i < 1023)
            buf[i++] = ch;
    }
    if (n == 1)
        printf("%s\n", buf);

    return 0;
}