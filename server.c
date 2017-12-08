#include <stdio.h>
#include <winsock2.h>

extern int initWSADATA();
extern SOCKET initSocket();

int main() {

    initWSADATA();

    SOCKET servSoc = initSocket();

    unsigned long ul = 1;
    //设置成非阻塞模式
    int ret = ioctlsocket(servSoc, FIONBIO, (unsigned long *)&ul);
    // if(ret == SOCKET_ERROR) {
    //     printf("设置阻塞模式失败！code: %d\n", WSAGetLastError());
    //     closesocket(servSoc);
    //     WSACleanup();
    //     return 0;
    // }

    struct sockaddr_in addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8888);
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    ret = bind(servSoc, (struct sockaddr *)&addrSrv, sizeof(addrSrv));

    // if(ret == SOCKET_ERROR) {
    //     printf("绑定失败! code:%d \n ", WSAGetLastError());
    //     closesocket(servSoc);
    //     WSACleanup();
    // }

    listen(servSoc, 10);
    struct sockaddr_in clientSoc;

    int len = sizeof(struct sockaddr);
    printf("通话开始，结束请按Ctrl+c\n");
    fd_set rfd, wfd;
    FD_ZERO(&rfd);
    fflush(stdout);
    while(1) {

        // SOCKET sockConn = accept(servSoc, (struct sockaddr *)&clientSoc, &len);

        // if(sockConn == INVALID_SOCKET)
        //     continue;

        // if(FD_ISSET(FD_SETSIZE))

        // char sendBuf[100];
        // sprintf(sendBuf, "欢迎 %s 进入聊天室\n 开始说话\n", inet_ntoa(clientSoc.sin_addr));
        // send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);

        // char recvBuf[100];
        // recv(sockConn, recvBuf, 100, 0);
        // printf("%s\n");

        // while(1) {

        //     char recvBuf[100];
        //     recv(sockConn, recvBuf, 100, 0);

        //     printf("%s 说：%s \n", inet_ntoa(clientSoc.sin_addr), recvBuf);
        //     fflush(stdout);
        //     char talk[100];
        //     printf("请填写内容按回车结束：");
        //     gets(talk);
        //     send(sockConn, talk, strlen(talk) + 1, 0);
        //     printf("\n");
        // }
        // printf("结束与%s通话！", inet_ntoa(clientSoc.sin_addr));
        closesocket(sockConn);

    }

    printf("\n");

    WSACleanup();
}
