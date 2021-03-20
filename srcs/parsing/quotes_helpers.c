/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:43:58 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/03/20 11:39:20 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int parse_er(char *err, int ret)
{
	write(1, err, ft_strlen(err));
	write(1, "\n", 1);
	return (ret);
}

int quote_ends(int type, int i, char *str)
{
	char quote;

	if (type == S_QUOTE)
		quote = '\'';
	if (type == D_QUOTE)
		quote = '\"';
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int quotes_finder(char *str, t_list **lst)
{
	int i;
	int counter;
	int type;
	int flag;
	t_quotes *quotes;

	i = 0;
	counter = 0;
	while (str[i])
	{
		flag = 0;
		if (str[i] == '\\')
			i += 2;
		if (str[i] == '\'')
		{
			quotes = malloc(sizeof(t_quotes));
			quotes->type = S_QUOTE;
			quotes->opens = i;
			quotes->closes = quote_ends(S_QUOTE, i + 1, str);
			if (quotes->closes == -1)
				return (-1);
			lst_append(lst, quotes);
			type = S_QUOTE;
			counter++;
			flag = 1;
		}
		if (str[i] == '\"')
		{
			quotes = malloc(sizeof(t_quotes));
			quotes->type = D_QUOTE;
			quotes->opens = i;
			quotes->closes = quote_ends(D_QUOTE, i + 1, str);
			if (quotes->closes == -1)
				return (-1);
			lst_append(lst, quotes);
			type = D_QUOTE;
			counter++;
			flag = 1;
		}
		if (flag == 1)
			i = quote_ends(type, i + 1, str) + 1;
		else
			i++;
	}
	return (counter);
}

int is_between_quotes(int i, t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (i > ((t_quotes *)tmp->content)->opens &&
			i < ((t_quotes *)tmp->content)->closes)
			return (((t_quotes *)tmp->content)->type);
		tmp = tmp->next;
	}
	return (0);
}

int *commas(char *str, t_list **lst)
{
	int i;
	int count;
	int *commas;
	t_list *tmp;

	tmp = *lst;
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue;
		if (str[i] == ';' && is_between_quotes(i, &tmp) == 0)
			count++;
	}
	if (count == 0)
		return (NULL);
	commas = malloc((sizeof(int) * count) + sizeof(int));
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue;
		if (str[i] == ';' && is_between_quotes(i, &tmp) == 0)
		{
			commas[count] = i;
			count++;
		}
	}
	commas[count] = -2;
	return (commas);
}

int check_last_cmd(char *cmd, int last_comma)
{
	int i;
	int flag;

	i = last_comma;
	flag = 0;
	while (cmd[i])
		i++;
	if (i == last_comma + 1)
		return (0);
	return (1);
}

char *fill_command(char *cmd, int index, int *comma)
{
	int i;
	int j;
	int len;
	int last;
	char *tmp;

	last = 0;
	while (comma[last] != -2)
		last++;
	if (index == 0)
	{
		len = comma[index];
		i = 0;
	}
	else if (index == last && check_last_cmd(cmd, comma[last - 1]))
	{
		len = ft_strlen(cmd) - comma[index - 1] - 1;
		i = comma[index - 1] + 1;
	}
	else
	{
		len = comma[index] - comma[index - 1] - 1;
		i = comma[index - 1] + 1;
	}
	tmp = (char *)malloc((len + 1) * sizeof(char));
	j = 0;
	while (j < len)
	{
		tmp[j] = cmd[i];
		i++;
		j++;
	}
	tmp[len] = '\0';
	return (tmp);
}

int check_first_cmd(char *cmd, int first_comma)
{
	int i;
	int flag;

	flag = 0;
	i = 0;
	while (i < first_comma)
	{
		if (cmd[i] != ' ')
			flag = 1;
		i++;
	}
	if (i == 0 || flag == 0)
		return (-1);
	return (1);
}

int cmd_counter(int *comma, char *cmd)
{
	int i;

	i = 0;
	while (comma[i] != -2)
		i++;
	if (check_first_cmd(cmd, comma[0]) == -1)
		return (parse_er("bash: syntax error near unexpected token `;'", -1));
	if (check_last_cmd(cmd, comma[i - 1]))
		i++;
	return (i);
}

void ft_free(char **tab, int n)
{
	int i;

	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

char **cmds_spliter(int *comma, char *cmd, t_list **quotes)
{
	char **tab;
	t_list *tmp;
	int i;
	int j;

	j = -1;
	i = 0;
	tmp = *quotes;
	if (comma != NULL)
	{
		if ((i = cmd_counter(comma, cmd)) == -1)
			return (NULL);
		tab = (char **)malloc((i + 1) * sizeof(char *));
		j = -1;
		while (++j < i)
			tab[j] = ft_strdup_dzeb(fill_command(cmd, j, comma));
		tab[j] = NULL;
		free(comma);
	}
	else
	{
		tab = (char **)malloc((2) * sizeof(char *));
		tab[0] = ft_strdup(cmd);
		tab[1] = NULL;
	}
	return (tab);
}

char **split_cmds(char *cmd)
{
	t_list *tmp;
	int *comma;
	int ret;
	char **tab;

	tmp = NULL;
	comma = NULL;
	if ((ret = quotes_finder(cmd, &tmp)) == -1)
	{
		ft_putstr_fd("Multiple lines command\n", 1);
		return (NULL);
	}
	comma = commas(cmd, &tmp);
	tab = cmds_spliter(comma, cmd, &tmp);
	// if (comma)
	// free(comma);
	// if (tmp)
	// 	free(tmp);
	return (tab);
}
int only_char(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int check_cmds(char **cmds, char *cmd)
{
	int i;
	int *comma;
	t_list *tmp;
	int last;
	int ret;

	tmp = NULL;
	last = 0;
	comma = NULL;
	ret = quotes_finder(cmd, &tmp);
	if ((comma = commas(cmd, &tmp)) != NULL)
	{
		while (comma[last] != -2)
			last++;
		i = -1;
		while (cmds[++i])
		{
			if (i == cmd_counter(comma, cmd) - 1)
				if (only_char(' ', cmds[i]) && comma[last - 1] == (int)ft_strlen(cmd) - 1)
					return (parse_er("bash: syntax error near unexpected token `;'", 1));
			if (i != cmd_counter(comma, cmd) - 1 && only_char(' ', cmds[i]))
				return (parse_er("bash: syntax error near unexpected token `;'", 1));
		}
	}
	return (0);
}

// int main()
// {
// 	int i;
// 	char **tab;
// 	char *cmd;

// 	i = 0;
// 	tab = NULL;
// 	cmd = ft_strdup("echo alloewa  ; chkat3awd; anjerbou comma mabine quotes; ';;;;;;;;;'; hanta sidi khedamnine; njerbou comma we7da mabine double quotes; \";\" ;ewa chbghiti a sidi ; 3reftek chnou bghiti ; njerbou bzf d commas wesst double quotes w comma we7da wess single quotes, \";;;;;;;;;;\"; ';' ; ewa db mzn ;     ;");

// 	tab = split_cmds(cmd);
// 	if (tab)
// 		check_cmds(tab, cmd);
// 	ft_free(tab, i);
// }
