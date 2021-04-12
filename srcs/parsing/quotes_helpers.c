/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 09:43:58 by ael-bagh          #+#    #+#             */
/*   Updated: 2021/04/12 16:51:06 by ael-bagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_er(char *err, int ret)
{
	write(1, err, ft_strlen(err));
	write(1, "\n", 1);
	return (ret);
}

void	del_node(void *content)
{
	((t_quotes *)content)->type = 0;
	((t_quotes *)content)->closes = 0;
	((t_quotes *)content)->opens = 0;
	free(content);
}

int	quote_ends(int type, int i, char *str)
{
	char	quote;

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

int	s_quote(t_quotes *quotes, t_list **lst, int i, char *str)
{
	quotes = malloc(sizeof(t_quotes));
	quotes->type = S_QUOTE;
	quotes->opens = i;
	quotes->closes = quote_ends(S_QUOTE, i + 1, str);
	if (quotes->closes == -1)
	{
		ft_lstclear(lst, del_node);
		return (-1);
	}
	lst_append(lst, quotes);
	return (0);
}

int	d_quote(t_quotes *quotes, t_list **lst, int i, char *str)
{
	quotes = malloc(sizeof(t_quotes));
	quotes->type = D_QUOTE;
	quotes->opens = i;
	quotes->closes = quote_ends(D_QUOTE, i + 1, str);
	if (quotes->closes == -1)
	{
		ft_lstclear(lst, del_node);
		return (-1);
	}
	lst_append(lst, quotes);
	return (0);
}

void q_helper(int *type, int *flag, int i)
{
	if (i == 1)
	{
		*type = S_QUOTE;
		*flag = 1;
	}
	if (i == 2)
	{
		*type = D_QUOTE;
		*flag = 1;
	}
}

void	q_helper_second(t_quotes *quotes, t_list **lst, int i, char *str)
{

}

int	quotes_finder(char *str, t_list **lst)
{
	int			i;
	int			counter;
	int			*type;
	int			*flag;
	t_quotes	*quotes;

	i = 0;
	quotes = NULL;
	counter = 0;
	while (str[i])
	{
		flag = 0;
		if (str[i] == '\\')
			i += 2;
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (s_quote(quotes, lst, i, str) == -1)
				return (-1);
			q_helper(&type, &flag, 1 + (str[i] == '\"'));
			counter++;
		}
		// if (str[i] == '\'')
		// {
		// 	if (s_quote(quotes, lst, i, str) == -1)
		// 		return (-1);
		// 	q_helper(&type, &flag, 1);
		// 	counter++;
		// }
		// if (str[i] == '\"')
		// {
		// 	if (d_quote(quotes, lst, i, str) == -1)
		// 		return (-1);
		// 	q_helper(&type, &flag, 2);
		// 	counter++;
		// }
		if (flag == 1)
			i = quote_ends(type, i + 1, str) + 1;
		else
			i++;
	}
	return (counter);
}

int	is_between_quotes(int i, t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (i > ((t_quotes *)tmp->content)->opens
			&& i < ((t_quotes *)tmp->content)->closes)
			return (((t_quotes *)tmp->content)->type);
		tmp = tmp->next;
	}
	return (0);
}

int	commas_counter(char *str, t_list *tmp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == ';' && is_between_quotes(i, &tmp) == 0)
			count++;
	}
	return (count);
}

void	commas_array(int *commas, char *str, t_list *tmp)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && (i++))
			continue ;
		if (str[i] == ';' && is_between_quotes(i, &tmp) == 0)
		{
			commas[count] = i;
			count++;
		}
	}
	commas[count] = -2;
}

int	*commas(char *str, t_list **lst)
{
	int		count;
	int		*commas;
	t_list	*tmp;

	tmp = *lst;
	count = commas_counter(str, tmp);
	if (count == 0)
		return (NULL);
	commas = malloc((sizeof(int) * count) + sizeof(int));
	if (!commas)
		return (NULL);
	commas_array(commas, str, tmp);
	return (commas);
}

int	check_last_cmd(char *cmd, int last_comma)
{
	int	i;
	int	flag;

	i = last_comma;
	flag = 0;
	while (cmd[i])
		i++;
	if (i == last_comma + 1)
		return (0);
	return (1);
}

int	last_comma(int *commas)
{
	int	last;

	last = 0;
	while (commas[last] != -2)
		last++;
	return (last);
}

int	len_init(int index, int *comma, int last, char *cmd)
{
	if (index == 0)
		return (comma[index]);
	else if (index == last && check_last_cmd(cmd, comma[last - 1]))
		return (ft_strlen(cmd) - comma[index - 1] - 1);
	else
		return (comma[index] - comma[index - 1] - 1);
}

int	i_init(int index, int *comma, int last, char *cmd)
{
	if (index == 0)
		return (0);
	else if (index == last && check_last_cmd(cmd, comma[last - 1]))
		return (comma[index - 1] + 1);
	else
		return (comma[index - 1] + 1);
}

char	*fill_command(char *cmd, int index, int *comma)
{
	int		i;
	int		j;
	int		len;
	int		last;
	char	*tmp;

	last = last_comma(comma);
	len = len_init(index, comma, last, cmd);
	i = i_init(index, comma, last, cmd);
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

int	check_first_cmd(char *cmd, int first_comma)
{
	int	i;
	int	flag;

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

int	cmd_counter(int *comma, char *cmd)
{
	int	i;

	i = 0;
	while (comma[i] != -2)
		i++;
	if (check_first_cmd(cmd, comma[0]) == -1)
		return (parse_er("bash: syntax error near unexpected token `;'", -1));
	if (check_last_cmd(cmd, comma[i - 1]))
		i++;
	return (i);
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

char	**cmds_spliter(int *comma, char *cmd)
{
	char	**tab;
	int		i;
	int		j;

	j = -1;
	i = 0;
	if (comma != NULL)
	{
		i = cmd_counter(comma, cmd);
		if (i == -1)
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
		tab[0] = ft_strdup_dzeb(cmd);
		tab[1] = NULL;
	}
	return (tab);
}

char	**split_cmds(char *cmd)
{
	t_list	*tmp;
	int		*comma;
	int		ret;
	char	**tab;

	tmp = NULL;
	comma = NULL;
	ret = quotes_finder(cmd, &tmp);
	if (ret == -1)
	{
		ft_putstr_fd("Multiple lines command\n", 1);
		return (NULL);
	}
	comma = commas(cmd, &tmp);
	tab = cmds_spliter(comma, cmd);
	ft_lstclear(&tmp, del_node);
	return (tab);
}

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

int	free_the_nipples(t_list *tmp, char **cmds, int i)
{
	ft_lstclear(&tmp, del_node);
	ft_free(cmds, i + 1);
	return (parse_er("bash: syntax error near unexpected token `;'", 1));
}

int	check_cmds_helper(char **cmds, char *cmd, t_list *tmp, int *comma)
{
	int	last;
	int	i;

	i = -1;
	last = last_comma(comma);
	while (cmds[++i])
	{
		if (i == cmd_counter(comma, cmd) - 1)
			if (only_char(' ', cmds[i])
				&& (comma[last - 1] == (int)ft_strlen(cmd) - 1))
				free_the_nipples(tmp, cmds, i);
		if (i != cmd_counter(comma, cmd) - 1 && only_char(' ', cmds[i]))
			free_the_nipples(tmp, cmds, i);
	}
	if (comma)
		free(comma);
	i = 0;
	while (cmds[i])
	{
		printf("%s\n", cmds[i]);
		i++;
	}
	ft_free(cmds, i);
	ft_lstclear(&tmp, del_node);
	return (0);
}

int	check_cmds(char **cmds, char *cmd)
{
	int		i;
	int		*comma;
	t_list	*tmp;
	int		ret;

	tmp = NULL;
	ret = quotes_finder(cmd, &tmp);
	comma = commas(cmd, &tmp);
	if (comma != NULL)
		return (check_cmds_helper(cmds, cmd, tmp, comma));
	i = 0;
	while (cmds[i])
	{
		printf("%s\n", cmds[i]);
		i++;
	}
	ft_free(cmds, i);
	return (0);
}

int main()
{
	int i;
	char **tab;
	char *cmd;

	i = 0;
	tab = NULL;
	cmd = ft_strdup("allo; meh come\'    ;  \' on dude; meh    ; allo ; allo ';' allo");
	tab = split_cmds(cmd);
	if (tab)
		check_cmds(tab, cmd);
	free(cmd);
	while (1);
}
