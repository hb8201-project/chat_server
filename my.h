// my.h
// 头文件
#ifndef MY_H
#define MY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> // 线程
#include <unistd.h> // 读写
#include <sys/socket.h> // 套接字
#include <netinet/in.h> // ip地址
#include <arpa/inet.h> // 大小端转换

#define UMAX 10 // 最大用户数
#define NMAX 16 // 最大用户名长度
#define KMAX 8 // 最大密码长度
#define MMAX 256 // 单次最大离线消息长度

// 存储用户信息
typedef struct 
{
    char name[NMAX - 1]; // 用户名
    int key[KMAX - 1]; // 密码
} User;

// 在线用户节点
typedef struct onnode
{
    char name[NMAX - 1]; // 用户名
    struct onnode *next; // 后继
} OnNode;
// 在线用户链表
typedef struct
{
    OnNode *head; // 头节点
    OnNode *r; // 尾指针
} OnList;


// 离线消息节点
typedef struct offnode
{
    char fs[NMAX - 1]; // 发送方
    char js[NMAX - 1]; // 接收方
    char message[MMAX - 1]; // 消息
    struct offnode *next; // 后继
} OffNode;
// 离线消息链表
typedef struct
{
    OffNode *head; // 头节点
    OffNode *r; // 尾指针
} OffList;

extern User user[UMAX - 1]; // 用户信息
extern int unumber; // 已存用户数量
extern OnList onlist; // 在线用户链表
extern OffList offlist; // 离线消息链表

void onlistinit(OnList *l); // 在线用户链表初始化
void onlistadd(OnList *l, char *n); // 在线用户添加
void onlistdel(OnList *l, char *n); // 在线用户删除(删除指定用户)
void offlistinit(OffList *l); // 离线消息链表初始化
void offlistadd(OffList *l, char *c1, char *c2, char *c3); // 离线消息添加
void offlistdel(OffList *l); // 离线消息删除(删除链表首个节点)
int finduser(char *name); // 查找用户结构体数组是否重复
void *server_task(void *p); // 服务器线程入口函数


#endif