// szhuce.c
// 用户账号注册（服务器）
#include "my.h"

void szhuce(int fd)
{
    char buf[1024];
    char msg[1024];
    if (unumber >= UMAX)
    {
        strcpy(msg, "服务器用户已满，注册失败！");
        xie(fd, msg);
        return;
    }
    strcpy(msg, "请设置用户名（最大16个字符）：");
    xie(fd, msg);
    while (1)
    {
        if(du(fd, 0, buf) == -1)
        {
            return ;
        }

        if (strlen(buf) == 0)
        {
            strcpy(msg, "用户名不能为空，请重新输入：");
            xie(fd, msg);
            continue;
        }
        if (strlen(buf) >= NMAX)
        {
            strcpy(msg, "超过16个字符，请重新输入：");
            xie(fd, msg);
            continue;
        }
        if (finduser(buf) != 0)
        {
            strcpy(msg, "用户名重复，请重新输入：");
            xie(fd, msg);
            continue;
        }
        if (unumber >= UMAX)
        {
            strcpy(msg, "服务器用户已满，注册失败！");
            xie(fd, msg);
            return;
        }
        strcpy(user[unumber].name, buf);
        break;
    }
    // 密码操作
    strcpy(msg, "请设置密码（最大8个字符）：");
    xie(fd, msg);
    while (1)
    {
        if (du(fd, 0, buf) == -1)
        {
            return ;
        }

        if (strlen(buf) == 0)
        {
            strcpy(msg, "密码不能为空，请重新输入：");
            xie(fd, msg);
            continue;
        }
        if (strlen(buf) >= KMAX)
        {
            strcpy(msg, "超过8个字符，请重新输入：");
            xie(fd, msg);
            continue;
        }
        strcpy(user[unumber].key, buf);
        unumber++;
        break;
    }
    strcpy(msg, "用户注册成功！\n");
    xie(fd, msg);
    return;
}