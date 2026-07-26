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

// 用户名与密码
typedef struct 
{
    char name[16]; // 用户名
    int key[8]; // 密码
} User;

// 在线用户
typedef struct
{
    char name[16]; // 在线用户
} OnlineU;

// 离线消息
typedef struct
{
    char fs[16]; // 发送方
    char js[16]; // 接收方
    char message[256]; // 消息
} Offlinem;

#endif