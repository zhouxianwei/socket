#include <stdio.h>
#include <winsock2.h>

int initWSADATA() {
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData) != 0;
    if(ret)
        printf("socket网络实例创建失败！");
    return ret;
}


SOCKET initSocket() {
    SOCKET servSoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(servSoc == INVALID_SOCKET)
        printf("socket 打开失败！");
    return servSoc;
}

int main(int argc, char const *argv[]) {
    printf("%d\n", FD_SETSIZE);
    return 0;
}