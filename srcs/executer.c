/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:35:24 by abiari            #+#    #+#             */
/*   Updated: 2021/02/27 17:40:51 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct	s_command
{
	const char **argv;
}				t_command;

int spawn_proc(int in, int out, t_command *cmd)
{
	pid_t pid;

	if ((pid = fork()) == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		return execvp(cmd->argv[0], (char *const *)cmd->argv);
	}
	return pid;
}

int fork_pipes(int n, t_command *cmd, char **envp)
{
	int		i;
	int		in;
	int		fd[2];
	
	in = 0;
	i = 0;
	while (i < n - 1)
	{
		pipe(fd);
		spawn_proc(in, fd[1], cmd + i);
		close(fd[1]);
		in = fd[0];
		i++;
	}
	if (in != 0)
		dup2(in, 0);
	return execve(cmd[i].argv[0], (char *const *)cmd[i].argv, envp);
}

void	error()
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	exit(-1);
}

int 	main(int argc, char const *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	const char *ls[] = {"ls", "-l", 0};
	const char *awk[] = {"awk", "{print $1}", 0};
	const char *sort[] = {"sort", 0};
	const char *uniq[] = {"uniq", 0};
	t_command cmd[] = {{ls}, {awk}, {sort}, {uniq}};
	return fork_pipes(4, cmd, envp);
	
	return 0;
}