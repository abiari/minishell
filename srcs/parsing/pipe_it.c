/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:43:03 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/17 14:18:00 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*pipes(char *str, t_list **lst)
{
	int		count;
	int		*pipes;
	t_list	*tmp;

	tmp = *lst;
	count = char_counter(str, tmp, '|');
	if (count == 0)
		return (NULL);
	pipes = malloc((sizeof(int) * count) + sizeof(int));
	if (!pipes)
		return (NULL);
	char_array(pipes, str, tmp, '|');
	return (pipes);
}

char	**pipe_it(char *cmd)
{
	t_list	*tmp;
	int		*pipe;
	int		ret;
	char	**tab;

	tmp = NULL;
	pipe = NULL;
	ret = quotes_finder(cmd, &tmp);
	if (ret == -1)
	{
		ft_putstr_fd("Syntax error: Quote not closed\n", 2);
		return (NULL);
	}
	pipe = pipes(cmd, &tmp);
	tab = pipe_spliter(pipe, cmd);
	ft_lstclear(&tmp, del_node);
	return (tab);
}
