# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: yasamankarimi <yasamankarimi@student.co      +#+                      #
#                                                    +#+                       #
#    Created: 2024/07/30 11:39:41 by yasamankari   #+#    #+#                  #
#    Updated: 2024/08/01 11:36:02 by ykarimi       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := cc
CFLAGS := -Wall -Werror -Wextra
INCLUDES := -I./include
BUILD_DIR := bin
SRC_DIR := src
INC_DIR := include
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

-include $(DEPS)

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME).a

re: fclean all

test:
	valgrind --leak-check=full --show-leak-kinds=all
	
.PHONY: all clean fclean re