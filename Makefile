# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcharbon <fcharbon@student.42london.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 13:14:19 by fcharbon          #+#    #+#              #
#    Updated: 2024/05/17 19:52:11 by fcharbon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
CC := gcc
CFLAGS := -Wall -Werror -Wextra -g -pthread
SRCS := src/main.c \
		src/parsing.c \
		src/innitmate.c \
		src/utils1.c \
		src/utils2.c \
		src/threads.c \
		src/actions.c \

OBJ := $(SRCS:.c=.o)
INCLUDE := includes/philosophers.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
