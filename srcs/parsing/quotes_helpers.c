#include "../../includes/minishell.h"

typedef struct s_quotes
{
	int				type;
	int				opens;
	int				closes;
}					t_quotes;

/*returns the index of the quote's closing; if it wasnt closed returns -1*/

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

/* returns the number of pair quotes (opened AND closed) found; adds each pair of quotes into the quotes list*/

int		quotes_finder(char *str, t_list **lst)
{
	int 			i;
	int				counter;
	int				type;
	t_quotes		*quotes;

	i = 0;
	counter = 0;
	while (str[i])
	{
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
		}
		if (quote_ends(type, i + 1, str) != -1)
			i = quote_ends(type, i + 1, str) + 1;
		else
			i++;
	}
	return (counter);
}

/* TODO :int is_between_quotes(int i, char *str);*/

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

int main()
{
	t_list		*lst;
	t_list		*tmp;
	int			i = -1;

	int ret;
	char cmd[100] = "ech\'o\'  allo; echo -n\"UGH\" meh";

	lst = NULL;
	ret = quotes_finder(cmd, &lst);
	if (ret == -1)
		printf("allo");
	tmp = lst;
	while (cmd[++i])
	{
		if ((ret = is_between_quotes(i, &lst)) == S_QUOTE)
			printf("single quote\n");
		else if ((ret = is_between_quotes(i, &lst)) == D_QUOTE)
			printf("double quote\n");
		else
			printf("no quotes\n");
	}
	// if (ret != 0)
	// {
	// 	while (tmp != NULL)
	// 	{
	// 		printf("quote starts at : %d | quote ends at : %d | quote type : %d\n", ((t_quotes *)tmp->content)->opens, ((t_quotes *)tmp->content)->closes, ((t_quotes *)tmp->content)->type);
	// 		tmp = tmp->next;
	// 	}
	// }
}
