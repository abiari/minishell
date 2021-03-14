/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:43:58 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/03/14 15:15:09 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		parse_error(char *err, int ret)
{
	write(1, err, ft_strlen(err));
	write(1, "\n", 1);
	return (ret);
}

int		quote_ends(int type, int i, char *str)
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

int		quotes_finder(char *str, t_list **lst)
{
	int 			i;
	int				counter;
	int				type;
	int				flag;
	t_quotes		*quotes;

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

int		is_between_quotes(int i , t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (i > ((t_quotes *)tmp->content)->opens && i < ((t_quotes *)tmp->content)->closes)
			return (((t_quotes *)tmp->content)->type);
		tmp = tmp->next;
	}
	return (0);
}

int		*commas(char *str, t_list **lst)
{
	int		i;
	int		count;
	int		*commas;
	t_list	*tmp;

	tmp = *lst;
	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == ';' && !is_between_quotes(i, &tmp))
			count++;
	if (count == 0)
		return (NULL);
	commas = malloc((sizeof(int) * count) + sizeof(int));
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == ';' && !is_between_quotes(i, &tmp))
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

	i = last_comma;
	while (cmd[i])
		i++;
	if (i == last_comma + 1)
		return (0);
	return (1);
}

char		*fill_command(char *cmd, int index, int *comma)
{
	int i;
	int j;
	int len;
	int last;
	char *tmp;

	last = 0;
	while(comma[last] != -2)
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

int		cmd_counter(int *comma, char *cmd)
{
	int i;

	i = 0;
	while(comma[i] != -2)
		i++;
	if (check_first_cmd(cmd, comma[0]) == -1)
		return (parse_error("bash: syntax error near unexpected token `;'", -1));
	if (check_last_cmd(cmd, comma[i - 1]))
		i++;
	return (i);
}

// static	void	ft_free(char **tab, int n)
// {
// 	int	i;

// 	i = 0;
// 	while (i > n)
// 		free(tab[i++]);
// 	free(tab);
// 	tab = NULL;
// }

int main()
{
	t_list		*lst;
	int			i = 0;
	int			j = 0;
	int			*comma;
	char		**tab;
	char		*tmp;
	int			ret;
	char		*cmd;
	int			cmds_num;

	cmd = ft_strdup("echo  allo \'hamid\';echo test | cat -e; mehmeh");
	cmds_num = 0;
	lst = NULL;
	ret = quotes_finder(cmd, &lst);  /* creates a list of quotes || TODO: PROTECT the absence of quotes ||*/
	if ((comma = commas(cmd, &lst)) != NULL)       /* creates an array of valid comas that aren't quoted */
	{
		if ((cmds_num = cmd_counter(comma, cmd)) == -1)
			return (1);

		tab = (char **)malloc((cmds_num + 1) * sizeof(char *));
		while (j < cmds_num)
		{
			tmp = fill_command(cmd ,j , comma);
			tab[j] = ft_strdup(tmp);
			free(tmp);
			j++;
		}
		tab[j] = NULL;
	}
	else
	{
		tab = (char **)malloc((2) * sizeof(char *));
		tab[0] = ft_strdup(cmd);
		tab[1] = NULL;
	}
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	free(cmd);
	// ft_free(tab, i);
	while (1);
}
