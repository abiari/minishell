/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_it_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:37 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/17 18:29:12 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**pp_spliter2(int *pipe)
{
	free(pipe);
	return (NULL);
}

char	**pp_spliter3(char *cmd)
{
	char	**tab;

	tab = (char **)malloc((2) * sizeof(char *));
	tab[0] = ft_strdup(cmd);
	tab[1] = NULL;
	return (tab);
}

char	**pp_spliter4(int *pipe, char *cmd, int i)
{
	char	**tab;
	char	*tmp;
	int		j;

	tab = (char **)malloc((i + 1) * sizeof(char *));
	j = -1;
	while (++j < i)
	{
		tmp = fill_command(cmd, j, pipe);
		tab[j] = tmp;
	}
	tab[j] = NULL;
	free(pipe);
	return (tab);
}

char	**pipe_spliter(int *pipe, char *cmd)
{
	char	**tab;
	int		i;

	if (pipe)
	{
		i = cmd_counter(pipe, cmd, 1);
		if (i == -1)
			tab = pp_spliter2(pipe);
		tab = pp_spliter4(pipe, cmd, i);
	}
	else
		tab = pp_spliter3(cmd);
	return (tab);
}
