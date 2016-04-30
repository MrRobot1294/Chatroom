#include "../../include/my_head.h"

void chathistory_write1(FILE **file, Link msg)
{
        if(fprintf(*file,"我 对 %s (历史) %s\n", msg->target_user, msg->message) == -1)
	{
	    perror_exit1("write error!");
	}
}

void chathistory_write2(FILE **file, Link msg)
{
        if(fprintf(*file,"%s 对 我 (历史) %s\n", msg->name, msg->message) == -1)
	{
	    perror_exit1("write error!");
	}
}

void chathistory_write3(FILE **file, Link msg)
{
        if(fprintf(*file,"我 对 %s (离线) (历史) %s\n", msg->target_user, msg->message) == -1)
	{
	    perror_exit1("write error!");
	}
}

void chathistory_write4(FILE **file, Link msg)
{
        if(fprintf(*file,"%s 对 我 (离线) (历史) %s\n", msg->name, msg->message) == -1)
	{
	    perror_exit1("write error!");
	}
}

void chathistory_write5(FILE **file, Link msg)
{
        if(fprintf(*file,"我 对 所有人 (历史) %s\n", msg->message) == -1)
	{
	    perror_exit1("write error!");
	}
}

void chathistory_write6(FILE **file, Link msg)
{
        if(fprintf(*file,"%s 对 所有人 (历史) %s\n", msg->name, msg->message) == -1)
	{
	    perror_exit1("write error!");
	}
}

void history_read(FILE **file, int new_fd)
{
    Node historymsg;

    memset(&historymsg, 0, sizeof(Node));

    while(NULL != fgets(historymsg.message, sizeof(historymsg.message), *file))
    {
        historymsg.action = CHECK_CHAT_HISTORY;
        
	write(new_fd, &historymsg, sizeof(Node));
     
	memset(&historymsg, 0, sizeof(Node));
    }
}

void check_history(Link msg, int new_fd)
{    
    char filename[50];

    FILE *file;

    memset(filename, 0, sizeof(filename));

    sprintf(filename, "chathistory/chat%s.txt", msg->id);

    if((file = fopen(filename, "a+")) == NULL)
    {
        perror_exit("open error!");
    }

    history_read(&file, new_fd);

    if(fclose(file) != 0)
    {
        perror_exit("close error!");
    }
}

void delete_history(Link msg, int new_fd)
{    
    char filename[50];

    FILE *file;

    memset(filename, 0, sizeof(filename));

    sprintf(filename, "chathistory/chat%s.txt", msg->id);

    if((file = fopen(filename, "w")) == NULL)
    {
        perror_exit("open error!");
    }

    if(fclose(file) != 0)
    {
        perror_exit("close error!");
    }  
    
    my_strcpy(msg->message, "success");

    write(new_fd, msg, sizeof(Node));
}
