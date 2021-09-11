/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:49:46 by abiari            #+#    #+#             */
/*   Updated: 2021/09/11 13:50:54 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_err(char *str)
{
	ft_putstr_fd("msh: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	print_env(t_list **envl)
{
	t_list	*tmp;

	tmp = *envl;
	while (tmp)
	{
		printf("declare -x %s\n", ((t_envl *)(tmp->content))->var);
		tmp = tmp->next;
	}
}

void	is_printable(int *prnt, char *haystack)
{
	if (ft_strchr(haystack, '=') != NULL)
		*prnt = 1;
	else
		*prnt = 0;
}

int	check_key(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (0);
	while (arg[i])
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]) && arg[0] != '_')
			return (0);
		i++;
	}
	return (1);
}
