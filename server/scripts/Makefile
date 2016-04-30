CC := gcc
CFLAGS := -Wall -O3
Libs = -lmy_string -L ./lib -lpthread -lsqlite3
Target := server
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += main handle_client my_socket my_register my_link my_log online_message group_chat private_chat user_function offline_msg chat_record file_send file_receive change_name change_password forget_password ban_chat
AllObjs := $(addsuffix /src/*.o,$(Modules))
