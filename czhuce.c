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
        if (strcmp(buf, "登录账号请输1，注册账号请输2：") == 0 ||
            strcmp(buf, "请设置用户名（最大16个字符）：") == 0 ||
            strcmp(buf, "用户名不能为空，请重新输入：") == 0 ||
            strcmp(buf, "超过16个字符，请重新输入：") == 0 ||
            strcmp(buf, "用户名重复，请重新输入：") == 0 ||
            strcmp(buf, "请设置密码（最大8个字符）：") == 0 ||
            strcmp(buf, "密码不能为空，请重新输入：") == 0 ||
            strcmp(buf, "超过8个字符，请重新输入：") == 0)
        {
            printf("%s", buf);
            fgets(msg, sizeof(msg), stdin);
            msg[strcspn(msg, "\r\n")] = '\0';
            xie(fd, msg);
        }
        else if (strcmp(buf, "用户注册成功！") == 0)
        {
            printf("%s\n", buf);
            return;
        }
        else if (strcmp(buf, "服务器用户已满，注册失败！") == 0)
        {
            printf("%s\n", buf);
            close(fd);
            return;
        }
        else
        {
            // 其他情况，可能是用户名重复
            printf("%s", buf);
        }

    }
}