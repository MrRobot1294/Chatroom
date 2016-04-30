#include "../../include/my_head.h"

void my_register(int new_fd)
{
    clear();
    refresh();

    int i = 0;

    char ch;
    char psd[20];
    char str[30] = "                            ";

    WINDOW *new_window, *new_window2;
   
    memset(&msg1, 0, sizeof(Node));
    msg1.action = REGISTER;

    new_window = newwin(17, 70, 5, 24);

    box(new_window, 0, 0);

    mvwaddstr(new_window, 2, 31, "register");
    mvwaddstr(new_window, 1, 1, "ESC");
    mvwaddstr(new_window, 4, 9, "name     :");
    mvwaddstr(new_window, 6, 9, "password :");
    mvwaddstr(new_window, 8, 9, "re-enter :");
    mvwaddstr(new_window, 10, 9, "question : Who is your ******?");
    mvwaddstr(new_window, 12, 9, "answer   :");
    mvwaddstr(new_window, 4, 48, "(Less than 19)");
    mvwaddstr(new_window, 6, 48, "(Less than 19)");
    mvwaddstr(new_window, 8, 48, "(Less than 19)");
    mvwaddstr(new_window, 12, 48, "(Less than 19)");
    wmove(new_window, 4, 20); 
    wrefresh(new_window);

    noecho();
    do
    {
        i = 0;

        mvwaddstr(new_window, 4, 20, str);
        mvwaddstr(new_window, 4, 48, "(Less than 19)");
        wmove(new_window, 4, 20); 
        wrefresh(new_window);
        while((ch = wgetch(new_window)) != '\n')
        { 
	    if(ch == 27)
	    {
	        goto EXIT_REGISTER;
	    }

	    if(ch == 127)
	    {
	        if(i > 0)
	        {
	            mvwaddstr(new_window, 4, 19 + i, " ");
	            wmove(new_window, 4, 19 + i);
		    wrefresh(new_window);

		    i--;
		    msg1.id[i] = '\0';
		}
	    }
	    else
	    {
                msg1.name[i] = ch;
                wprintw(new_window, "%c", msg1.name[i]);
	        i++;
	    }

	    if(i == 20)
	    {
	        mvwaddstr(new_window, 4, 48, "(More than 19)");
		wmove(new_window, 4, 40);
		wrefresh(new_window);
	    }
	    /*while(i > 40)
	    {
	        wmove(new_window, 5, 51);
		wrefresh(new_window);
	    }*/
        }
    }while(i > 19 || i == 0);

    msg1.name[i] = '\0';

    do
    {
        noecho();
        do
        {
            i = 0;

            mvwaddstr(new_window, 6, 20, str);
            mvwaddstr(new_window, 8, 20, str);
            mvwaddstr(new_window, 6, 48, "(Less than 19)");
            mvwaddstr(new_window, 8, 48, "(Less than 19)");
            wmove(new_window, 6, 20); 
            wrefresh(new_window);
            while((ch = wgetch(new_window)) != '\n')
            {
	        if(ch == 27)
	        {
	            goto EXIT_REGISTER;
	        }

	        if(ch == 127)
	        {
		    if(i > 0)
	            {
	                mvwaddstr(new_window, 6, 19 + i, " ");
	                wmove(new_window, 6, 19 + i);
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
	            mvwaddstr(new_window, 6, 48, "(More than 19)");
		    wmove(new_window, 6, 40);
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
	        if(ch == 27)
	        {
	            goto EXIT_REGISTER;
	        }

	        if(ch == 127)
	        {
		    if(i > 0)
	            {
	                mvwaddstr(new_window, 8, 19 + i, " ");
	                wmove(new_window, 8, 19 + i);
		        wrefresh(new_window);

		        i--;
		        psd[i] = '\0';
	            }
	        }
	        else
	        {
	            waddch(new_window, '*');
	            wrefresh(new_window);
                    psd[i] = ch;
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
    
        psd[i] = '\0';
       
        if(my_strcmp(psd, msg1.password) != 0)
	{
	    mvwaddstr(new_window, 15, 15, "(The PASSWORD and RE-ENTER are different)");
	}

    }while(my_strcmp(psd, msg1.password) != 0);

    mvwaddstr(new_window, 15, 15, "                                         ");
    wrefresh(new_window);

    noecho();
    do
    {
        i = 0;

        mvwaddstr(new_window, 12, 20, str);
        mvwaddstr(new_window, 12, 48, "(Less than 19)");
        wmove(new_window, 12, 20); 
        wrefresh(new_window);
        while((ch = wgetch(new_window)) != '\n')
        {
	    if(ch == 27)
	    {
	        goto EXIT_REGISTER;
	    }

	    if(ch == 127)
	    {
	        if(i > 0)
	        {
	            mvwaddstr(new_window, 12, 19 + i, " ");
	            wmove(new_window, 12, 19 + i);
		    wrefresh(new_window);

		    i--;
		    msg1.answer[i] = '\0';
		}
	    }
	    else
	    {
                msg1.answer[i] = ch;
                wprintw(new_window, "%c", msg1.answer[i]);
	        i++;
            }

	    if(i == 20)
	    {
	        mvwaddstr(new_window, 12, 48, "(More than 19)");
		wmove(new_window, 12, 40);
		wrefresh(new_window);
	    }
	    /*while(i > 40)
	    {
	        wmove(new_window, 5, 51);
		wrefresh(new_window);
	    }*/
        }
    }while(i > 19 || i == 0);

    msg1.answer[i] = '\0';

    write(new_fd, &msg1, sizeof(Node));
    memset(&msg1, 0, sizeof(Node));
    read(new_fd, &msg1, sizeof(Node));


    clear();
    refresh();

    new_window2 = newwin(13, 50, 5, 30);

    box(new_window2,0,0);

    if(msg1.action == SUCCESS)
    {
        mvwaddstr(new_window2, 3, 16, "Welcome to join us!");
        mvwaddstr(new_window2, 5, 13, "Please remember your id :");
        mvwaddstr(new_window2, 7, 21, msg1.id);
    }
    else
    {
        mvwaddstr(new_window2, 4, 22, "Failed");
        mvwaddstr(new_window2, 7, 12, "Sorry, please try again....");
    }
    wrefresh(new_window2);

    EXIT_REGISTER:

    sleep(1);
}
