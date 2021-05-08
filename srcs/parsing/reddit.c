/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reddit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:37:52 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/05/08 13:45:00 by ael-bagh         ###   ########.fr       */
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
			return (APP_R);
	}
	if (str[i] == '<')
	{
		while (str[i] == '<')
		{
			i++;
			count++;
		}
		if (count != 1)
			return (-1);
		else
			return (OUT_R);
	}
	return (-1);
}

int	validate_red(char *str, int i, t_list *tmp)
{
	int red;

	red = red_type_check(str, i);
	if (red != -1)
	{
		if ((red == IN_R || red == OUT_R) && is_between_quotes(i, &tmp) == 0)
			return (1);
		else if (red == APP_R)
		{
			if (is_between_quotes(i, &tmp) == 0 && is_between_quotes(i + 1, &tmp) == 0)
				return (2);
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
		{
			if (validate_red(str, i, tmp) == 1)
				count++;
			else if (validate_red(str, i, tmp) == 2)
			{
				i++;
				count++;
			}
		}
	}
	return (count);
}

void	red_array(int *array, char *str, t_list *tmp)
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
		{
			if (validate_red(str, i, tmp) == 1 || validate_red(str, i, tmp) == 2)
			{
				array[count] = i;
				count++;
			}
		}
	}
	array[count] = -2;
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
	red_array(reds, str, tmp);
	return (reds);
}

int		red_finder(char *str, t_list **redi, t_list **tp)
{
	int			i;
	int			count;
	t_red		*red;
	t_list		*tmp;

	tmp = *tp;
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == '>' || str[i] == '<')
		{
			if (validate_red(str, i, tmp) == 1 || validate_red(str, i, tmp) == 2)
			{
				red = malloc(sizeof(t_red));
				red->index = i;
				red->type = red_type_check(str, i);
				count++;
				if (validate_red(str, i, tmp) == 2)
					i++;
				lst_append(redi, red);
			}
		}
	}
	return (count);
}


void print_list(t_list *list)
{
	if (list)
	{
		printf("FROM PRINT_LIST %d | %d\n", ((t_red*)list->content)->index, ((t_red*)list->content)->type);
		print_list(list->next);
	}
}

void	fill_red(int index, char *cmd, t_list *red) /*ach kadir a sa7bi zid t9ra mn lbssala*/
{
	//char	*str;
	int		prev;
	//int		i;
	t_list	*tmp;

	(void)cmd;
	tmp = red;
	prev = 0;
	while (((t_red*)tmp->content)->index != index && ((t_red*)tmp->next))
	{
		prev = ((t_red*)tmp->content)->index;
	}
	printf("%d\n", prev);
}

void	split_red(char *cmd, t_list *reds, t_list *quotes)
{
	int		red_count;
	char	**meh;
	t_list	*tmp;
	int		i;

	(void)cmd;
	i = 0;
	tmp = reds;
	red_count = red_counter(cmd, quotes);
	meh = (char**)malloc(sizeof(char*) * (red_count + 2));
	while (((t_red*)tmp->next))
	{
		//meh[i] = ft_strdup(fill_red(((t_red*)tmp->content)->index, cmd, reds));
		fill_red(((t_red*)tmp->content)->index, cmd, reds);
	}
}

void	reddit(char *cmd)
{
	t_list	*tmp;
	t_list	*tp;
	//char	*cmd;
	int		ret;
	// char	**red;

	tmp = NULL;
	tp = NULL;
	ret = quotes_finder(cmd, &tmp);
	ret = red_finder(cmd, &tp, &tmp);
	//print_list(tp);
	if (ret > 0)
		split_red(cmd, tp, tmp);
	ft_lstclear(&tmp, del_node);
	ft_lstclear(&tp, del_node_r);
}

