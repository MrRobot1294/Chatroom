#include "../../include/my_head.h"

void perror_exit2(char *s)
{
    printf(s);
    exit(1);
}

void file_send_write(FILE **file, Link msg)
{
    if(fprintf(*file,"%s", msg->message) == -1)
    {
	perror_exit2("write error!");
    }
}

void file_send_write2(FILE **file, Link msg)
{
    if(fprintf(*file,"FILESEND_%s_%s\n", msg->name, msg->answer) == -1)
    {
	perror_exit2("write error!");
    }
}


int file_send_callback(void *para, int columncount, char **columnvalue, char **columnname)
{
    char *filename = (char *)para;
    
    memset(filename, 0, sizeof(filename));

    sprintf(filename, "file_transfer/file%s", columnvalue[0]);

    return 0;
}

int file_send_callback2(void *para, int columncount, char **columnvalue, char **columnname)
{
    char *target_id = (char *)para;
    
    memset(target_id, 0, sizeof(target_id));

    my_strcpy(target_id, columnvalue[0]);

    return 0;
}


void file_send(Link msg, int new_fd)
{
    int target_sfd;

    char filename[50];
    
    char sql[1024];
    char *errmsg;
   
    sqlite3 *db;

    FILE *file;

    memset(filename, 0, sizeof(filename));

    my_strcpy(filename, "file_transfer/nobody");
        
    sqlite3_open("users.db", &db);
    sprintf(sql, "select id from user where name='%s'", msg->target_user);

    sqlite3_exec(db, sql, file_send_callback, filename, &errmsg);

    sqlite3_close(db);

    sprintf(filename, "%s%s", filename, msg->answer);
    
    if(my_strcmp(msg->message, "(end)") == 0)
    {
        if(my_strncmp(filename, "file_transfer/nobody", 20) == 0)
	{
	    msg->action = FAILED_NOBODY;
	    write(new_fd, msg, sizeof(Node));
	    
	    if((file = fopen(filename, "w")) == NULL)
            {
                perror_exit2("open error!");
            }
            if(fclose(file) != 0)
            {
                perror_exit2("close error!");
            }  

	}
	else
	{     
	    target_sfd = link_search_name(msg);

	    if(target_sfd != -1)
	    {
	        write(target_sfd, msg, sizeof(Node));
	    }
	    else
	    {
	        char target_id[10];

	        sqlite3_open("users.db", &db);
                sprintf(sql, "select id from user where name='%s'", msg->target_user);

                sqlite3_exec(db, sql, file_send_callback2, target_id, &errmsg);

                sqlite3_close(db);

	        memset(filename, 0, sizeof(filename));

	        sprintf(filename, "offmsg/msg%s.txt", target_id);
            
	        if((file = fopen(filename, "a")) == NULL)
                {
                    perror_exit1("open error!");
                }

                file_send_write2(&file, msg);

                if(fclose(file) != 0)
                {
                    perror_exit1("close error!");
                }

	    }
	}
    }
    else
    {
        if((file = fopen(filename, "a+")) == NULL)
        {
            perror_exit2("open error!");
        }

        file_send_write(&file, msg);

        if(fclose(file) != 0)
        {
            perror_exit2("close error!");
        }  
    }
}
