/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 11:47:42 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/17 13:43:58 by ael-bagh         ###   ########.fr       */
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

void	delist(void *content)
{
	free(content);
}

void	del_node_r(void *content)
{
	((t_red *)content)->type = 0;
	((t_red *)content)->index = 0;
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
