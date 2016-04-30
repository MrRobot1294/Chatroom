#include "../../include/my_head.h"

void perror_exit1(char *s)
{
    printf(s);
    exit(1);
}

void file_write(FILE **file, Link msg)
{
        if(fprintf(*file,"%s_%s_%s\n", msg->name, msg->target_user, msg->message) == -1)
	{
	    perror_exit1("write error!");
	}
}

int chat_callback(void *para, int columncount, char **columnvalue, char **columnname)
{
    printf("%s\n", columnvalue[0]);
    printf("aaa\n");
    Link msg = (Link )para;
    
    memset(msg->id, 0, sizeof(msg->id));

    my_strcpy(msg->id, columnvalue[0]);
printf("%s\n",msg->id);
    msg->action = SUCCESS_OFFLINE;

    return 0;
}
    
void private_chat(Link msg, int new_fd)
{    
    int target_sfd = link_search_name(msg);

    Node msg2;

    memset(&msg2, 0, sizeof(Node));
    if(target_sfd != -1)
    {
        msg2.action = msg->action;
	msg2.online_sfd = msg->online_sfd;

        my_strcpy(msg2.name, msg->name);
        my_strcpy(msg2.target_user, msg->target_user);
        my_strcpy(msg2.message, msg->message);

        char filename[50];

        FILE *file;


	memset(filename, 0, sizeof(filename));

	sprintf(filename, "chathistory/chat%s.txt", msg->id);
            
	if((file = fopen(filename, "a")) == NULL)
        {
            perror_exit1("open error!");
        }

        chathistory_write1(&file, msg);

        if(fclose(file) != 0)
        {
            perror_exit1("close error!");
        }
        
	memset(filename, 0, sizeof(filename));


	sprintf(filename, "chathistory/chat%s.txt", link_search_id2(msg));
            
	if((file = fopen(filename, "a")) == NULL)
        {
            perror_exit1("open error!");
        }

        chathistory_write2(&file, msg);

        if(fclose(file) != 0)
        {
            perror_exit1("close error!");
        }

        write(target_sfd, &msg2, sizeof(Node));
    }
    else
    {
        char str[9];

        char sql[1024];
        char *errmsg;

        sqlite3 *db;
        
	memset(str, 0, sizeof(str));
	my_strcpy(str, msg->id);

        msg->action = FAILED_NOBODY;

        printf("%s %s\n",msg->id,msg->password);
        printf("aaa\n");

        sqlite3_open("users.db", &db);
        sprintf(sql, "select id from user where name='%s'", msg->target_user);

        sqlite3_exec(db, sql, chat_callback, msg, &errmsg);

	if(msg->action == SUCCESS_OFFLINE)
	{
	    char filename[50];

            FILE *file;
	    
	    memset(filename, 0, sizeof(filename));

	    sprintf(filename, "chathistory/chat%s.txt", str);
            
	    if((file = fopen(filename, "a")) == NULL)
            {
                perror_exit1("open error!");
            }

            chathistory_write3(&file, msg);

            if(fclose(file) != 0)
            {
                perror_exit1("close error!");
            }
         

	    memset(filename, 0, sizeof(filename));

	    sprintf(filename, "chathistory/chat%s.txt", msg->id);
            
	    if((file = fopen(filename, "a")) == NULL)
            {
                perror_exit1("open error!");
            }

            chathistory_write4(&file, msg);

            if(fclose(file) != 0)
            {
                perror_exit1("close error!");
            }


	    memset(filename, 0, sizeof(filename));

	    sprintf(filename, "offmsg/msg%s.txt", msg->id);
            
	    if((file = fopen(filename, "a")) == NULL)
            {
                perror_exit1("open error!");
            }

            file_write(&file, msg);

            if(fclose(file) != 0)
            {
                perror_exit1("close error!");
            }
	}

	write(new_fd, msg, sizeof(Node));
    }
}

