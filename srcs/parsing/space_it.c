/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:56:13 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/01 14:07:25 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*spaces(char *str, t_list **lst)
{
	int		count;
	int		*spaces;
	t_list	*tmp;

	tmp = *lst;
	count = char_counter(str, tmp, ' ');
	if (count == 0)
		return (NULL);
	spaces = malloc((sizeof(int) * count) + sizeof(int));
	if (!spaces)
		return (NULL);
	char_array(spaces, str, tmp, ' ');
	return (spaces);
}

char	**space_spliter(int *space, char *cmd)
{
	char	**tab;
	int		i;
	int		j;

	j = -1;
	i = 0;
	if (space != NULL)
	{
		i = space_counter(space);
		if (i == -1)
			return (NULL);
		tab = (char **)malloc((i + 1) * sizeof(char *));
		j = -1;
		while (++j < i)
			tab[j] = ft_strdup_dzeb(fill_command(cmd, j, space));
		tab[j] = NULL;
		free(space);
	}
	else
	{
		tab = (char **)malloc((2) * sizeof(char *));
		tab[0] = ft_strdup(cmd);
		tab[1] = NULL;
	}
	return (tab);
}

char	**space_it(char *red)
{
	t_list	*tmp;
	int		*space;
	char	**tab;

	tmp = NULL;
	space = NULL;
	quotes_finder(red, &tmp);
	space = spaces(red, &tmp);
	tab = space_spliter(space, red);
	ft_lstclear(&tmp, del_node);
	return (tab);
}

char	*split_ws(char *red)
{
	char **tab;
	int		i;
	char *cmd;

	i = -1;
	tab = NULL;
	cmd = NULL;
	tab = space_it(red);
	if (tab)
		if (two_d_counter(tab) > 1)
			while (tab[++i])
			{
				cmd = ft_strjoin(cmd, tab[i]);
			}
	return (cmd);
}

char		*get_cmd(char **red, char **pipelist)
{
	int	i;
	char	*cmd;

	(void)pipelist;
	i = -1;
	cmd = NULL;
	if (red)
	{
		while(red[++i])
		{
			if ((only_char(' ', red[i]) && i == 0) || red[1] == NULL)
				return (NULL);
			cmd = split_ws(red[i]);
		}
	}
	return (cmd);
}
