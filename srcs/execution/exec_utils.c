/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 11:13:07 by abiari            #+#    #+#             */
/*   Updated: 2021/09/10 11:15:31 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_dir(char *exec)
{
	DIR	*dir_name;

	dir_name = opendir(exec);
	if (dir_name)
	{
		if (closedir(dir_name) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			return (-1);
		}
		return (1);
	}
	return (0);
}

char	*check_exec(char *cmd, t_list *envl)
{
	char	*bin;
	int		fd;

	bin = cmd;
	if (bin[0] == '\0')
		return (bin);
	fd = open(bin, O_RDONLY);
	if (fd < 0)
		bin = bin_path(bin, envl);
	close(fd);
	return (bin);
}

int	is_builtin(char *cmd)
{
	if ((ft_strcmp("echo", cmd) == 0) || (ft_strcmp("env", cmd) == 0)
		|| (ft_strcmp("cd", cmd) == 0) || (ft_strcmp("export", cmd) == 0)
		|| (ft_strcmp("pwd", cmd) == 0) || (ft_strcmp("exit", cmd) == 0)
		|| (ft_strcmp("unset", cmd) == 0))
		return (1);
	else if ((ft_strcmp("ECHO", cmd) == 0) || (ft_strcmp("ENV", cmd) == 0)
		|| (ft_strcmp("CD", cmd) == 0) || (ft_strcmp("EXPORT", cmd) == 0)
		|| (ft_strcmp("PWD", cmd) == 0) || (ft_strcmp("EXIT", cmd) == 0)
		|| (ft_strcmp("UNSET", cmd) == 0))
		return (2);
	else
		return (0);
}

int	check_if_builtin(t_pipeline *cmd, t_list **envl)
{
	int	ret;

	ret = is_builtin(cmd->cmd[0]);
	if (ret != 1)
	{
		cmd->cmd[0] = check_exec(cmd->cmd[0], *envl);
		if (cmd->cmd[0] == NULL)
			return (1);
	}
	return (0);
}
