#include "../../include/my_head.h"

void file_receive_read(FILE **file, int new_fd, Link msg)
{  
    memset(msg->message, 0, sizeof(msg->message));

    while(NULL != fgets(msg->message, sizeof(msg->message), *file))
    {
        write(new_fd, msg, sizeof(Node));
        
	memset(msg->message, 0, sizeof(msg->message));
    }
}

void file_receive(Link msg, int new_fd)
{
    FILE *file;

    char filename[50];

    memset(filename, 0, sizeof(filename));
    sprintf(filename, "file_transfer/file%s%s", msg->id, msg->name);

    if((file = fopen(filename, "a+")) == NULL)
    {
        printf("open error!");
	exit(1);
    }
    
    file_receive_read(&file, new_fd, msg);

    if(fclose(file) != 0)
    {
        printf("close error!");
	exit(1);
    }
    
    memset(filename, 0, sizeof(filename));
    sprintf(filename, "file_transfer/file%s%s", msg->id, msg->name);

    remove(filename);

}
