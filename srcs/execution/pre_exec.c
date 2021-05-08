/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:43:08 by abiari            #+#    #+#             */
/*   Updated: 2021/05/08 13:12:24 by abiari           ###   ########.fr       */
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
	int	bin_fd;

	split_path = ft_split((find_env_var("PATH", &envl))->var, ':');
	if (!split_path)
	{
		// ft_putstr_fd("msh: $PATH variable corrupted", 2);
		return(NULL);
	}
	while (split_path)
	{
		bin_fd = open(ft_strjoin(*split_path, cmd), O_RDONLY);
		if (bin_fd > 0)
		{
			path = ft_strdup(ft_strjoin(*split_path, cmd));
			free_double(split_path);
			close(bin_fd);
			return (path);
		}
		split_path++;
	}
	free_double(split_path);
	return(NULL);
}
