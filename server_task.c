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
    char buf[1024];
    char msg[1024] = {0};
    char uname[NMAX] = {0};   // 存在线用户名

    xie(fd, "连接成功！");

    while (1)
    {
        xie(fd, "登录账号请输1，注册账号请输2：");

        if (du(fd, 0, buf) == -1)
            goto cleanup;

        if (strcmp(buf, "exit") == 0)
            goto cleanup;

        if (strcmp(buf, "1") == 0)
        {
            if (sdenglu(fd, uname) == -1)
                goto cleanup;
            xie(fd, "现在已登录，可以发送消息（@用户名 消息）");

            // 私聊消息循环
            while (1)
            {
                if (du(fd, 0, buf) == -1)
                    goto cleanup;
                if (strcmp(buf, "exit") == 0)
                    break;
                // 检查消息格式
                if (buf[0] == '@')
                {
                    char duixiang[NMAX] = {0};
                    char xiaoxi[MMAX] = {0};
                    // 获取信息格式中空格的位置
                    char *kongge = strchr(buf, ' ');
                    if (kongge == NULL)
                    {
                        xie(fd, "格式错误，请使用 @用户名 消息");
                        continue;
                    }
                    // 获取用户名长度
                    int len = kongge - buf - 1;
                    if (len <= 0 || len >= NMAX)
                    {
                        xie(fd, "用户名长度不合法（1-15字符）");
                        continue;
                    }
                    strncpy(duixiang, buf + 1, len);
                    duixiang[len] = '\0';
                    strcpy(xiaoxi, kongge + 1);

                    // 查找在线用户
                    OnNode *node = onlist.head->next;
                    int found = 0;
                    while (node != NULL)
                    {
                        if (strcmp(node->name, duixiang) == 0)
                        {
                            found = 1;
                            break;
                        }
                        node = node->next;
                    }
                    if (found)
                    {
                        char send_msg[NMAX + MMAX + 10];
                        snprintf(send_msg, sizeof(send_msg), "%s：%s", uname, xiaoxi);
                        xie(node->fd, send_msg);
                    }
                    else
                        xie(fd, "目标用户不在线，消息未缓存");
                }
            }
            break;
        }
        else if (strcmp(buf, "2") == 0)
        {
            szhuce(fd);
            // 注册完成后继续循环，完成登录操作
            continue;
        }
        else
            xie(fd, "请输入有效消息！");
    }

cleanup:
    if (strlen(uname) > 0)
    {
        onlistdel(&onlist, uname);
        printf("用户 %s 已下线\n", uname);
    }
    close(fd);
    return NULL;
}