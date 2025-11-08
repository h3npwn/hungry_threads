# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abahja <abahja@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/04 09:30:00 by abahja            #+#    #+#              #
#    Updated: 2025/07/20 21:46:36 by abahja           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Werror -Wextra -Wall
SRC = philo.c srcs/utils_parse.c srcs/init_data.c srcs/the_game.c srcs/time.c \
		srcs/monitor.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: $(NAME)
	gdb ./$(NAME) 5 800 200 200

.PHONY: all clean fclean re debug
