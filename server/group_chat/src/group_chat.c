#include "../../include/my_head.h"

void group_chat(Link msg)
{
    Node msg2;

    Link p = online_user->next;

    memset(&msg2, 0, sizeof(Node));
    
    char filename[50];

    FILE *file;

    memset(filename, 0, sizeof(filename));

    sprintf(filename, "chathistory/chat%s.txt", msg->id);
            
    if((file = fopen(filename, "a")) == NULL)
    {
        perror_exit1("open error!");
    }

    chathistory_write5(&file, msg);

    if(fclose(file) != 0)
    {
        perror_exit1("close error!");
    }

    msg2.action = msg->action;
    my_strcpy(msg2.message, msg->message);
    my_strcpy(msg2.name, msg->name);

    while(p != NULL)
    {
        if(my_strcmp(msg->id, p->id) != 0)
	{
	    memset(filename, 0, sizeof(filename));

	    sprintf(filename, "chathistory/chat%s.txt", p->id);
	    if((file = fopen(filename, "a")) == NULL)
            {
                perror_exit1("open error!");
            }

            chathistory_write6(&file, msg);

            if(fclose(file) != 0)
            {
                perror_exit1("close error!");
            }

            write(p->online_sfd, &msg2, sizeof(Node));
        }
	p = p->next;
    }
}
