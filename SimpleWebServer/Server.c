#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <windows.h>
#include <winsock2.h>
#pragma comment(lib,"Ws2_32.lib")

#define MAXCONNECT 10
#define PORT 8000
int main()
{
    WSADATA WsaData;
    int err = WSAStartup (MAKEWORD(1, 1), &WsaData);
	if (err == SOCKET_ERROR)
	{
           printf ("WSAStartup() failed: %ld\n", GetLastError ());
           return 1;
	}

	int s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (s < 0)
    {
		printf("can't open socket");
        return 1;
    }
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (LPSOCKADDR)&sin, sizeof(sin)) == -1)
    {
        close(s);
        printf("can't bind");
        return 1;
   	}
    listen(s, MAXCONNECT);
    SOCKADDR_IN from;
	int fromlen = sizeof(from);
    int client_fd;
    printf("accepted connection from %s, port %d\n", inet_ntoa(from.sin_addr), htons(from.sin_port)) ;
    while (1)
    {
        client_fd = accept(s,(struct sockaddr*)&from, &fromlen);
        printf("got connection\n");
        if (client_fd == -1)
        {
            perror("Can't accept");
            return(1);
        }
        else
        {

        }
    }
    close(client_fd);
    return 0;
}
