# make 是工具，Makefile 是给make工具都的配置文本文件
# make 程序读取当前目录下 Makfile，根据里面写的规则，自动执行编译指令

# 标准规则格式：
# 目标名：依赖文件列表（太长需要换行续写，行末尾加 \）
# 	编译命令（Tab开头）

# 编译服务器
server:my.h server.c onlistinit.c onlistadd.c onlistdel.c offlistinit.c \
offlistadd.c offlistdel.c server_task.c finduser.c szhuce.c du.c xie.c sdenglu.c
	cc server.c onlistinit.c onlistadd.c onlistdel.c offlistinit.c \
offlistadd.c offlistdel.c server_task.c finduser.c szhuce.c du.c xie.c sdenglu.c \
-o server -pthread

# 编译客户端
clinet:my.h clinet.c cdenglu.c czhuce.c du.c xie.c clinet_task.c
	cc clinet.c cdenglu.c czhuce.c du.c xie.c clinet_task.c \
-o clinet -pthread

# 清理编译生成的程序
.PHONY: clean
clean:
	rm -rf server clinet *.o