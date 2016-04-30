#include "../../include/my_head.h"

void my_log(int new_fd)
{
    clear();
    refresh();

    int i = 0;

    char ch;
    char str[30] = "                            ";

    WINDOW *new_window, *new_window2;
    
    memset(&msg1, 0, sizeof(Node));
    msg1.action = LOG;

    new_window = newwin(17, 70, 5, 24);

    box(new_window, 0, 0);

    mvwaddstr(new_window, 2, 35, "log");
    mvwaddstr(new_window, 1, 1, "ESC");
    mvwaddstr(new_window, 5, 9, "id       :");
    mvwaddstr(new_window, 8, 9, "password :");
    //mvwaddstr(new_window, 11, 28, "Forgot Password");
    //mvwaddstr(new_window, 10, 9, "question : Who is your father?");
    //mvwaddstr(new_window, 12, 9, "answer   :");
    mvwaddstr(new_window, 5, 48, "(Less than 8)");
    mvwaddstr(new_window, 8, 48, "(Less than 19)");
    //mvwaddstr(new_window, 12, 48, "(Less than 19)");
    wmove(new_window, 5, 20); 
    wrefresh(new_window);

    //keypad(new_window, true);

    //cbreak();

    noecho();
    do
    {
        i = 0;

        mvwaddstr(new_window, 5, 20, str);
        mvwaddstr(new_window, 5, 48, "(8 digit number)");
        wmove(new_window, 5, 20); 
        wrefresh(new_window);
        while((ch = wgetch(new_window)) != '\n')
        {
            if(ch == 27)
	    {
	        goto EXIT_LOG;
	    }

	    if(ch == 127)
	    {
	        if(i > 0)
	        {
	            mvwaddstr(new_window, 5, 19 + i, " ");
	            wmove(new_window, 5, 19 + i);
		    wrefresh(new_window);

		    i--;
		    msg1.id[i] = '\0';
		}
	    }
	    else
	    {
                msg1.id[i] = ch;
                wprintw(new_window, "%c", msg1.id[i]);
	        i++;
	    }

	    if(i == 9)
	    {
	        mvwaddstr(new_window, 5, 48, "(More than 8)   ");
		wmove(new_window, 5, 29);
		wrefresh(new_window);
	    }
	    if(i == 8)
	    {
	        mvwaddstr(new_window, 5, 48, "(8 digit number)");
		wmove(new_window, 5, 28);
		wrefresh(new_window);
	    }
	    if(i < 8 && i > 0)
	    {
	        mvwaddstr(new_window, 5, 48, "(Less than 8)   ");
		wmove(new_window, 5, 20 + i);
		wrefresh(new_window);
	    }
	    /*while(i > 40)
	    {
	        wmove(new_window, 5, 51);
		wrefresh(new_window);
	    }*/
        }
    }while(i != 8 || i == 0);

    msg1.id[i] = '\0';

    noecho();
    do
    {
        i = 0;

        mvwaddstr(new_window, 8, 20, str);
        mvwaddstr(new_window, 8, 48, "(Less than 19)");
        wmove(new_window, 8, 20); 
        wrefresh(new_window);
        while((ch = wgetch(new_window)) != '\n')
        {
	    /*if(ch == KEY_DOWN)
	    {
	        get(new_window, y1, x1);
                b[i] = '\0';
                
		w
	    }*/
	    if(ch == 27)
	    {
	        goto EXIT_LOG;
	    }

	    if(ch == 127)
	    { 
	        if(i > 0)
	        {
	            mvwaddstr(new_window, 8, 19 + i, " ");
	            wmove(new_window, 8, 19 + i);
		    wrefresh(new_window);

		    i--;
		    msg1.password[i] = '\0';
		}
	    }
	    else
	    {
	        waddch(new_window, '*');
	        wrefresh(new_window);
                msg1.password[i] = ch;
	        i++;
	    }

	    if(i == 20)
	    {
	        mvwaddstr(new_window, 8, 48, "(More than 19)");
		wmove(new_window, 8, 40);
       		wrefresh(new_window);
	    }
	    /*while(i > 40)
	    {
	        wmove(new_window, 5, 51);
		wrefresh(new_window);
	    }*/
        }
    }while(i > 19 || i == 0);

    msg1.password[i] = '\0';

    /*echo();
    do
    {
        i = 0;

        mvwaddstr(new_window, 12, 20, str);
        mvwaddstr(new_window, 12, 48, "(Less than 19)");
        wmove(new_window, 12, 20); 
        wrefresh(new_window);
        while((ch = wgetch(new_window)) != '\n')
        {
            d[i] = ch;
	    i++;

	    if(i == 20)
	    {
	        mvwaddstr(new_window, 12, 48, "(More than 19)");
		wmove(new_window, 12, 40);
		wrefresh(new_window);
	    }
	    //while(i > 40)
	    //{
	      //  wmove(new_window, 5, 51);
		//wrefresh(new_window);
	    //}
        }
    }while(i > 19);

    d[i] = '\0';*/

    write(new_fd, &msg1, sizeof(Node));
    memset(&msg1, 0, sizeof(Node));
    read(new_fd, &msg1, sizeof(Node));
    
    clear();
    refresh();

    new_window2 = newwin(13, 50, 5, 30);

    box(new_window2, 0, 0);

    switch(msg1.action)
    {
        case SUCCESS_ADMIN:
	{
            mvwaddstr(new_window2, 4, 18, "Welcome back");
            mvwaddstr(new_window2, 7, 22, "ADMIN");
	    break;
	}
	case SUCCESS:
	{
            mvwaddstr(new_window2, 4, 16, "Welcome to come back");
            mvwaddstr(new_window2, 7, 22, msg1.name);
	    break;
	}
	case SUCCESS_BAN:
	{
            mvwaddstr(new_window2, 3, 10, "Sorry, you have been banned to say");
            mvwaddstr(new_window2, 5, 22, msg1.name);
	    break;
	}
	case FAILED:
	{
            mvwaddstr(new_window2, 4, 22, "Failed");
            mvwaddstr(new_window2, 7, 12, "Sorry, please try again....");
	    break;
	}
	case FAILED_BAN:
	{     
	    mvwaddstr(new_window2, 3, 10, "Sorry, you have been banned to log");
            mvwaddstr(new_window2, 5, 22, msg1.name);
	    break;
	}	
	case FAILED_ONLINE:
	{     
            mvwaddstr(new_window2, 4, 22, "Failed");
	    mvwaddstr(new_window2, 3, 10, "Sorry, the id have been logged");
	    break;
	}	
	default:
	{
	}
    }
    wrefresh(new_window2);

    EXIT_LOG:

    sleep(1);
}
