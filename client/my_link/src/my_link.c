#include "../../include/my_head.h"

void headnode(Link *head)
{
    (*head) = (Link)malloc(sizeof(Node));
    (*head)->next = NULL;
}

void link_insert(Link msg)
{
    //Link newnode;

    newnode = (Link)malloc(sizeof(Node));
    memset(newnode, 0, sizeof(Node));

    newnode->online_sfd = msg->online_sfd;
    newnode->state = msg->state;
    my_strcpy(newnode->name,msg->name);
    my_strcpy(newnode->id,msg->id);
   
    Link p = online_user;
    Link q = online_user->next;

    if(q == NULL)
    {
         newnode->next = online_user->next;
	 online_user->next = newnode;
    }

    while(q != NULL)
    {
        if(newnode->state == 0)
	{
	    newnode->next = online_user->next;
	    online_user->next = newnode;

	    break;
	}
	if(q->state == 0 || my_strcmp(q->name, newnode->name) <= 0)
	{
	    p = p->next;
	    q = q->next;
	}
	else
	{
	    newnode->next = q;
	    p->next = newnode;

	    break;
	}

	if(q == NULL)
	{
	    newnode->next = q;
	    p->next = newnode;
	}
    }
}

void link_print()
{
    Link p = online_user->next;

    while(p != NULL)
    {
        printf("%d %d %s %s %s\n",p->online_sfd,p->state,p->id,p->name,p->password);

	p = p->next;
    }
}

int link_search_name(Link msg)
{
    Link p = online_user->next;

    while(p != NULL)
    {
        if(my_strcmp(p->name, msg->target_user) == 0)
	{
	    return p->online_sfd;
	}

	p = p->next;
    }
    return -1;
}

void link_search_id(Link msg)
{
    Link p = online_user->next;

    while(p != NULL)
    {
        if(my_strcmp(p->id, msg->id) == 0)
	{
	    msg->action = FAILED_ONLINE;
	}

	p = p->next;
    }
}

void link_search_sfd(int new_fd)
{
    Link p = online_user->next;
    Link q = online_user;

    while(p != NULL)
    {
        if(p->online_sfd == new_fd)
	{
	    q->next = p->next;
	    free(p);
	    p = NULL;
	    
	    break;
	}
        
	q = q->next;
	p = p->next;
    }
}

char * link_search_id2(Link msg)
{
    Link p = online_user->next;

    while(p != NULL)
    {
        if(my_strcmp(p->name, msg->target_user) == 0)
	{
	    return p->id;
	}

	p = p->next;
    }

    return NULL;
}

void change_name_search_id(Link msg)
{
    Link p = online_user->next;

    while(p != NULL)
    {
        if(my_strcmp(p->id, msg->id) == 0)
	{
	    my_strcpy(p->name, msg->name);
	}

	p = p->next;
    }
}

void quit_search_id(Link msg)
{
    Link p = online_user->next;
    Link q = online_user;

    while(p != NULL)
    {
        if(my_strcmp(p->id, msg->id) == 0)
	{
	    q->next = p->next;
	    free(p);
	    p = NULL;
	    
	    break;
	}
        
	q = q->next;
	p = p->next;
    }
}
