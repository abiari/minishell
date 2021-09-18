/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reddit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:37:52 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 16:33:41 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**red_spliter(int *red_arr, char *cmd, t_list *quotes)
{
	char	**tab;
	int		i;
	int		j;

	j = -1;
	i = 0;
	if (red_arr != NULL)
	{
		i = red_counter(cmd, quotes) + 1;
		if (i == -1)
			return (NULL);
		tab = (char **)malloc((i + 1) * sizeof(char *));
		j = -1;
		while (++j < i)
			tab[j] = fill_red(cmd, j, red_arr);
		tab[j] = NULL;
		free(red_arr);
	}
	else
		return (NULL);
	return (tab);
}

char	*check_red_norm(char **red)
{
	char	*tab;

	if (only_char(' ', red[0]) || red[0] == '\0')
		tab = ft_strdup("");
	else
	{
		tab = ft_strdup(red[0]);
		tab = my_strjoin(tab, " ");
	}
	return (tab);
}

char	**check_red_norm1(int i, char **red)
{
	char	**tab;
	char	**spaces;
	char	*tmp;
	int		j;

	tab = malloc((i + 1) * sizeof(char *));
	tab[0] = check_red_norm(red);
	j = 0;
	while (red[++j])
	{
		spaces = space_it(red[j]);
		tab[j] = ft_strdup(spaces[0]);
		if (two_d_counter(spaces) > 0)
		{
			tmp = to_join(spaces);
			tab[0] = my_strjoin(tab[0], tmp);
			tab[0] = my_strjoin(tab[0], " ");
			free(tmp);
		}
		if (spaces)
			free_chard(spaces);
	}
	tab[j] = NULL;
	return (tab);
}

char	**check_red(char **red, t_list *quotes, char *cmd)
{
	char	**tab;
	int		i;

	i = red_counter(cmd, quotes) + 1;
	if (!red)
		return (NULL);
	tab = check_red_norm1(i, red);
	return (tab);
}

char	**reddit(char *cmd)
{
	t_list	*tmp;
	t_list	*tp;
	int		*red_arr;
	int		ret;
	char	**redit[2];

	tmp = NULL;
	tp = NULL;
	ret = quotes_finder(cmd, &tmp);
	ret = red_finder(cmd, &tp, &tmp);
	red_arr = reds(cmd, &tmp);
	redit[0] = red_spliter(red_arr, cmd, tmp);
	redit[1] = check_red(redit[0], tmp, cmd);
	if (redit[0])
		free_chard(redit[0]);
	ft_lstclear(&tmp, del_node);
	ft_lstclear(&tp, del_node_r);
	return (redit[1]);
}
