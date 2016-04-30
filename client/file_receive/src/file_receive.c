#include "../../include/my_head.h"

void file_receive(int new_fd)
{
    int flag = 3;
    int ch;
    
    echo();
    
    mvwprintw(ch_window3, 1, 4, "是否接收 %s?", file_name);
    mvwaddstr(ch_window3, 3, 4, "  是");
    mvwaddstr(ch_window3, 4, 4, "  否");
    
    mvwaddstr(ch_window3, flag, 4, "=>");
    wrefresh(ch_window3);
    
    keypad(ch_window3, true);
    cbreak();

    while(1)
    {
        curs_set(0);

	noecho();
	while((ch = wgetch(ch_window3)) != '\n')
	{
	    if(ch == KEY_UP || ch == KEY_DOWN)
	    {
	        mvwaddstr(ch_window3, flag, 4, "  ");

	        if(flag == 3)
		{
		    flag = 4;
		}
		else
		{
		    flag = 3;
		}
	        mvwaddstr(ch_window3, flag, 4, "=>");
		wrefresh(ch_window3);
	    }
	}
        
        switch(flag)
	{
	    case 3:
	    {
	        curs_set(1);
		echo();

		char filename[50];

		Node msg3;

	        mvwaddstr(ch_window3, 1, 4, "                                          ");
	        mvwaddstr(ch_window3, 3, 4, "                                          ");
	        mvwaddstr(ch_window3, 4, 4, "                                          ");
	
	        mvwaddstr(ch_window3, 2, 4, "保存目录: ");
		wmove(ch_window3, 2, 14);
		wrefresh(ch_window3);

		wscanw(ch_window3, "%s", filename);
	        
		mvwaddstr(ch_window3, 2, 4, "                                          ");
		wrefresh(ch_window3);

		sprintf(filename, "%s%s", filename, file_name);
		
		memset(&msg3, 0, sizeof(Node));
		msg3.action = FILE_SEND_START;
		my_strcpy(msg3.name, file_name);
		my_strcpy(msg3.id, msg1.id);
		my_strcpy(msg3.target_user, filename);

		write(new_fd, &msg3, sizeof(Node));
		
                curs_set(0);
	    }
	    case 4:
	    {
		goto EXIT_FILE_SEND;
	    }
	    default:
	    {
	        break;
	    }
	}
    }

    EXIT_FILE_SEND:
    mvwaddstr(ch_window3, 1, 4, "                                       ");
    mvwaddstr(ch_window3, 3, 4, "                                       "); 
    mvwaddstr(ch_window3, 4, 4, "                                       ");
    wrefresh(ch_window3);
}

void file_receive_write(Link msg)
{
    FILE *file;

    char filename[50];

    memset(filename, 0, sizeof(filename));
    my_strcpy(filename, msg->target_user);

    if(NULL == (file = fopen(filename, "a+")))
    {
        printf("open error!");
	exit(1);
    }

    if(fprintf(file, "%s", msg->message) == -1)
    {
        printf("write error!");
	exit(1);
    }

    if(0 != fclose(file))
    {
        printf("close error!");
	exit(1);
    }

}
