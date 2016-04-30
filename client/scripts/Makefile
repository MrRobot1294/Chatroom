CC := gcc
CFLAGS := -Wall -O3
Libs = -lmy_string -L ./lib -lpthread -lncursesw
Target := client
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += main my_connect my_menu my_register my_select my_log chat_interface handle_server group_chat private_chat check_history delete_history file_send file_receive my_link change_name send_face change_password forget_password admin_chat_interface ban_chat
AllObjs := $(addsuffix /src/*.o,$(Modules))
