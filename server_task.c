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
    strcpy(msg, "连接成功！");
    xie(fd, msg);

    // strcpy(msg, "登录账号请输1，注册账号请输2：");
    // xie(fd, msg);
    while (1)
    {
        if (du(fd, 0, buf) == -1)
        {
            goto cleanup;
        }
        if (strcmp(buf, "exit") == 0)
        {
            goto cleanup;
        }
        if (strncmp(buf, "1", 1) == 0)
        {
printf("4");
            if (sdenglu(fd, uname) == -1)
                goto cleanup;
            break;
        }
        else if (strncmp(buf, "2", 1) == 0)
        {
printf("3\n");
            szhuce(fd);
            strcpy(msg, "登录账号请输1，注册账号请输2：");
            xie(fd, msg);
            continue;
        }
        else
        {
            strcpy(msg, "请输入有效消息：");
            xie(fd, msg);
        }
    }
    // 检查离线消息并补发
    OffNode *off_node = offlist.head->next;
    while (off_node != NULL)
    {
        if (strcmp(off_node->js, uname) == 0)
        {
            char offline_msg[MMAX + NMAX + 20] = {0};
            snprintf(offline_msg, sizeof(offline_msg), "[离线消息] %s: %s", 
                     off_node->fs, off_node->message);
            xie(fd, offline_msg);
            // 删除已发送的离线消息
            offlistdel(&offlist);
        }
        off_node = off_node->next;
    }

    while (1)
    {
        if (du(fd, 0, buf) == -1)
            goto cleanup;
        if (strcmp(buf, "exit") == 0)
            break;
        // 处理私聊消息
        if (buf[0] == '@')
        {
            // 解析目标用户名和消息
            char target[NMAX] = {0};
            char message[MMAX] = {0};
            char *space = strchr(buf, ' ');
            if (space != NULL)
            {
                int len = space - buf - 1;
                if (len < NMAX)
                {
                    strncpy(target, buf + 1, len);
                    target[len] = '\0';
                    strcpy(message, space + 1);
                    // 查找目标用户是否在线
                    OnNode *node = onlist.head->next;
                    int found = 0;
                    while (node != NULL)
                    {
                        if (strcmp(node->name, target) == 0)
                        {
                            found = 1;
                            break;
                        }
                        node = node->next;
                    }
                    if (found)
                    {
                        // 目标在线，直接发送
                        char send_msg[1024] = {0};
                        sprintf(send_msg, "[%s]: %s", uname, message);
                    }
                    else
                    {
                        // 目标离线，缓存消息
                        offlistadd(&offlist, uname, target, message);
                        strcpy(msg, "用户离线，消息已缓存");
                        xie(fd, msg);
                    }
                }
                else
                {
                    strcpy(msg, "用户名长度不合法（1-15个字符）");
                    xie(fd, msg);
                }
            }
            else
            {
                strcpy(msg, "格式错误，请使用 @用户名 消息 格式发送");
                xie(fd, msg);
            }
        }
        else
        {
            strcpy(msg, "请使用 @用户名 消息 格式发送");
            xie(fd, msg);
        }
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