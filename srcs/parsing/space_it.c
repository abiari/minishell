/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:56:13 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/17 14:22:03 by ael-bagh         ###   ########.fr       */
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

char	*rm_dup_spaces(char	*str, t_list **quotes)
{
	t_list	*tmp;
	char	*lol;
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
		while (str[i] && str[i] == ' ' && is_between_quotes(i, &tmp) == 0)
			i++;
		start = i;
		while (str[i] && ((str[i] != ' ') || (str[i] == ' ' && is_between_quotes(i, &tmp) != 0)))
			i++;
		end = i;
		if (start != end)
		{
			tmp_str = ft_strjoin(cmd, " ");
			free(cmd);
			lol = ft_substr(str, start, end - start);
			cmd = ft_strjoin(tmp_str, lol);
			free(lol);
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
	char	*tmp2;
	
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
	{
		tmp2 = tab[i];
		tab[i] = magic_touch(tab[i]);
		if (ft_strchr(tmp2, '\"') || ft_strchr(tmp2, '\''))
			free(tmp2);
	}
	free(cmd);
	return (tab);
}
