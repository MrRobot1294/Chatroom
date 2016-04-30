#include "../../include/my_head.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("usage:./server ip\n");
	exit(1);
    }

    pthread_t cli_thread;

    headnode(&online_user);

    int sfd = tcp_init(argv[1], portnumber);

    while(1)
    {
        printf("server waiting...... \n");

        int new_fd = tcp_accept(sfd);

	pthread_create(&cli_thread, NULL, (void *)handle_client, (void *)&new_fd);
    }

    return 0;
}
