// sdenglu.c
// 用户登录操作（服务器），返回成功或失败
#include "my.h"

int sdenglu(int fd, char *name)
{
    char buf[1024];
    char msg[1024];
    strcpy(msg, "请输入用户名：");
    xie(fd, msg);
    // 遍历已存用户信息
    while (1)
    {
        if (du(fd, 0, buf) == -1)
            return -1;
        int i = 0;
        int found = 0;  // 是否找到用户
        for (; i < unumber; i++)
        {
            if (strcmp(buf, user[i].name) == 0)
            {
                found = 1;
                strcpy(msg, "请输入密码：");
                xie(fd, msg);
                if (du(fd, 0, buf) == -1)
                    return -1;
                if (strcmp(buf, user[i].key) == 0)
                {
                    strcpy(name, user[i].name);
                    onlistadd(&onlist, name);
                    strcpy(msg, "登录成功!\n");
                    xie(fd, msg);
                    return 0;;
                }
                else
                {
                    strcpy(msg, "密码错误!\n");
                    xie(fd, msg);
                    strcpy(msg, "请输入用户名：");
                    xie(fd, msg);
                    break;
                }
            }
        }
        if (!found)
        {
            strcpy(msg, "用户名未注册!\n");
            xie(fd, msg);
            strcpy(msg, "请输入用户名：");
            xie(fd, msg);
        }
    }
}