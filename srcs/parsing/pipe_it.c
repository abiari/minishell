/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:43:03 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/06 16:06:45 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*pipes(char *str, t_list **lst)
{
	int		count;
	int		*pipes;
	t_list	*tmp;

	tmp = *lst;
	count = char_counter(str, tmp, '|');
	if (count == 0)
		return (NULL);
	pipes = malloc((sizeof(int) * count) + sizeof(int));
	if (!pipes)
		return (NULL);
	char_array(pipes, str, tmp, '|');
	return (pipes);
}


char	**pipe_spliter(int *pipe, char *cmd)
{
	char	**tab;
	int		i;
	int		j;

	j = -1;
	i = 0;
	tab = NULL;
	if (pipe != NULL)
	{
		i = cmd_counter(pipe, cmd, 1);
		if (i == -1)
			return (NULL);
		tab = (char **)malloc((i + 1) * sizeof(char *));
		j = -1;
		while (++j < i)
			tab[j] = ft_strdup(fill_command(cmd, j, pipe));
		tab[j] = NULL;
		free(pipe);
	}
	else
	{
		tab = (char **)malloc((2) * sizeof(char *));
		tab[0] = ft_strdup(cmd);
		tab[1] = NULL;
	}
	return (tab);
}

char	**pipe_it(char *cmd)
{
	t_list	*tmp;
	int		*pipe;
	int		ret;
	char	**tab;

	tmp = NULL;
	pipe = NULL;
	ret = quotes_finder(cmd, &tmp);
	pipe = pipes(cmd, &tmp);
	tab = pipe_spliter(pipe, cmd);
	ft_lstclear(&tmp, del_node);
	return (tab);
}
