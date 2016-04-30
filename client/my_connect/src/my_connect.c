#include "../../include/my_head.h"

int tcp_connect(char *ip, int port)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sfd == -1)
    {
        perror("socket");
	exit(1);
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(struct sockaddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip);

    if(connect(sfd, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
	close(sfd);
	exit(1);
    }

    return sfd;
}
