# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 17:19:26 by abiari            #+#    #+#              #
#    Updated: 2021/03/11 12:43:58 by abiari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = msh
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = srcs/main.c srcs/builtins/msh_cd.c srcs/builtins/msh_pwd.c\
srcs/utils/env_utils.c srcs/utils/env_utils2.c srcs/utils/lst_append.c

all: $(NAME)

$(NAME):
	make -C /libft
	$(CC) $(CFLAGS) $(SRC) libft/libft.a -o msh

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
