#include "../../include/my_head.h"

void my_menu1(int new_fd)
{
    int my_choose;
    char str[20];

    WINDOW *new_window;
    
    //initscr();

    setlocale(LC_ALL, "");

    initscr();

    while(1)
    {
        clear();
	refresh();

        new_window = newwin(13, 50, 5, 30);

        box(new_window,0,0);
        mvwaddstr(new_window,2,21,"welcome");
        mvwaddstr(new_window,5,13,"register");
        mvwaddstr(new_window,5,30,"log");
        mvwaddstr(new_window,9,13,"forget-psd");
        mvwaddstr(new_window,9,30,"quit");
        mvaddstr(18,30,"please input(register/log/forget-psd/quit): ");
        refresh();
        wrefresh(new_window);
    
        move(18,74);
        refresh();

        echo();
        scanw("%s", str);

	my_choose = my_select1(str);

	switch(my_choose)
	{
	    case REGISTER:
	    {
		my_register(new_fd);

	        break;
	    }
	    case LOG:
	    {
	        my_log(new_fd);

		if(msg1.action == SUCCESS || msg1.action == SUCCESS_BAN)
		{
                 headnode(&online_user);

		    pthread_t ser_thread;

		    pthread_create(&ser_thread, NULL, (void *)handle_server,(void *) &new_fd);

		    chat_interface(new_fd);
		}
		if(msg1.action == SUCCESS_ADMIN)
		{
                 headnode(&online_user);

		    pthread_t ser_thread;

		    pthread_create(&ser_thread, NULL, (void *)handle_server,(void *) &new_fd);

		    admin_chat_interface(new_fd);
		}


	        break;
	    }
	    case CHANGE_PASSWORD:
	    {
	        forget_password(new_fd);

	        break;
	    }
	    case QUIT:
	    {
                goto EXIT_CLIENT;

	        break;
	    }
	    case WRONG_INPUT:
	    {
	        break;
	    }
	    default:
	    {
	        break;
	    }
	    
	}
    }

    EXIT_CLIENT:
    endwin();
}
