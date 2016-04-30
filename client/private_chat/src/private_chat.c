#include "../../include/my_head.h"

void private_chat(int new_fd)
{
    char str[100];

    Node msg;

    char *wday1[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep);
    
    memset(str, 0, sizeof(str[100]));

    memset(&msg, 0, sizeof(Node));
    msg.action = PRIVATE_CHAT;
    msg.online_sfd = msg1.online_sfd;
    msg.state = msg1.state;
    my_strcpy(msg.id, msg1.id);
    my_strcpy(msg.name, msg1.name);
    my_strcpy(msg.password, msg1.password);

    curs_set(1);

    mvwaddstr(ch_window3, 1, 4, "TO      :");
    mvwaddstr(ch_window3, 3, 4, "MESSAGE :");
    wmove(ch_window3, 1, 14);
    wrefresh(ch_window3);

    echo();
    wscanw(ch_window3, "%s", msg.target_user);
    
    wmove(ch_window3, 3, 14);
    wrefresh(ch_window3);
    
    wscanw(ch_window3, "%s", str);

    sprintf(msg.message, "(%d/%d/%d %s %d:%d:%d): %s", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday, wday1[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec, str);

    wprintw(ch_window2, "我 对 %s %s\n", msg.target_user, msg.message);
    wrefresh(ch_window2);

    write(new_fd, &msg, sizeof(Node));

    mvwaddstr(ch_window3, 1, 4, "                                             ");
    mvwaddstr(ch_window3, 3, 4, "                                             ");
    mvwaddstr(ch_window3, 4, 1, "                                             ");
    wrefresh(ch_window3);
}
