/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:37:19 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/09/18 17:50:03 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*norm_main(t_list *tmp[2], char *exp, int i)
{
	if (i == 0)
	{
		ft_putstr_fd("Quotes unclosed\n", 2);
		ft_lstclear(&tmp[0], del_node);
		free(exp);
		return (NULL);
	}
	else
	{
		ft_lstclear(&tmp[0], del_node);
		ft_lstclear(&tmp[1], del_node_r);
		free(exp);
		return (NULL);
	}
	return (NULL);
}

t_list	*norm_main2(t_list *tmp[2], char *exp, char **pipe)
{
	ft_lstclear(&tmp[0], del_node);
	ft_lstclear(&tmp[1], del_node_r);
	if (pipe)
		free_chard(pipe);
	free(exp);
	return (NULL);
}

void	norm_main3(t_list *tmp[2], char *exp)
{
	ft_lstclear(&tmp[0], del_node);
	ft_lstclear(&tmp[1], del_node_r);
	free(exp);
}

t_list	*norm_main4(t_list *tmp[2], char *exp)
{
	int	ret;

	ret = quotes_finder(exp, &tmp[0]);
	if (ret == -1)
		return (norm_main(tmp, exp, 0));
	ret = red_finder(exp, &tmp[1], &tmp[0]);
	if (ret == -1)
		return (norm_main(tmp, exp, 1));
	return (NULL);
}

t_list	*main_lst(char *cmd, t_list **envl)
{
	t_list	*tmp[2];
	char	**pipe;
	char	*exp;
	t_cmd	*cmd_list;
	t_list	*main_list;

	exp = NULL;
	tmp[0] = NULL;
	tmp[1] = NULL;
	main_list = NULL;
	pipe = NULL;
	exp = expand(cmd, envl);
	pipe = pipe_it(exp);
	if (check_pipes(pipe, exp) == 1 || check_reds(pipe) == 0)
		return (norm_main2(tmp, exp, pipe));
	cmd_list = cmd_lst(pipe, envl);
	if (pipe)
		free_chard(pipe);
	if (!cmd_list && red_finder(exp, &tmp[1], &tmp[0]) >= 1)
		return (norm_main(tmp, exp, 1));
	lst_append(&main_list, cmd_list);
	norm_main3(tmp, exp);
	return (main_list);
}
