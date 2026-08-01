// du.c
// 从服务器或者客户端读取信息选择是否打印出来 0不打印 1打印,返回是否断开连接
#include "my.h"

int du(int fd, int n, char *buf)
{
    int len;
    int a = read(fd, &len, MSG_HEAD_LEN);
    // 断开连接
    if (a <= 0)
    {
        return -1;
    }
    // 读取不完整
    if (a != MSG_HEAD_LEN)
    {
        return -1;
    }
    len = ntohl(len);
    // 空
    if (len == 0)
    {
        buf[0] = '\0';
        return 0;
    }
    // 消息过长
    if (len >= 1024)
    {
        printf("消息过长（不超过1024字节）\n");
        return -1;
    }


    memset(buf, 0, 1024);
    a = read(fd, buf, len);
    if (a <= 0)
    {
        return -1;
    }
    // 字节数不对
    if (a != (int)len)
    {
        return -1;
    }
    buf[a] = '\0';
    if (n)
    {
        printf("%s\n", buf);
    }
    return 0;
}