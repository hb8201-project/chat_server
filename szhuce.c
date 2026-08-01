// szhuce.c
// 用户账号注册（服务器）
#include "my.h"

void szhuce(int fd)
{
    char buf[1024];
    char msg[1024];
    if (unumber >= UMAX)
    {
        xie(fd, "服务器用户已满，注册失败！");
        return;
    }

    xie(fd, "请设置用户名（最大16个字符）：");
    while (1)
    {
        if(du(fd, 0, buf) == -1)
            return ;

        if (strlen(buf) == 0)
        {
            xie(fd, "用户名不能为空，请重新输入：");
            continue;
        }
        if (strlen(buf) >= NMAX)
        {
            xie(fd, "超过16个字符，请重新输入：");
            continue;
        }
        if (finduser(buf) != 0)
        {
            xie(fd, "用户名重复，请重新输入：");
            continue;
        }
        if (unumber >= UMAX)
        {
            xie(fd, "服务器用户已满，注册失败！");
            return;
        }
        strcpy(user[unumber].name, buf);
        break;
    }
    // 密码操作
    xie(fd, "请设置密码（最大8个字符）：");
    while (1)
    {
        if (du(fd, 0, buf) == -1)
            return ;

        if (strlen(buf) == 0)
        {
            xie(fd, "密码不能为空，请重新输入：");
            continue;
        }
        if (strlen(buf) >= KMAX)
        {
            xie(fd, "超过8个字符，请重新输入：");
            continue;
        }
        strcpy(user[unumber].key, buf);
        unumber++;
        break;
    }
    xie(fd, "用户注册成功！");
    return;
}