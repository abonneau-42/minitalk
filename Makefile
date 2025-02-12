CC = cc
NAME_CLIENT = client
NAME_SERVER = server
BUILD_DIR = .build
INCLUDES_DIR = ./includes
HEADER = minitalk.h

CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES_DIR)
INCLUDES_FILES = $(addprefix $(INCLUDES_DIR)/, $(HEADER))

SRCS_DIR = srcs

SRCS_FILES_CLIENT = 	client/client.c \
						client/client_message.c \
						utils.c \

SRCS_FILES_SERVER = 	server/server.c \
						server/server_message.c \
						utils.c \

SRCS_CLIENT = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES_CLIENT))
SRCS_SERVER = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES_SERVER))

OBJS_CLIENT = $(patsubst $(SRCS_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS_CLIENT))
OBJS_SERVER = $(patsubst $(SRCS_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS_SERVER))

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES_FILES) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME_SERVER) $(NAME_CLIENT) 

re: fclean all

.PHONY: all clean fclean re