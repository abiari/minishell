/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_it.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:54:07 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 16:43:15 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_gucci(char c, int i)
{
	if (i == 0)
	{
		if (ft_isalpha(c) || c == '_')
			return (1);
		return (0);
	}
	return (ft_isalnum(c) || c == '_');
}

int	dollar_finder(char *str, t_list **quotes)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && (bq(i, quotes) != S_QUOTE)
			&& (str[i + 1] != '\0' && str[i + 1] != ' ' && str[i + 1] != '\"'))
			return (i);
		i++;
	}
	return (-1);
}

char	*join_one(char *str, char c)
{
	char	*ret;
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[++i])
		ret[i] = str[i];
	ret[i] = c;
	ret[i + 1] = '\0';
	free(str);
	return (ret);
}

char	*ret_touch(char *str, t_list *tmp)
{
	char	*ret_str;
	int		i;

	i = -1;
	ret_str = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (!is_valid_quote(i, &tmp))
				ret_str = join_one(ret_str, str[i]);
			else
				continue ;
		}
		else
			ret_str = join_one(ret_str, str[i]);
	}
	return (ret_str);
}

char	*magic_touch(char *str)
{
	int		i;
	t_list	*tmp;
	char	*ret_str;

	tmp = NULL;
	i = quotes_finder(str, &tmp);
	if (i == -1)
		return (quote_error());
	if (i == 0)
		return (str);
	ret_str = ret_touch(str, tmp);
	ft_lstclear(&tmp, del_node);
	return (ret_str);
}
