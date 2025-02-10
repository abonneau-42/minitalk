CC = cc
NAME_CLIENT = client
NAME_SERVER = server
BUILD_DIR = .build
INCLUDES_DIR = ./includes
HEADER_CLIENT = client.h
HEADER_SERVER = server.h

CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES_DIR)
INCLUDES_FILES_CLIENT = $(addprefix $(INCLUDES_DIR)/, $(HEADER_CLIENT))
INCLUDES_FILES_SERVER = $(addprefix $(INCLUDES_DIR)/, $(HEADER_SERVER))

SRCS_DIR = srcs

SRCS_FILES_CLIENT = 	client.c \

SRCS_FILES_SERVER = 	server.c \

SRCS_CLIENT = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES_CLIENT))
SRCS_SERVER = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES_SERVER))

OBJS_CLIENT = $(patsubst $(SRCS_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS_CLIENT))
OBJS_SERVER = $(patsubst $(SRCS_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS_SERVER))

all: $(NAME_SERVER) $(NAME_CLIENT) 

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES_FILES_CLIENT) $(INCLUDES_FILES_SERVER) Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME_SERVER) $(NAME_CLIENT) 

re: fclean all

.PHONY: all clean fclean re