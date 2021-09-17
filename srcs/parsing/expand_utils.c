/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 18:23:54 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/17 18:27:00 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*norm_expand(int tmp, char *tab, t_list **envl)
{
	t_envl	*var;
	char	*pmt[4];
	int		t[2];

	t[0] = 0;
	t[1] = tmp;
	while (is_gucci(tab[t[1]], t[0]) && tab[t[1]])
	{
		t[0]++;
		t[1]++;
	}
	pmt[0] = ft_substr(tab, tmp, t[1] - tmp);
	var = find_env_var(pmt[0], envl);
	free(pmt[0]);
	pmt[1] = ft_strndup(tab, tmp - 1);
	if (var && var->value)
	{
		pmt[2] = ft_strjoin(pmt[1], var->value);
		pmt[3] = ft_strjoin(pmt[2], &tab[t[1]]);
		free(pmt[2]);
	}
	else
		pmt[3] = ft_strjoin(pmt[1], &tab[t[1]]);
	free(pmt[1]);
	return (pmt[3]);
}

char	*norm_expand2(int tmp, char *tab)
{
	char	*pmt[3];
	char	*expanded;
	int		i;

	i = tmp + 1;
	pmt[0] = ft_strndup(tab, tmp - 1);
	pmt[2] = ft_itoa(g_vars.exit_code);
	pmt[1] = ft_strjoin(pmt[0], pmt[2]);
	free(pmt[2]);
	expanded = ft_strjoin(pmt[1], &tab[i]);
	free(pmt[0]);
	free(pmt[1]);
	return (expanded);
}

char	*norm_expand3(char *pmt3, t_list **envl)
{
	char	*ret;

	ret = expand(pmt3, envl);
	free(pmt3);
	return (ret);
}

char	*expanded(t_list *quotes, char *tab)
{
	ft_lstclear(&quotes, del_node);
	return (ft_strdup(tab));
}

char	*expand(char *tab, t_list **envl)
{
	int		tmp[2];
	char	*pmt;
	t_list	*quotes;

	pmt = NULL;
	quotes = NULL;
	tmp[0] = quotes_finder(tab, &quotes);
	tmp[1] = dollar_finder(tab, &quotes);
	if (tmp[1] == -1)
		return (expanded(quotes, tab));
	else
	{
		tmp[1]++;
		if (tab[tmp[1]] != '?')
			pmt = norm_expand(tmp[1], tab, envl);
		else
			pmt = norm_expand2(tmp[1], tab);
		ft_lstclear(&quotes, del_node);
		tmp[0] = quotes_finder(pmt, &quotes);
		if (dollar_finder(pmt, &quotes) >= 0)
			pmt = norm_expand3(pmt, envl);
		ft_lstclear(&quotes, del_node);
	}
	return (pmt);
}
