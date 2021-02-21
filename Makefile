# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiari <abiari@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 17:19:26 by abiari            #+#    #+#              #
#    Updated: 2021/02/21 15:01:24 by abiari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = msh
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = srcs/main.c

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) libft/libft.a -o msh

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re