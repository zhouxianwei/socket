#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#include <windows.h>

extern int initWSADATA();
extern SOCKET initSocket();

struct arglist {
    char *message;
} args;

unsigned int __stdcall getServMsg(void *args) {
    struct arglist *als = (struct arglist *)args;
    char *message;
    while(1) {
        gets(message);
        als->message = message;
    }
}

void main() {

    initWSADATA();

    SOCKET sClient = initSocket();

    struct sockaddr_in saServer;

    saServer.sin_family = AF_INET;
    saServer.sin_port = htons(8888);
    saServer.sin_addr.S_un.S_addr = inet_addr("192.168.0.104");

    int ret = connect(sClient, (struct sockaddr *)&saServer, sizeof(struct sockaddr));
    if (ret == SOCKET_ERROR) {
        printf("connect() failed! errorCode: %d\n", WSAGetLastError());
        closesocket(sClient);
        WSACleanup();
        return;
    }

    unsigned long NonBlock = 1;
    if(ioctlsocket(sClient, FIONBIO, &NonBlock) == SOCKET_ERROR) {
        printf("ioctlsocket failed\n");
        return;
    }
    fflush(stdout);
    char recvBuf[100];
    char message;

    //recv(sClient, recvBuf, 100, 0);
    //printf("%s\n", recvBuf);

    fd_set rfd;
    fd_set wfd;
    args.message = "";
    HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, getServMsg, &args, 0, NULL);

    do {
        FD_ZERO(&rfd);
        FD_ZERO(&wfd);
        FD_SET(sClient, &rfd);
        FD_SET(sClient, &wfd);


        ret = select(0, &rfd, &wfd, NULL, NULL);

        if(ret == SOCKET_ERROR) {
            closesocket(sClient);
            break;
        }

        if(ret > 0) {
            if(FD_ISSET(sClient, &rfd)) {
                if(recv(sClient, recvBuf, 100, 0) == SOCKET_ERROR) {
                    printf("connect failed! \n");
                    break;
                }
                printf("server recv:%s\n", recvBuf);
            }

            if(FD_ISSET(sClient, &wfd)) {
                if(strlen(args.message) > 0) {
                    char *msg = args.message;
                    send(sClient, msg, strlen(msg) + 1, 0);
                    args.message = "";
                }
            }
        }
        fflush(stdout);
    } while(1);
    WSACleanup();
}
