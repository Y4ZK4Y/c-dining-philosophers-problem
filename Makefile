# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: yasamankarimi <yasamankarimi@student.co      +#+                      #
#                                                    +#+                       #
#    Created: 2024/07/30 11:39:41 by yasamankari   #+#    #+#                  #
#    Updated: 2024/08/22 15:17:28 by ykarimi       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := cc
CFLAGS := -Wall -Werror -Wextra
CFLAGS := -Wall -Werror -Wextra -g -fsanitize=thread

INCLUDES := -I./include
SRC_DIR := src
INC_DIR := include
BUILD_DIR := bin

SRCS = src/error.c src/init_structs.c src/init_locks.c src/parsing.c \
		src/log_message.c src/main.c src/monitor.c src/parsing_utils.c \
		src/philo_routine.c src/time_keeping.c src/utils.c src/threads.c \
		src/philo_utils.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re memcheck