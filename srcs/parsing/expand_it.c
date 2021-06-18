/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_it.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:54:07 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/18 15:57:39 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		char_finder(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
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
	ret = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[++i])
		ret[i] = str[i];
	ret[i] = c;
	ret[i + 1] = '\0';
	free(str);
	return (ret);
}

char	*magic_touch(char *str)
{
	int	i;
	t_list	*tmp;
	char	*ret_str;

	tmp = NULL;
	ret_str = ft_strdup("");
	i = quotes_finder(str, &tmp);
	i = -1;
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

char	*expand(char *tab, t_list **envl)
{
	int		i;
	int		tmp[2];
	char	*ret;
	char	*key;
	t_envl	*var;
	t_list	*quotes;

	ret = NULL;
	quotes = NULL;
	i = quotes_finder(tab, &quotes);
	i = -1;
	tmp[0] = 0;
	tmp[1] = 0;
	if (char_finder(tab, '$') == -1 || (char_finder(tab, '$') != -1 && is_between_quotes(char_finder(tab, '$'), &quotes) == S_QUOTE))
		return (tab);
	while (tab[++i])
	{
		if (tab[i] == '\\' && (i++))
	 			continue ;
		if (tab[i] == '$' && is_between_quotes(i, &quotes) != S_QUOTE)
		{
			tmp[0] = i;
			while ((tab[i] != ' ' && tab[i] != '\"'&& tab[i] != '\'') && tab[i])
				i++;
			key = ft_substr(tab, tmp[0] + 1, i - (tmp[0] + 1));
			var = find_env_var(key, envl);
			ret = ft_strndup(tab, tmp[0]);
			if (var)
				ret = ft_strjoin(ret, var->value);
			ret = ft_strjoin(ret, &tab[i]);
			ft_lstclear(&quotes, del_node);
			tmp[1] = quotes_finder(ret, &quotes);
			if (char_finder(ret, '$') != -1 && is_between_quotes(char_finder(ret, '$'), &quotes) != S_QUOTE)
				expand(ret, envl);
			if (tab[i] == '\0')
				return (ret);
		}
	}
	return (ret);
}

char	**spank_it(char **tab, t_list **envl)
{
	int		i;
	char	**ret;
	char	**final;

	i = two_d_counter(tab);
	ret = (char **)malloc((i + 1) * sizeof(char *));
	i = -1;
	while (tab[++i])
		ret[i] = expand(tab[i], envl);
	ret[i] = NULL;
	final = (char **)malloc((i + 1) * sizeof(char *));
	i = -1;
	while (ret[++i])
		final[i] = magic_touch(ret[i]);
	final[i] = NULL;
	return (final);
}
