#include "../../include/my_head.h"

void my_register(Link msg, int new_fd)
{
    int rc;

    int row;
    int column;

    char sql[1024];
    char *errmsg;
    char **result;

    sqlite3 *db;

    rc = sqlite3_open("users.db",&db);
    if(rc)
    {
        printf("open failed\n");
	msg->action = FAILED;
        write(new_fd, msg, sizeof(Node));

	goto EXIT_REGISTER;
    }

    //printf("aaaa\n");
    
    rc = sqlite3_get_table(db, "select *from user", &result, &row, &column, &errmsg);
    if(rc)
    {
        printf("failed\n");
	msg->action = FAILED;
        write(new_fd, msg, sizeof(Node));

	goto EXIT_REGISTER;
    }

    sprintf(msg->id, "%08d", row);
    
    //printf("%s\n",msg->id);

    sprintf(sql, "insert into user(id,name,password,answer,state) values('%s','%s','%s','%s',1)", msg->id, msg->name, msg->password, msg->answer);

    rc = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    if(rc)
    {
        printf("failed\n");
	msg->action = FAILED;
        write(new_fd, msg, sizeof(Node));

	goto EXIT_REGISTER;
    }
    
    msg->action = SUCCESS;

    msg->state = 1;

    //printf("%d %s %s\n",msg->action,msg->name,msg->password);
    
    //write(new_fd, &msg, sizeof(Node));

    write(new_fd, msg, sizeof(Node));
    
    EXIT_REGISTER:
    sqlite3_close(db);
}
