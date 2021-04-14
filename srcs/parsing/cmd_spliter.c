/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_spliter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 11:53:48 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/04/14 11:54:51 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fill_command(char *cmd, int index, int *comma)
{
	int		i;
	int		j;
	int		len;
	int		last;
	char	*tmp;

	last = last_comma(comma);
	len = len_init(index, comma, last, cmd);
	i = i_init(index, comma, last, cmd);
	tmp = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	while (j < len)
	{
		tmp[j] = cmd[i];
		i++;
		j++;
	}
	tmp[len] = '\0';
	return (tmp);
}

int	check_first_cmd(char *cmd, int first_comma)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (i < first_comma)
	{
		if (cmd[i] != ' ')
			flag = 1;
		i++;
	}
	if (i == 0 || flag == 0)
		return (-1);
	return (1);
}

int	cmd_counter(int *comma, char *cmd)
{
	int	i;

	i = 0;
	while (comma[i] != -2)
		i++;
	if (check_first_cmd(cmd, comma[0]) == -1)
		return (parse_er("bash: syntax error near unexpected token `;'", -1));
	if (check_last_cmd(cmd, comma[i - 1]))
		i++;
	return (i);
}

char	**cmds_spliter(int *comma, char *cmd)
{
	char	**tab;
	int		i;
	int		j;

	j = -1;
	i = 0;
	if (comma != NULL)
	{
		i = cmd_counter(comma, cmd);
		if (i == -1)
			return (NULL);
		tab = (char **)malloc((i + 1) * sizeof(char *));
		j = -1;
		while (++j < i)
			tab[j] = ft_strdup_dzeb(fill_command(cmd, j, comma));
		tab[j] = NULL;
		free(comma);
	}
	else
	{
		tab = (char **)malloc((2) * sizeof(char *));
		tab[0] = ft_strdup_dzeb(cmd);
		tab[1] = NULL;
	}
	return (tab);
}

char	**split_cmds(char *cmd)
{
	t_list	*tmp;
	int		*comma;
	int		ret;
	char	**tab;

	tmp = NULL;
	comma = NULL;
	ret = quotes_finder(cmd, &tmp);
	if (ret == -1)
	{
		ft_putstr_fd("Multiple lines command\n", 1);
		return (NULL);
	}
	comma = commas(cmd, &tmp);
	tab = cmds_spliter(comma, cmd);
	ft_lstclear(&tmp, del_node);
	return (tab);
}
