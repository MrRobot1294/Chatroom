#ifndef _FUNC_H_
#define _FUNC_H_

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <pthread.h>

#define portnumber 8888

#define LOG 1111
#define REGISTER 1112
#define QUIT 1113

#define PRIVATE_CHAT 1114
#define GROUP_CHAT 1115
#define CHECK_CHAT_HISTORY 1116
#define DELETE_CHAT_HISTORY 1117
#define FILE_SEND 1118
#define FILE_SEND_START 1119
#define CHANGE_NAME 1122
#define CHANGE_PASSWORD 1123
#define FORGET_PASSWORD 1124
#define BAN_CHAT 1125
#define QUIT_USER 1126

#define YES 1120
#define NO 1121

#define SUCCESS 1130
#define SUCCESS_ADMIN 1131
#define SUCCESS_BAN 1132

#define SUCCESS_CHANGE_PSD 1139

#define FAILED 1133
#define FAILED_BAN 1134
#define FAILED_ONLINE 1135

#define SUCCESS_OFFLINE 1136
#define FAILED_NOBODY 1137

#define FAILED_CHANGE_PSD 1138

#define ONLINE 1140

#define OFFLINE_MSG 1141

#define SUCCESS_BAN_CHAT 1142
#define FAILED_BAN_CHAT 1143

#define BACKFLAG 1150

#define WRONG_INPUT 1160


struct node
{
    int action;
    int online_sfd;

    int state;
 
    char id[9];
    char name[20];
    char password[20];
    char answer[20];

    char target_user[20];
    char message[100];

    struct node *next;
};

typedef struct node Node;
typedef struct node * Link;

Link newnode;

//Node Msg;

//sqlite3 *db;

Link online_user;

extern void handle_client(void * arg);
extern int tcp_init(char* ip, int port);
extern int tcp_accept(int sfd);
extern void my_register(Link msg, int new_fd);

#endif
