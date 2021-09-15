/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_it.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:54:07 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/15 09:46:04 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dollar_finder(char *str, t_list **quotes)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$' && (is_between_quotes(i, quotes) != S_QUOTE)
			&& (str[i + 1] != '\0' && str[i + 1] != ' ' && str[i + 1] != '\"'))
			// && (str[i + 1] != '='))
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

char	*magic_touch(char *str)
{
	int		i;
	t_list	*tmp;
	char	*ret_str;

	tmp = NULL;
	i = quotes_finder(str, &tmp);
	if (i == -1)
	{
		ft_putstr_fd("Error: Quote not closed\n", 2);
		return (NULL);
	}
	if (i == 0)
		return (str);
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
	ft_lstclear(&tmp, del_node);
	return (ret_str);
}

char	*expand(char *tab, t_list **envl)
{
	int		tmp[3];
	char	*ret;
	char	*pmt[2];
	char	*key;
	char	*ito;
	t_envl	*var;
	t_list	*quotes;

	ret = NULL;
	quotes = NULL;
	tmp[1] = quotes_finder(tab, &quotes);
	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = dollar_finder(tab, &quotes);
	if (tmp[2] == -1)
	{
		ft_lstclear(&quotes, del_node);
		return (ft_strdup(tab));
	}
	else
	{
		tmp[2]++;
		tmp[0] = tmp[2];
		if (tab[tmp[2]] != '?')
		{
			while ((tab[tmp[2]] != ' ' && tab[tmp[2]] != '\"'
					&& tab[tmp[2]] != '\'' && tab[tmp[2]] != '$' && tab[tmp[2]] != '=')
				&& tab[tmp[2]])
				tmp[2]++;
			key = ft_substr(tab, tmp[0], tmp[2] - (tmp[0]));
			var = find_env_var(key, envl);
			free(key);
			pmt[0] = ft_strndup(tab, tmp[0] - 1);
			if (var && var->value)
			{
				pmt[1] = ft_strjoin(pmt[0], var->value);
				ret = ft_strjoin(pmt[1], &tab[tmp[2]]);
				free(pmt[1]);
			}
			else
				ret = ft_strjoin(pmt[0], &tab[tmp[2]]);
			free(pmt[0]);
		}
		else
		{
			tmp[2]++;
			pmt[0] = ft_strndup(tab, tmp[0] - 1); 
			ito = ft_itoa(g_vars.exit_code);
			pmt[1] = ft_strjoin(pmt[0], ito);
			free(ito);
			ret = ft_strjoin(pmt[1], &tab[tmp[2]]);
			free(pmt[0]);
			free(pmt[1]);
		}
		ft_lstclear(&quotes, del_node);
		tmp[1] = quotes_finder(ret, &quotes);
		if (dollar_finder(ret, &quotes) >= 0)
		{
			key = ret;
			ret = expand(key, envl);
			ft_lstclear(&quotes, del_node);
			free(key);
		}
		ft_lstclear(&quotes, del_node);
	}
	return (ret);
}
