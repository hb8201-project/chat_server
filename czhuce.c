// czhuce.c
// 用户账号注册（客户端）
#include "my.h"

void czhuce(int fd)
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
        if (strcmp(buf, "服务器用户已满，注册失败！") == 0)
        {
            printf("服务器用户已满，注册失败！\n");
            close(fd);
            return;
        }
        else if (strcmp(buf, "用户注册成功！\n") == 0 || strcmp(buf, "用户注册成功！") == 0)
        {
            printf("用户注册成功！\n");
            return;
        }
        else if (strcmp(buf, "请设置用户名（最大16个字符）：") == 0)
        {
            printf("请设置用户名（最大16个字符）：");
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);
        }
        else if (strcmp(buf, "请设置密码（最大8个字符）：") == 0)
        {
            printf("请设置密码（最大8个字符）：");
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);
        }
        else
        {
            // 其他情况，可能是提示输入用户名或密码
            printf("%s", buf);
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);
        }

    }
}