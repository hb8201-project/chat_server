// cdenglu.c
// 用户登录操作（客户端）
#include "my.h"

void cdenglu(int fd)
{
    char buf[1024];
    char msg[1024];
    while (1)
    {
        if (du(fd, 1, buf) == -1)
        {
            close(fd);
            return;
        }
        if (strcmp(buf, "用户名未注册!") == 0 || strcmp(buf, "用户名未注册!\n") == 0)
        {
            printf("用户名未注册，请重新输入：");
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);
        }
        else if (strcmp(buf, "密码错误!") == 0 || strcmp(buf, "密码错误!\n") == 0)
        {
            printf("密码错误，请输入密码：");
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);
        }
        else if (strcmp(buf, "登录成功!") == 0 || strcmp(buf, "登录成功!\n") == 0)
        {
            printf("登录成功！\n");
            return;
        }
        else if (strcmp(buf, "请输入用户名：") == 0 || strcmp(buf, "请输入用户名：\n") == 0)
        {
            printf("请输入用户名：");
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);
        }
        else if (strcmp(buf, "请输入密码：") == 0 || strcmp(buf, "请输入密码：\n") == 0)
        {
            printf("请输入密码：");
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);
        }
        else
        {
            // 其他情况
            printf("服务器：%s\n", buf);
        }
    }
}