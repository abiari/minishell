#include "../../includes/minishell.h"

typedef struct s_quotes
{
	int				*type;
	int				*opens;
	int				*closes;
	struct s_quotes	*next;
}					t_quotes;


t_quotes	*ft_lstnew(int *type, int *opens, int *closes)
{
	t_quotes	*new;

	new = malloc(sizeof(t_quotes));
	new->type = type;
	new->opens = opens;
	new->closes = closes;
	new->next = NULL;
	return (new);
}

void	ft_lstaddback(t_quotes **lst, int *type, int *opens, int *closes)
{
	t_quotes	*new;
	t_quotes	*tmp;

	tmp = *lst;
	if (!lst)
	{
		*lst = ft_lstnew(type, opens, closes);
		return;
	}
	while(tmp->next != NULL)
		tmp = tmp->next;
	new = malloc(sizeof(t_quotes));
	new->type = type;
	new->opens = opens;
	new->closes = closes;
	new->next = NULL;
	tmp->next = new;
}

/*returns the index of the quote's closing; if it wasnt closed returns -1*/

int		quote_ends(int type, int i, char *str)
{
	char quote;

	if (type == 1)
		quote = '\'';
	if (type == 2)
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

int		quotes_finder(char *str)
{
	int 		i;
	t_quotes	*quotes;
	t_quotes	*tmp;
	int			counter;
	int			type;

	i = 0;
	while (str[i])
	{
		if (str[i] == "\\")
			i += 2;
		if (str[i] == "\'")
		{
			ft_lstaddback(&quotes , 1, i, quote_ends(1, i+1, str));
			type = 1;
			counter++;
		}
		if (str[i] == "\"")
		{
			ft_lstaddback(&quotes , 2, i, quote_ends(2, i+1, str));
			type = 2;
			counter++;
		}
		if (quote(type, i+1, str) != -1)
			i = quote(type, i+1, str) + 1;
		else
			i++;
	}
	return (counter);
}

/* TODO :int is_between_quotes(int i, char *str);*/
