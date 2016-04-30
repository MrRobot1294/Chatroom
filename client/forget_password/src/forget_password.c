#include "../../include/my_head.h"

void forget_password(int new_fd)
{
    int i = 0;

    char ch;
    char psd[20];
    char str[30] = "                            ";
    Node msg;

    memset(&msg, 0, sizeof(Node));

    WINDOW *new_window;

    msg.action = FORGET_PASSWORD;

    clear();
    refresh();
    ch_window6 = newwin(17, 70, 5, 24);
    box(ch_window6, 0, 0);

    mvwaddstr(ch_window6, 1, 1, "ESC");
    mvwaddstr(ch_window6, 3, 9, "id           :");
    mvwaddstr(ch_window6, 5, 9, "question     : Who is your ******?");
    mvwaddstr(ch_window6, 6, 9, "answer       :");
    mvwaddstr(ch_window6, 8, 9, "new-password :");
    mvwaddstr(ch_window6, 10, 9, "re-enter     :");

    mvwaddstr(ch_window6, 3, 52, "(Less than 8)");
    mvwaddstr(ch_window6, 6, 52, "(Less than 19)");
    mvwaddstr(ch_window6, 8, 52, "(Less than 19)");
    mvwaddstr(ch_window6, 10, 52, "(Less than 19)");

    wmove(ch_window6, 3, 20); 
    wrefresh(ch_window6);

    noecho();
    do
    {
        i = 0;

        mvwaddstr(ch_window6, 3, 24, str);
        mvwaddstr(ch_window6, 3, 52, "(8 digit number)");
        wmove(ch_window6, 3, 24); 
        wrefresh(ch_window6);
        while((ch = wgetch(ch_window6)) != '\n')
        {
            if(ch == 27)
	    {
	        goto EXIT_FORGET_PASSWORD;
	    }

	    if(ch == 127)
	    {
	        if(i > 0)
	        {
	            mvwaddstr(ch_window6, 3, 23 + i, " ");
	            wmove(ch_window6, 3, 23 + i);
		    wrefresh(ch_window6);

		    i--;
		    msg.id[i] = '\0';
		}
	    }
	    else
	    {
                msg.id[i] = ch;
                wprintw(ch_window6, "%c", msg.id[i]);
	        i++;
	    }

	    if(i == 9)
	    {
	        mvwaddstr(ch_window6, 3, 52, "(More than 8)   ");
		wmove(ch_window6, 3, 33);
		wrefresh(ch_window6);
	    }
	    if(i == 8)
	    {
	        mvwaddstr(ch_window6, 3, 52, "(8 digit number)");
		wmove(ch_window6, 3, 32);
		wrefresh(ch_window6);
	    }
	    if(i < 8 && i > 0)
	    {
	        mvwaddstr(ch_window6, 3, 52, "(Less than 8)   ");
		wmove(ch_window6, 3, 24 + i);
		wrefresh(ch_window6);
	    }
	    /*while(i > 40)
	    {
	        wmove(ch_window6, 5, 51);
		wrefresh(ch_window6);
	    }*/
        }
    }while(i != 8 || i == 0);

    msg.id[i] = '\0';

    noecho();
    do
    {
        i = 0;

        mvwaddstr(ch_window6, 6, 24, str);
        mvwaddstr(ch_window6, 6, 52, "(Less than 19)");
        wmove(ch_window6, 6, 24); 
        wrefresh(ch_window6);
        while((ch = wgetch(ch_window6)) != '\n')
        {
	    /*if(ch == KEY_DOWN)
	    {
	        get(ch_window6, y1, x1);
                b[i] = '\0';
                
		w
	    }*/
	    if(ch == 27)
	    {
	        goto EXIT_FORGET_PASSWORD;
	    }

	    if(ch == 127)
	    { 
	        if(i > 0)
	        {
	            mvwaddstr(ch_window6, 6, 23 + i, " ");
	            wmove(ch_window6, 6, 23 + i);
		    wrefresh(ch_window6);

		    i--;
		    msg.answer[i] = '\0';
		}
	    }
	    else
	    {
                msg.answer[i] = ch;
                wprintw(ch_window6, "%c", ch);
	        wrefresh(ch_window6);
	        i++;
	    }

	    if(i == 20)
	    {
	        mvwaddstr(ch_window6, 6, 52, "(More than 19)");
		wmove(ch_window6, 6, 44);
       		wrefresh(ch_window6);
	    }
	    if(i == 19)
	    {
	        mvwaddstr(ch_window6, 6, 52, "(Less than 19)");
		wmove(ch_window6, 6, 43);
       		wrefresh(ch_window6);
	    }
	    /*while(i > 40)
	    {
	        wmove(ch_window6, 5, 51);
		wrefresh(ch_window6);
	    }*/
        }
    }while(i > 19 || i == 0);

    msg.answer[i] = '\0';

    do
    {
        noecho();
        do
        {
            i = 0;

            mvwaddstr(ch_window6, 8, 24, str);
            mvwaddstr(ch_window6, 10, 24, str);
            mvwaddstr(ch_window6, 8, 52, "(Less than 19)");
            mvwaddstr(ch_window6, 10, 52, "(Less than 19)");
            wmove(ch_window6, 8, 24); 
            wrefresh(ch_window6);
            while((ch = wgetch(ch_window6)) != '\n')
            {
	        if(ch == 27)
	        {
	            goto EXIT_FORGET_PASSWORD;
	        }

	        if(ch == 127)
	        {
		    if(i > 0)
	            {
	                mvwaddstr(ch_window6, 8, 23 + i, " ");
	                wmove(ch_window6, 8, 23 + i);
		        wrefresh(ch_window6);

		        i--;
		        msg.password[i] = '\0';
	            }
	        }
	        else
	        {

	            waddch(ch_window6, '*');
	            wrefresh(ch_window6);
                    msg.password[i] = ch;
	            i++;
		}

	        if(i == 20)
	        {
	            mvwaddstr(ch_window6, 8, 52, "(More than 19)");
		    wmove(ch_window6, 8, 44);
       		    wrefresh(ch_window6);
	        }
	    if(i == 19)
	    {
	        mvwaddstr(ch_window6, 8, 52, "(Less than 19)");
		wmove(ch_window6, 8, 43);
       		wrefresh(ch_window6);
	    }
	        /*while(i > 40)
	        {
	            wmove(ch_window6, 5, 51);
		    wrefresh(ch_window6);
	        }*/
            }
        }while(i > 19 || i == 0);

        msg.password[i] = '\0';

        noecho();
        do
        {
            i = 0;

            mvwaddstr(ch_window6, 10, 24, str);
            mvwaddstr(ch_window6, 10, 52, "(Less than 19)");
            wmove(ch_window6, 10, 24); 
            wrefresh(ch_window6);
            while((ch = wgetch(ch_window6)) != '\n')
            {
	        if(ch == 27)
	        {
	            goto EXIT_FORGET_PASSWORD;
	        }

	        if(ch == 127)
	        {
		    if(i > 0)
	            {
	                mvwaddstr(ch_window6, 10, 23 + i, " ");
	                wmove(ch_window6, 10, 23 + i);
		        wrefresh(ch_window6);

		        i--;
		        psd[i] = '\0';
	            }
	        }
	        else
	        {
	            waddch(ch_window6, '*');
	            wrefresh(ch_window6);
                    psd[i] = ch;
	            i++;
		}

	        if(i == 20)
	        {
	            mvwaddstr(ch_window6, 10, 52, "(More than 19)");
		    wmove(ch_window6, 10, 44);
		    wrefresh(ch_window6);
	        }
	    if(i == 19)
	    {
	        mvwaddstr(ch_window6, 10, 52, "(Less than 19)");
		wmove(ch_window6, 10, 43);
       		wrefresh(ch_window6);
	    }
	        /*while(i > 40)
	        {
	            wmove(ch_window6, 5, 51);
		    wrefresh(ch_window6);
	        }*/
            }
    
        }while(i > 19 || i == 0);
    
        psd[i] = '\0';
       
        if(my_strcmp(psd, msg.password) != 0)
	{
	    mvwaddstr(ch_window6, 15, 15, "(The NEW-PASSWORD and RE-ENTER are different)");
	}

    }while(my_strcmp(psd, msg.password) != 0);

    mvwaddstr(ch_window6, 15, 15, "                                                 ");
    wrefresh(ch_window6);

    write(new_fd, &msg, sizeof(Node));

    memset(&msg, 0, sizeof(Node));
    read(new_fd, &msg, sizeof(Node));
    
    clear();
    refresh();

    new_window = newwin(13, 50, 5, 30);

    box(new_window, 0, 0);

    switch(msg.action)
    {
        case SUCCESS_CHANGE_PSD:
	{
            mvwaddstr(new_window, 4, 22, "SUCCESS");
            mvwaddstr(new_window, 7, 17, "Please RELOGIN");
	    break;
	}

	case FAILED_CHANGE_PSD:
	{
            mvwaddstr(new_window, 4, 22, "Failed");
            mvwaddstr(new_window, 7, 12, "Sorry, please try again....");
	    break;
	}

	default:
	{
	}
    }
    wrefresh(new_window);

    sleep(1);

    EXIT_FORGET_PASSWORD:

    echo();
}
