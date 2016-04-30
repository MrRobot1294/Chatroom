#include "../../include/my_head.h"

int log_callback(void *para, int columncount, char **columnvalue, char **columnname)
{
    Link msg = (Link )para;

    my_strcpy(msg->name, columnvalue[0]);
    msg->state = atoi(columnvalue[2]);
    
    switch(msg->state)
    {
        case 0:
	{
	    msg->action = SUCCESS_ADMIN;
	    break;
	}
	case 1:
	{
	    msg->action = SUCCESS;
	    break;
	}
	case 2:
	{
	    msg->action = SUCCESS_BAN;
	    break;
	}
	case 3:
	{
	    msg->action = FAILED_BAN;
	    break;
	}
	default:
	{
	    printf("error\n");
	}
    }
    return 0;
}

void my_log(Link msg, int new_fd)
{
    char sql[1024];
    char *errmsg;
    
    sqlite3 *db;

    msg->action = FAILED;

    sqlite3_open("users.db", &db);
    sprintf(sql, "select name,answer,state from user where id='%s' and password='%s'", msg->id, msg->password);

    sqlite3_exec(db, sql, log_callback, msg, &errmsg);

    link_search_id(msg);

    if(msg->action == SUCCESS_ADMIN || msg->action == SUCCESS || msg->action == SUCCESS_BAN)
    {
        msg->online_sfd = new_fd;

	link_insert(msg);
    }

    write(new_fd, msg, sizeof(Node));

    link_print();

    sqlite3_close(db);
}
