#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <winsock2.h>
//#pragma comment(lib,"Ws2_32.lib")
#include <windows.h>

#define MAXCONNECT 5
#define PORT 8000
#define BYTES 1024

void takeAdr(char *dst, char *src)
{
    int i = 5;
    int j = 0;
    while (src[i] != ' ')
    {
        dst[j] = src[i];
        i++;
        j++;
    }
    dst[j] = '\0';
}

void sending(int client_fd)
{
    char mesg[10000];
    int info, bytes_read;
    char data[BYTES], path[10000];
    memset((void*)mesg, (int)'\0', 10000);
    recv(client_fd, mesg, 10000, 0);
    //printf("%s\n", mesg);
    takeAdr(path, mesg);
    if ((info = open(path, O_RDONLY))!= -1 )
    {
        while ((bytes_read = read(info, data, BYTES)) > 0)
        {
            //printf("%d\n",bytes_read);
            send(client_fd, data, bytes_read, 0);
        }
        //printf("%d\n",bytes_read);
    }
    else
    {
        printf("can't found\n");
    }
    closesocket(client_fd);
}

int main()
{
    WSADATA WsaData;
    int err = WSAStartup (MAKEWORD(2, 2), &WsaData);
	if (err == SOCKET_ERROR)
	{
           printf ("WSAStartup() failed: %ld\n", GetLastError ());
           return 1;
	}
//	int s = socket(AF_INET, SOCK_STREAM, 0);
    int s = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0) ;
	if (s == INVALID_SOCKET)
    {
        printf("can't open socket");
        return 1;
    }
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(s, (struct SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR) //(LPSOCKADDR)&sin
    {
        printf("can't bind");
        return 1;
    }
    err = listen(s, MAXCONNECT);
    if (err == SOCKET_ERROR)
    {
        printf("can't listen");
        return 1;
    }
    SOCKADDR_IN from;
	int fromlen = sizeof(from);
    int client_fd;
    printf("accepted connection from %s, port %d\n", inet_ntoa(from.sin_addr), htons(from.sin_port)) ;

    while (1)
    {
        client_fd = accept(s, (struct SOCKADDR*)&from, &fromlen);
        if (client_fd == INVALID_SOCKET)
        {
            printf("can't accept\n");
            return 1;
        }
        else
        {
 //         printf("connected\n");
            sending(client_fd);
        }
    }
    closesocket(s);
    closesocket(client_fd);
    WSACleanup();
    return 0;
}
