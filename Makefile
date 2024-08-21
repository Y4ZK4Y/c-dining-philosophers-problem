# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: yasamankarimi <yasamankarimi@student.co      +#+                      #
#                                                    +#+                       #
#    Created: 2024/07/30 11:39:41 by yasamankari   #+#    #+#                  #
#    Updated: 2024/08/20 21:24:17 by yasamankari   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := cc
CFLAGS := -Wall -Werror -Wextra -pthread -g
# CFLAGS := -Wall -Werror -Wextra -fsanitize=thread

INCLUDES := -I./include
SRC_DIR := src
INC_DIR := include
BUILD_DIR := bin

SRCS = src/error_handling.c src/init.c src/input.c \
		src/log.c src/main.c src/monitor.c src/parsing_input_utils.c \
		src/philo_life_cycle.c src/time.c src/utils.c src/create_threads.c

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