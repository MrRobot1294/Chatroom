#include "../../include/my_head.h"

void change_name(Link msg)
{
    Link p;

    char sql[1024];
    char *errmsg;

    sqlite3 *db;

    sqlite3_open("users.db", &db);

    sprintf(sql, "update user set name='%s' where id='%s'", msg->name, msg->id);

    printf("%s\n", msg->name);

    sqlite3_exec(db, sql, NULL, NULL, &errmsg);

    sqlite3_close(db);

    change_name_search_id(msg);

    link_print();

    p = online_user->next;

    while(p != NULL)
    {
        if(my_strcmp(p->id, msg->id) != 0)
	{
	    printf("%d\n",p->online_sfd);
            write(p->online_sfd, msg, sizeof(Node));
        }
	p = p->next;
    }
}
