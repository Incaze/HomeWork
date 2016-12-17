#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/socket.h>
#include <features.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <netinet/in.h>



#define exit_on_error(expr) do { \
	if (-1 == (expr)) { \
		perror(# expr); \
		exit(1); \
	} \
} while(0)

#define BUF_SZ 2048

char in_buf[BUF_SZ];

void hex_print(char *buf, int len) {
	const int width = 16;
	for (int i = 0; i < len; ++i) {
		printf("%02hhx%c", buf[i], ((i+1) % width == 0) ? '\n' : ' ');
	}

	if ((len % width) != 0) {
		putchar('\n');
	}
	putchar('\n');
}

int bindRawSocketToInterface(char *device, int rawsock, int protocol)
{

	struct sockaddr_ll sll;
	struct ifreq ifr;

	bzero(&sll, sizeof(sll));
	bzero(&ifr, sizeof(ifr));

	strncpy((char *)ifr.ifr_name, device, IFNAMSIZ);
	if((ioctl(rawsock, SIOCGIFINDEX, &ifr)) == -1)
	{
		printf("Error getting Interface index !\n");
		exit(-1);
	}

	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = ifr.ifr_ifindex;
	sll.sll_protocol = htons(protocol);

	if((bind(rawsock, (struct sockaddr *)&sll, sizeof(sll)))== -1)
	{
		perror("can't bind\n");
		exit(-1);
	}

	return 1;

}

parseEthernetHeader(unsigned char *packet, int len)
{
	struct ethhdr *ethernet_header;

	if(len > sizeof(struct ethhdr))
	{
		ethernet_header = (struct ethhdr *)packet;

        printf("Destination MAC: ");
		hex_print(ethernet_header->h_dest, 6);
		printf("\n");

        printf("Source MAC: ");
		hex_print(ethernet_header->h_source, 6);
		printf("\n");

        printf("Protocol: ");
		hex_print((void *)&ethernet_header->h_proto, 2);
		printf("\n");
	}
	else
	{
		printf("Packet size too small\n");
	}
}

parseIpHeader(unsigned char *packet, int len)
{
	struct ethhdr *ethernet_header;
	struct iphdr *ip_header;

	ethernet_header = (struct ethhdr *)packet;

	if(ntohs(ethernet_header->h_proto) == ETH_P_IP)
	{
		if(len >= (sizeof(struct ethhdr) + sizeof(struct iphdr)))
		{
			ip_header = (struct iphdr*)(packet + sizeof(struct ethhdr));

			printf("Destination IP address: %s\n", inet_ntoa(ip_header->daddr));
			printf("Source IP address: %s\n", inet_ntoa(ip_header->saddr));

		}
		else
		{
			printf("IP packet does not have full header\n");
		}

	}
}

parseTcpHeader(unsigned char *packet , int len)
{
	struct ethhdr *ethernet_header;
	struct iphdr *ip_header;
	struct tcphdr *tcp_header;

	if(len >= (sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct tcphdr)))
	{
		ethernet_header = (struct ethhdr *)packet;

		if(ntohs(ethernet_header->h_proto) == ETH_P_IP)
		{
			ip_header = (struct iphdr *)(packet + sizeof(struct ethhdr));

			if(ip_header->protocol == IPPROTO_TCP)
			{
				tcp_header = (struct tcphdr*)(packet + sizeof(struct ethhdr) + ip_header->ihl*4 );

				printf("Source Port: %d\n", ntohs(tcp_header->source));
				printf("Destination Port: %d\n", ntohs(tcp_header->dest));

			}
			else
			{
				printf("Not a TCP packet\n");
			}
		}
		else
		{
			printf("Not an IP packet\n");
		}

	}
	else
	{
		printf("TCP Header not present\n");
	}
}

int main(int argc, char *argv[])
{
	int raw_sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	exit_on_error(raw_sock);

	int read_cnt, len;
	unsigned char packet_buffer[BUF_SZ];
	struct sockaddr_ll packet_info;
	int packet_info_size = sizeof(packet_info);

	while (0 < (read_cnt = read(raw_sock, in_buf, BUF_SZ)))
    {
		hex_print(in_buf, read_cnt);
		if((len = recvfrom(raw_sock, packet_buffer, BUF_SZ, 0, (struct sockaddr*)&packet_info, &packet_info_size)) == -1)
		{
			perror("Recv from returned -1: ");
			exit(-1);
		}
		else
		{
            parseEthernetHeader(packet_buffer, len);
            parseIpHeader(packet_buffer, len);
            parseTcpHeader(packet_buffer, len);
		}
	}
	return 0;
}
