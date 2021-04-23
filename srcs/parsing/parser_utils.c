/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 11:47:42 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/04/23 13:34:10 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del_node(void *content)
{
	((t_quotes *)content)->type = 0;
	((t_quotes *)content)->closes = 0;
	((t_quotes *)content)->opens = 0;
	free(content);
}

int	parse_er(char *err, int ret)
{
	write(1, err, ft_strlen(err));
	write(1, "\n", 1);
	return (ret);
}

void	ft_free(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

int	only_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	free_the_nipples(t_list *tmp, char **cmds, int i)
{
	ft_lstclear(&tmp, del_node);
	(void)i;
	(void)cmds;
	//ft_free(cmds, i);
	return (parse_er("bash: syntax error near unexpected token `;'", 1));
}
