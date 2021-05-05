/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reddit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:37:52 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/05/05 11:48:57 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	red_type_check(char *str, int i)
{
	int count;

	count = 0;
	if (str[i] == '>')
	{
		while (str[i] == '>')
		{
			i++;
			count++;
		}
		if (count > 2)
			return (-1);
		if (count == 1)
			return (IN_R);
		if (count == 2)
			return (APP_R)
	}
	if (str[i] == '<')
	{
		while (str[i] == '<')
		{
			i++;
			count++;
		}
		if (count != 1)
			return (-1)
		else
			return (OUT_R);
	}
	return (-1)
}

int	validate_red(char *str, int i, t_list *tmp)
{
	int red;

	red = red_type_check(str, i);
	if (red != -1)
	{
		if ((red == IN_R || red == OUT_R) && && is_between_quotes(i, &tmp) == 0)
			return (1);
		else if (red == APP_R)
		{
			if (is_between_quotes(i, &tmp) == 0 && is_between_quotes(i + 1, &tmp) == 0)
				return (2)
		}
	}
	return (0);
}

int	red_counter(char *str, t_list *tmp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == '>' || str[i] == '<')
			if (validate_red(str, i, tmp) == 1)
				count++;
			else if (validate_red(str, i, tmp) == 2)
			{
				i++;
				count++;
			}
	}
	return (count);
}

int	*reds(char *str, t_list **lst)
{
	int		count;
	int		*reds;
	t_list	*tmp;

	tmp = *lst;
	count = red_counter(str, tmp);
	if (count == 0)
		return (NULL);
	reds = malloc((sizeof(int) * count) + sizeof(int));
	if (!reds)
		return (NULL);
	// char_array(reds, str, tmp, '>');
	return (reds);
}

char	**reddit(char *cmd)
{
	t_list	*tmp;
	int		*red;
	int		ret;
	char	**tab;

	tmp = NULL;
	red = NULL;
	ret = quotes_finder(cmd, &tmp);
	red = reds(cmd, &tmp);
	// tab = pipe_spliter(red, cmd);
	// ft_lstclear(&tmp, del_node);
	return (tab);
}

