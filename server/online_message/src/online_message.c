#include "../../include/my_head.h"

void online_message(Link msg, int new_fd)
{
    Node msg2;

    memset(&msg2, 0, sizeof(Node));

    msg2.action = ONLINE;
    
    Link p = online_user->next;
    
    while(p != NULL)
    {
        if(my_strcmp(p->id, msg->id) != 0)
	{
            msg2.state = p->state;
            my_strcpy(msg2.name, p->name);
            my_strcpy(msg2.id, p->id);

	    write(new_fd, &msg2, sizeof(Node));
        }

	p = p->next;
    }

    p = online_user->next;

    memset(&msg2, 0, sizeof(Node));

    msg2.action = ONLINE;
    msg2.state = msg->state;
    my_strcpy(msg2.name, msg->name);
    my_strcpy(msg2.id, msg->id);

    while(p != NULL)
    {
        if(my_strcmp(p->id, msg->id) != 0)
	{
	    printf("%d\n",p->online_sfd);
            write(p->online_sfd, &msg2, sizeof(Node));
        }
	p = p->next;
    }

}
