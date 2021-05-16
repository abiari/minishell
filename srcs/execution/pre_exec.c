/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:43:08 by abiari            #+#    #+#             */
/*   Updated: 2021/05/16 16:46:26 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_double(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*bin_path(char *cmd, t_list *envl)
{
	char	**split_path;
	char	*path;
	int		bin_fd;
	int		i = 0;

	split_path = ft_split((find_env_var("PATH", &envl))->value, ':');
	if (!split_path)
	{
		ft_putstr_fd("msh: $PATH variable not found", 2);
		return(NULL);
	}
	while (split_path[i])
	{
		split_path[i] = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(split_path[i], cmd);
		bin_fd = open(path, O_RDONLY);
		if (bin_fd > 0)
		{
			path = ft_strdup(ft_strjoin(split_path[i], cmd));
			free_double(split_path);
			close(bin_fd);
			return (path);
		}
		i++;
	}
	free_double(split_path);
	return(NULL);
}

void	check_n_exec(char *cmd, t_list *envl)
{
	int	fd;
	char	*bin;

	bin = cmd;
	fd = open(cmd, O_RDONLY);
	if (fd < 0)
	{
		bin = bin_path(cmd, envl);
		close(fd);
	}
	if (bin == NULL)
	{
		ft_putstr_fd("msh: command not found", 2);
		return ;
	}
	else
	{
		// fork_pipes
	}
}
