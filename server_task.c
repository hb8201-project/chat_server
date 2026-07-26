// server_task.c
// 服务器线程入口函数
/*
功能：
  - 客户端登录，存储用户消息
  - 将用户加入在线用户链表
  - 等待客户端发来的消息
  - 处理离线消息
  - 客户端退出时删除在线用户链表中的用户，关闭c_fd
*/
#include "my.h"

void *server_task(void *p)
{
    int fd = *(int *)p;
    write(fd, "连接成功!\n", strlen("连接成功!\n"));
    sleep(0.1);
    char buf[1024];

    write(fd, "请输入用户名（最大16个字符）：", strlen("请输入用户名（最大16个字符）："));
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        int n = read(fd, buf, (sizeof(buf)) - 1);
        if (n <= 0)
        {
            close(fd);
            pthread_exit(NULL);
        }
        buf[n] = '\0';
        buf[strcspn(buf,"\r\n")] = '\0';

        if (strlen(buf) == 0)
        {
            write(fd, "用户名不能为空，请重新输入：", strlen("用户名不能为空，请重新输入："));
            continue;
        }
        if (strlen(buf) > NMAX)
        {
            write(fd, "超过16个字符，请重新输入：", strlen("超过16个字符，请重新输入："));
            continue;
        }
        if (finduser(buf) == 0)
        {
            strcpy(user[unumber].name, buf);
            unumber++;
            break;
        }
        write(fd, "用户名重复，请重新输入：", strlen("用户名重复，请重新输入："));
    }
 write(fd, "ok\n", strlen("ok\n"));

}