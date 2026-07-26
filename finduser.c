// finduser.c
// 查找用户结构体数组是否重复
#include "my.h"

int finduser(char *name)
{
    for (int i = 0; i < unumber; i++)
    {
        if (strcmp(user[i].name, name) == 0)
        {
            return 1;
        }
    }
    return 0;
}