#include "../../include/my_head.h"

void delete_history(int new_fd)
{
    Node msg;

    memset(&msg, 0, sizeof(Node));

    msg.action = DELETE_CHAT_HISTORY;
    my_strcpy(msg.id, msg1.id);

    write(new_fd, &msg, sizeof(Node));
}
