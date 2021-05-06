/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reddit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:37:52 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/05/06 16:10:50 by ael-bagh         ###   ########.fr       */
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

char	**red_spliter(int *red, char *cmd)
{
	char	**tab;
	int		i;
	int		j;

	j = -1;
	i = 0;
	if (pipe != NULL)
	{
		i = red_counter(red, cmd);
		if (i == -1)
			return (NULL);
		tab = (char **)malloc((i + 1) * sizeof(char *));
		j = -1;
		while (++j < i)
			tab[j] = ft_strdup_dzeb(fill_command(cmd, j, red));
		tab[j] = NULL;
		free(red);
	}
	else
	{
		tab = (char **)malloc((2) * sizeof(char *));
		tab[0] = ft_strdup(cmd);
		tab[1] = NULL;
	}
	return (tab);
}

int		red_finder(char *str, t_list **redi, t_list **tmp)
{
	int			i;
	int			type;
	int			count;
	t_red		*red;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == '>' || str[i] == '<')
			if (validate_red(str, i, tmp) == 1 || validate_red(str, i, tmp) == 2)
			{
				red = malloc(sizeof(t_red));
				red->index = i;
				red->type = red_type_check(str, i);
				count++;
				lst_append(redi, red);
			}
	}
	return (count);
}

char	**reddit(char *cmd)
{
	t_list	*tmp;
	t_red	*r_srct;
	int		*red;
	int		ret;
	char	**tab;

	tmp = NULL;
	red = NULL;
	ret = quotes_finder(cmd, &tmp);
	ret = red_finder(cmd, &r_srct, &tmp);
	// red = reds(cmd, &tmp);
	// tab = red_spliter(red, cmd);
	ft_lstclear(&tmp, del_node);
	ft_lstclear(&r_srct, del_node_r);
	return (tab);
}

