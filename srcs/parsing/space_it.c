/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:56:13 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 19:22:12 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*spaces(char *str, t_list **lst)
{
	int		count;
	int		*spaces;
	t_list	*tmp;

	tmp = *lst;
	count = spaces_count(str, tmp, ' ');
	if (count == 0)
	{
		ft_lstclear(&tmp, del_node);
		return (NULL);
	}
	spaces = malloc((sizeof(int) * count) + sizeof(int));
	if (!spaces)
	{
		ft_lstclear(&tmp, del_node);
		return (NULL);
	}
	spaces_array(spaces, str, tmp, ' ');
	ft_lstclear(&tmp, del_node);
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
		tab = (char **)malloc((i + 1) * sizeof(char *));
		j = -1;
		while (++j < i)
		{
			tab[j] = between_valid_spaces(cmd, j, space);
		}
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

int	c_k(char c)
{
	if (c && c != ' ')
		return (1);
	return (0);
}

char	*rm_dup_spaces(char	*s, t_list **q)
{
	char	*lol[3];
	int		i[3];

	i[0] = 0;
	lol[2] = ft_strdup("");
	lol[1] = NULL;
	while (s[i[0]])
	{
		while (s[i[0]] && s[i[0]] == ' ' && bq(i[0], q) == 0)
			i[0]++;
		i[1] = i[0];
		while (c_k(s[i[0]]) || (s[i[0]] == ' ' && bq(i[0], q) != 0))
			i[0]++;
		i[2] = i[0];
		if (i[1] != i[2])
		{
			lol[1] = ft_strjoin(lol[2], " ");
			free(lol[2]);
			lol[0] = ft_substr(s, i[1], i[2] - i[1]);
			lol[2] = ft_strjoin(lol[1], lol[0]);
			free(lol[0]);
			free(lol[1]);
		}
	}
	return (lol[2]);
}

char	**space_it(char *str)
{
	t_list	*tmp;
	int		*space;
	char	**tab;
	char	*cmd[2];
	int		i[2];

	tmp = NULL;
	i[1] = quotes_finder(str, &tmp);
	cmd[0] = rm_dup_spaces(str, &tmp);
	ft_lstclear(&tmp, del_node);
	tmp = NULL;
	space = NULL;
	i[1] = quotes_finder(cmd[0], &tmp);
	space = spaces(cmd[0], &tmp);
	tab = space_spliter(space, cmd[0]);
	i[0] = -1;
	while (tab[++i[0]])
	{
		cmd[1] = tab[i[0]];
		tab[i[0]] = magic_touch(tab[i[0]]);
		if (ft_strchr(cmd[1], '\"') || ft_strchr(cmd[1], '\''))
			free(cmd[1]);
	}
	free(cmd[0]);
	return (tab);
}
