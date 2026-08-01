// cdenglu.c
// 用户登录操作（客户端）
#include "my.h"

void cdenglu(int fd)
{
    char buf[1024];
    char msg[1024];
    while (1)
    {
        if (du(fd, 0, buf) == -1)
        {
            close(fd);
            return;
        }
        if (strcmp(buf, "请输入用户名：") == 0)
        {
            printf("请输入用户名：");
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);
        }
        else if (strcmp(buf, "请输入密码：") == 0)
        {
            printf("请输入密码：");
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);
        }
        else if (strcmp(buf, "登录成功!") == 0)
        {
            printf("登录成功！\n");
            return;
        }
        else if (strcmp(buf, "用户名未注册！") == 0 ||
                 strcmp(buf, "密码错误！") == 0 ||
                 strcmp(buf, "该用户已在线！") == 0)
        {
            // 打印错误提示，循环继续
            printf("%s\n", buf);
        }
        else
        {
            // 其他情况
            printf("服务器：%s\n", buf);
        }
    }
}