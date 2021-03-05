/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 17:35:24 by abiari            #+#    #+#             */
/*   Updated: 2021/03/05 14:27:19 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct	s_command
{
	const char **argv;
}				t_command;

int spawn_proc(int in, int out, t_command *cmd, char *envp[])
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
		return execve(cmd->argv[0], (char *const *)cmd->argv, envp);
	}
	return pid;
}

int fork_pipes(int n, t_command *cmd, char **envp)
{
	int		i;
	int		in;
	int		fd[2];
	pid_t	pid;
	int ret = 0;
	
	in = 0;
	i = 0;
	while (i < n - 1)
	{
		pipe(fd);
		spawn_proc(in, fd[1], cmd + i, envp);
		close(fd[1]);
		if (in != 0)
			close(in);
		in = fd[0];
		i++;
	}
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	pid = fork();
	if (pid == 0)
		execve(cmd[i].argv[0], (char *const *)cmd[i].argv, envp);
	// while (wait(NULL) != -1);
	while (waitpid(-1, &ret, 0) != -1);
		//printf("%d\n", WEXITSTATUS(ret));
	return (ret);
}

void	error()
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	exit(-1);
}

int 	main(int argc, char const *argv[], char **envp)
{
	int ret;
	(void)argc;
	(void)argv;
	const char *ls[] = {"/bin/cat", 0};
	// const char *awk[] = {"./program", 0};
	const char *sort[] = {"/bin/ls", "-la", 0};
	const char *uniq[] = {"/usr/bin/sort", 0};
	t_command cmd[] = {{ls}/*, {awk}*/, {sort}, {uniq}};
	ret = fork_pipes(3, cmd, envp);
	// while(1);
	return(ret);
}