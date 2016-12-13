#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <winsock2.h>
//#pragma comment(lib,"Ws2_32.lib")
#include <windows.h>

#define BUF_SZ 2048

char in_buf[BUF_SZ];

struct ip_address {
    unsigned char ip1;
	unsigned char ip2;
	unsigned char ip3;
	unsigned char ip4;
};

struct ip_address get_ip(char *hex_num) {
	struct ip_address ip;
	ip.ip1 = (unsigned)*hex_num;
	ip.ip2 = (unsigned)*(hex_num + 1);
 	ip.ip3 = (unsigned)*(hex_num + 2);
	ip.ip4 = (unsigned)*(hex_num + 3);
	return ip;
}

void hex_print(char *buf, int len) {
	const int width = 16;
	int i;
	for (i = 0; i < len; ++i) {
		printf("%02hhx%c", buf[i], ((i+1) % width == 0) ? '\n' : ' ');
	}

	if ((len % width) != 0) {
		putchar('\n');
	}
	putchar('\n');
}

void check_winsock(int arg)
{
    if (arg == SOCKET_ERROR)
	{
           printf ("WSAStartup() failed: %ld\n", GetLastError ());
           return 1;
	}
    printf("Winsock initialised\n");
}

void check_socket(int arg)
{
    if (arg == INVALID_SOCKET)
    {
        printf("Can't open socket: %ld\n", GetLastError());
        WSACleanup();
        return 1;
    }
    printf("RAW socket created\n");
}

int main()
{
    WSADATA WsaData;
    int err = WSAStartup (MAKEWORD(2, 2), &WsaData);
	check_winsock(err);
	int raw_sock = WSASocket(AF_INET, SOCK_RAW, IPPROTO_RAW, NULL, 0, 0); //socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	check_socket(raw_sock);
	int read_cnt;
	while (0 < (read_cnt = read(raw_sock, in_buf, BUF_SZ)))
    {
        hex_print(in_buf, read_cnt);
	}
	return 0;
}
