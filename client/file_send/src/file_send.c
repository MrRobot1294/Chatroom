#include "../../include/my_head.h"

void perror_exit(char *s)
{
    printf(s);
    exit(1);
}

void file_send_read(FILE **file, int new_fd, Link msg)
{
    memset(msg->message, 0, sizeof(msg->message));

    while(NULL != fgets(msg->message, sizeof(msg->message), *file))
    {
	write(new_fd, msg, sizeof(Node));
     
        memset(msg->message, 0, sizeof(msg->message));
    }
}

void file_send(int new_fd)
{
    char str[1024];
    char filename[100];
    FILE *file;

    memset(filename, 0, sizeof(filename));

    Node msg;

    char *wday1[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep);
    
    memset(str, 0, sizeof(str));

    memset(&msg, 0, sizeof(Node));
    msg.action = FILE_SEND;
    msg.online_sfd = msg1.online_sfd;
    msg.state = msg1.state;
    my_strcpy(msg.id, msg1.id);
    my_strcpy(msg.name, msg1.name);
    my_strcpy(msg.password, msg1.password);

    curs_set(1);

    mvwaddstr(ch_window3, 1, 4, "TO       :");
    mvwaddstr(ch_window3, 3, 4, "FILE NAME:");
    mvwaddstr(ch_window3, 4, 4, "FILE PATH:");
    wmove(ch_window3, 1, 15);
    wrefresh(ch_window3);

    echo();
    wscanw(ch_window3, "%s", msg.target_user);
    
    wmove(ch_window3, 3, 15);
    wrefresh(ch_window3);
    
    wscanw(ch_window3, "%s", msg.answer);
    
    wmove(ch_window3, 4, 15);
    wrefresh(ch_window3);
    
    wscanw(ch_window3, "%s", str);
    
    memset(msg.message, 0, sizeof(msg.message));
    //sprintf(msg.message, "%s/%s %s (%d/%d/%d %s %d:%d:%d)\n", msg.name, msg.target_user, msg.answer, (1900+p->tm_year), (1+p->tm_mon), p->tm_mday, wday1[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
 
    //write(new_fd, &msg, sizeof(Node));

    sprintf(filename, "%s%s", str, msg.answer);

    if((file = fopen(filename, "a+")) == NULL)
    {
        perror_exit("open error!");
    }

    file_send_read(&file, new_fd, &msg);

    if(fclose(file) != 0)
    {
        perror_exit("close error!");
    }  

    memset(msg.message, 0, sizeof(msg.message));
    my_strcpy(msg.message, "(end)");
    write(new_fd, &msg, sizeof(Node));

    wprintw(ch_window2, "我 对 %s 发送了文件%s\n", msg.target_user, msg.answer);
    wrefresh(ch_window2);

    mvwaddstr(ch_window3, 1, 4, "                                             ");
    mvwaddstr(ch_window3, 3, 4, "                                             ");
    mvwaddstr(ch_window3, 4, 1, "                                             ");
    wrefresh(ch_window3);
}
