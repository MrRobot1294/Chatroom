#include "../../include/my_head.h"

void change_name(int new_fd)
{
    WINDOW *new_window;
    
    curs_set(1);

    new_window = newwin(3, 14, 1, 5);
    box(new_window, 0, 0);
    mvwaddstr(ch_window5, 3, 6, "         ");
    mvwaddstr(ch_window5, 4, 6, msg1.id);
    
    wrefresh(ch_window5);
    wrefresh(new_window);
    
    wmove(ch_window5, 2, 4);
    wrefresh(ch_window5);
    
    echo();
    wscanw(ch_window5, "%s", msg1.name);

    mvwaddstr(ch_window5, 1, 3, "                ");
    mvwaddstr(ch_window5, 2, 3, "                ");
    mvwaddstr(ch_window5, 3, 3, "                ");
    mvwaddstr(ch_window5, 4, 3, "                ");
    mvwaddstr(ch_window5, 2, 8, msg1.name);
    mvwaddstr(ch_window5, 3, 6, msg1.id);
    wrefresh(ch_window5);
    
    noecho();
    curs_set(0);

    Node msg;

    memset(&msg, 0, sizeof(Node));

    msg.action = CHANGE_NAME;
    my_strcpy(msg.name, msg1.name);
    my_strcpy(msg.id, msg1.id);
    msg.state = msg1.state;

    write(new_fd, &msg, sizeof(Node));
}
