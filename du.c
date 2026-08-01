// du.c
// 从服务器或者客户端读取信息选择是否打印出来 0不打印 1打印,返回是否断开连接
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