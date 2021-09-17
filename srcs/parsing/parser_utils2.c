/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:43:40 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/17 13:44:15 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	free_them(t_list *tmp, char **cmds, int i, int indice)
{
	ft_lstclear(&tmp, del_node);
	(void)i;
	(void)cmds;
	if (indice == 0)
		return (parse_er("bash: syntax error near unexpected token `;'", 1));
	else
		return (parse_er("bash: syntax error near unexpected token `|'", 1));
}
