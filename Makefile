# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 17:19:26 by abiari            #+#    #+#              #
#    Updated: 2021/09/11 13:53:09 by abiari           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = msh
CC = gcc
CFLAGS = -Wall -Werror -Wextra -lreadline -g3
RDLFLAGS = -L ~/goinfre/.brew/opt/readline/lib\
-I ~/goinfre/.brew/opt/readline/include

SRC = srcs/main.c srcs/builtins/msh_cd.c srcs/builtins/msh_pwd.c\
srcs/utils/env_utils.c srcs/utils/envp_to_envl.c srcs/utils/lst_append.c\
srcs/parsing/cmd_helper.c srcs/parsing/cmd_spliter.c\
srcs/parsing/commas_helpers.c srcs/parsing/helpers.c srcs/parsing/parser.c\
srcs/parsing/parser_utils.c srcs/parsing/pipe_it.c\
srcs/parsing/quotes_helpers.c srcs/parsing/red_helper.c srcs/parsing/reddit.c\
srcs/parsing/space_it.c srcs/parsing/utils.c srcs/parsing/expand_it.c\
srcs/execution/pipeline.c srcs/execution/redirection.c\
srcs/execution/executer.c srcs/signals/sig_handlers.c srcs/builtins/msh_echo.c\
srcs/builtins/msh_env.c srcs/builtins/msh_exit.c srcs/builtins/msh_export.c\
srcs/builtins/msh_unset.c srcs/utils/ft_ll_itoa.c srcs/utils/heredoc.c\
srcs/utils/rand_gen.c srcs/utils/delete_env_var.c srcs/execution/exec_utils.c\
srcs/builtins/export_utils.c

all: $(NAME)

$(NAME): $(SRC)
	make -C ./libft && make bonus -C ./libft && make clean -C ./libft
	$(CC) $(CFLAGS) $(RDLFLAGS) $(SRC) libft/libft.a -o $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re : fclean all

.PHONY: clean fclean all re
