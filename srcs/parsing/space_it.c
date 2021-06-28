/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:56:13 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/27 21:22:45 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	spaces_array(int *spaces,char *str, t_list *tmp, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == c && is_between_quotes(i, &tmp) == 0)
		{
			while (str[i] == c && is_between_quotes(i, &tmp) == 0)
				i++;
			spaces[count] = i;
			count++;
		}
	}
	spaces[count] = -2;
}

int	spaces_count(char *str, t_list *tmp, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == c && is_between_quotes(i, &tmp) == 0)
		{
			while (str[i] == c && is_between_quotes(i, &tmp) == 0)
				i++;
			count++;
		}
	}
	return (count);
}

char	*between_valid_spaces(char *cmd, int index, int	*space)
{
	int		i;
	int		j;
	int		len;
	int		last;
	char	*tmp;

	last = last_char(space);
	i = 0;
	len = 0;
	if (index != last - 1)
	{
		len = space[index + 1] - space[index] - 1;
		i = space[index];
	}
	else
	{
		len = ft_strlen(cmd) - space[index];
		i = space[index];	
	}
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

int	*spaces(char *str, t_list **lst)
{
	int		count;
	int		*spaces;
	t_list	*tmp;

	tmp = *lst;
	count = spaces_count(str, tmp, ' ');
	if (count == 0)
		return (NULL);
	spaces = malloc((sizeof(int) * count) + sizeof(int));
	if (!spaces)
		return (NULL);
	spaces_array(spaces, str, tmp, ' ');
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
			tab[j] = ft_strdup(between_valid_spaces(cmd, j, space));
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

char	*rm_dup_spaces(char	*str, t_list **quotes)
{
	t_list	*tmp;
	char	*tmp_str;
	char	*cmd;
	int		i;
	int		start;
	int		end;

	tmp = *quotes;
	i = 0;
	cmd = ft_strdup("");
	tmp_str = NULL;
	while (str[i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		while (str[i] && str[i] == ' ' && is_between_quotes(i, &tmp) == 0)
			i++;
		start = i;
		while (str[i] && ((str[i] != ' ') || (str[i] == ' ' && is_between_quotes(i, &tmp) != 0)))
			i++;
		end = i;
		if (start != end)
		{
			tmp_str = ft_strjoin(cmd, " ");
			cmd = tmp_str;
			cmd = ft_strjoin(cmd, ft_substr(str, start, end - start));
			free(tmp_str);
		}
	}
	return (cmd);
}

char	**space_it(char *str)
{
	t_list	*tmp;
	int		*space;
	int		ret;
	char	**tab;
	char	*cmd;
	int		i;
	
	tmp = NULL;
	ret = quotes_finder(str, &tmp);
	cmd = rm_dup_spaces(str, &tmp);
	ft_lstclear(&tmp, del_node);
	tmp = NULL;
	space = NULL;
	ret = quotes_finder(cmd, &tmp);
	space = spaces(cmd, &tmp);
	tab = space_spliter(space, cmd);
	i = -1;
	while (tab[++i])
		tab[i] = magic_touch(tab[i]);
	ft_lstclear(&tmp, del_node);
	return (tab);
}

// char	*split_ws(char *red, t_list **envl)
// {
// 	char **tab;
// 	int		i;
// 	char *cmd;

// 	i = -1;
// 	tab = NULL;
// 	cmd = NULL;
// 	tab = space_it(red, &envl);
// 	if (tab)
// 		if (two_d_counter(tab) > 1)
// 			while (tab[++i])
// 			{
// 				cmd = ft_strjoin(cmd, tab[i]);
// 			}
// 	return (cmd);
// }

// char		*get_cmd(char **red, char **pipelist)
// {
// 	int	i;
// 	int ret;
// 	char	*cmd;

// 	(void)pipelist;
// 	i = -1;
// 	ret = 0;
// 	cmd = NULL;
// 	if (red)
// 	{
// 		while(red[++i])
// 		{
// 			if ((only_char(' ', red[i]) && i == 0) || red[1] == NULL)
// 				return (NULL);
// 			cmd = split_ws(red[i]);
// 		}
// 	}
// 	return (cmd);
// }
