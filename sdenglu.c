// sdenglu.c
// 用户登录操作（服务器），返回成功或失败
#include "my.h"

int sdenglu(int fd, char *name)
{
    char buf[1024];
    char msg[1024];

    while (1)
    {
        xie(fd, "请输入用户名：");
        if (du(fd, 0, buf) == -1)
            return -1;
        if (strcmp(buf, "exit") == 0)
            return -1;

        int i = 0;
        int found = 0;  // 是否找到用户
        for (; i < unumber; i++)
        {
            if (strcmp(buf, user[i].name) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            xie(fd, "用户名未注册!");
            continue;
        }

        xie(fd, "请输入密码：");
        if (du(fd, 0, buf) == -1)
            return -1;
        if (strcmp(buf, user[i].key) != 0)
        {
            xie(fd, "密码错误!");
            continue;
        }

        // 检查用户是否在在线链表
        OnNode *p = onlist.head->next;
        while (p)
        {
            if (strcmp(p->name, user[i].name) == 0)
            {
                xie(fd, "该用户已在线!");
                break;
            }
            p = p->next;
        }
        // 已登录就重新输入用户名与密码
        if (p)
            continue;
        
        strcpy(name, user[i].name);
        onlistadd(&onlist, name, fd);
        xie(fd, "登录成功!");
        return 0;
    }
}