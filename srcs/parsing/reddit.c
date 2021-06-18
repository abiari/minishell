/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reddit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:37:52 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/06/18 16:14:42 by ael-bagh         ###   ########.fr       */
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
		if (count > 2)
			return (-1);
		if (count == 1)
			return (OUT_R);
		if (count == 2)
			return (DOC_R);
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
		else if (red == APP_R || red == DOC_R)
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
			if (validate_red(str, i, tmp) == 1)
			{
				array[count] = i;
				count++;
			}
			if (validate_red(str, i, tmp) == 2)
			{
				array[count] = i;
				count++;
				i++;
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
				red->id = count;
				count++;
				if (validate_red(str, i, tmp) == 2)
					i++;
				lst_append(redi, red);
			}
		}
	}
	return (count);
}

int	red_type(t_list **red, int id)
{
	t_list *reds;

	reds = *red;
	while (reds)
	{
		if(((t_red*)reds->content)->id == id - 1)
			return (((t_red*)reds->content)->type);
		reds = reds->next;
	}
	return (0);
}

void print_list(t_list *list)
{
	if (list)
	{
		printf("FROM PRINT_LIST %d | %d | %d\n", ((t_red*)list->content)->id, ((t_red*)list->content)->index, ((t_red*)list->content)->type);
		print_list(list->next);
	}
}

// char	*fill_red(int id, int index, char *cmd, t_list *red, t_list *quotes)
// {
// 	//char	*str;
// 	int		start;
// 	int		end;
// 	int		i;
// 	t_list	*tmp;

// 	(void)cmd;
// 	tmp = red;
// 	start = index;
// 	while (((t_red*)tmp->content)->id <= red_counter(cmd, quotes))
// 	{

// 		tmp = tmp->next;
// 	}

// }

// void	split_red(char *cmd, t_list *reds, t_list *quotes)
// {
// 	int		red_count;
// 	char	**meh;
// 	t_list	*tmp;
// 	int		i;

// 	(void)cmd;
// 	i = 0;
// 	tmp = reds;
// 	red_count = red_counter(cmd, quotes);
// 	meh = (char**)malloc(sizeof(char*) * (red_count + 2));
// 	while (tmp->next)
// 	{
// 		meh[i] = ft_strdup(fill_red(((t_red*)tmp->content)->id, ((t_red*)tmp->content)->index, cmd, reds, quotes));
// 		tmp = tmp->next;
// 	}
// }

char	**red_spliter(int *red_arr, char *cmd, t_list *quotes)
{
	char	**tab;
	int		i;
	int		j;

	j = -1;
	i = 0;
	if (red_arr != NULL)
	{
		i = red_counter(cmd, quotes) + 1;
		if (i == -1)
			return (NULL);
		tab = (char **)malloc((i + 1) * sizeof(char *));
		j = -1;
		while (++j < i)
			tab[j] = ft_strdup(fill_red(cmd, j, red_arr));
		tab[j] = NULL;
		free(red_arr);
	}
	else
		return (NULL);
	return (tab);
}

int manage_red(char **red)
{
	int	i;

	i = -1;
	while (red[++i])
	{
		if (only_char(' ', red[i]))
		{
			printf("bash: syntax error near unexpected token `>'\n");
			return (0);
		}
	}
	return (1);
}

char	*my_strjoin(char *s1, char const *s2)
{
	int		size;
	char	*ret;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(size + 1);
	if (ret == NULL)
		return (ret);
	ft_strlcpy(ret, s1, size + 1);
	ft_strlcpy(ret + ft_strlen(s1), s2, size + 1);
	return (ret);
}

char		*to_join(char **spaces)
{
	int	i;
	char	*cmd;

	i = 0;
	cmd = ft_strdup("");
	while (spaces[++i])
	{
		cmd = my_strjoin(cmd, spaces[i]);
	}
	return (cmd);
}

char		**check_red(char **red, t_list *quotes, char *cmd, t_list **envl)
{
	char	**tab;
	char	**spaces;
	int		i;
	int j;

	j = -1;
	i = red_counter(cmd, quotes) + 1;
	if (!red)
		return NULL;
	tab = malloc((i + 1) * sizeof(char *));
	if (only_char(' ', red[0]) || red[0] == '\0')
		tab[0] = ft_strdup("");
	else
	{
		tab[0] = ft_strdup(red[0]);
		tab[0] = my_strjoin(tab[0]," ");
	}
	i = 0;
	while (red[++i])
	{
		if(i != 0)
		{
			spaces = space_it(red[i], envl, 0);
			j = -1;
			tab[i] = ft_strdup(spaces[0]);
			if (two_d_counter(spaces) > 0)
			{
				tab[0] = my_strjoin(tab[0], to_join(spaces));
				tab[0] = my_strjoin(tab[0]," ");
			}
		}
	}
	tab[i] = NULL;
	return (tab);
}

char	**reddit(char *cmd, t_list **envl)
{
	t_list	*tmp;
	t_list	*tp;
	int		*red_arr;
	int		ret;
	char	**red;
	char	**ugh;

	tmp = NULL;
	tp = NULL;
	ret = quotes_finder(cmd, &tmp);
	ret = red_finder(cmd, &tp, &tmp);
	red_arr = reds(cmd, &tmp);
	red = red_spliter(red_arr, cmd, tmp);
	ugh = check_red(red, tmp, cmd, envl);
	ft_lstclear(&tmp, del_node);
	ft_lstclear(&tp, del_node_r);
	return (ugh);
}

