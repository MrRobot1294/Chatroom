#include "../../include/my_head.h"

void perror_exit(char *s)
{
    printf(s);
    exit(1);
}

void file_read(FILE **file, int new_fd)
{
    char ch[1024];

    char *p;
    char *delim = "_";
    Node offmsg;

    memset(&offmsg, 0, sizeof(Node));

    memset(ch, 0, sizeof(ch));

    while(NULL != fgets(ch, sizeof(ch), *file))
    {
        offmsg.action = OFFLINE_MSG;
        
        p = strtok(ch,delim);
	my_strcpy(offmsg.name, p);

	if(my_strcmp(offmsg.name, "FILESEND") == 0)
	{
            offmsg.action = FILE_SEND;

	    p = strtok(NULL,delim);
	    my_strcpy(offmsg.name, p);
        
	    p = strtok(NULL,delim);
	    my_strcpy(offmsg.answer, p);

	    int n;

	    for(n = 0; n < 20; n++)
	    {
	        if(offmsg.answer[n] == '\n')
		{
		    offmsg.answer[n] = '\0';
		}
	    }

	}
	else
	{
	    p = strtok(NULL,delim);
	    my_strcpy(offmsg.target_user, p);
        
	    p = strtok(NULL,delim);
	    my_strcpy(offmsg.message, p);
	}

	write(new_fd, &offmsg, sizeof(Node));
     
	memset(&offmsg, 0, sizeof(Node));
    }
}

void offline_msg(Link msg, int new_fd)
{
    char filename[50];

    FILE *file;

    memset(filename, 0, sizeof(filename));

    sprintf(filename, "offmsg/msg%s.txt", msg->id);

    if((file = fopen(filename, "a+")) == NULL)
    {
        perror_exit("open error!");
    }

    file_read(&file, new_fd);

    if(fclose(file) != 0)
    {
        perror_exit("close error!");
    }  
    
    memset(filename, 0, sizeof(filename));

    sprintf(filename, "offmsg/msg%s.txt", msg->id);
    
    if((file = fopen(filename, "w")) == NULL)
    {
        perror_exit("open error!");
    }
    if(fclose(file) != 0)
    {
        perror_exit("close error!");
    }
}
