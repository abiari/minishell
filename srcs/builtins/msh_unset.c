/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:45:23 by abiari            #+#    #+#             */
/*   Updated: 2021/06/07 18:12:17 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_alphanum(char *s)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!ft_isalpha(s[0]))
		return (0);
	while (s[i])
	{
		if (ft_isalpha(s[i]))
			flag = 1;
		if (!ft_isdigit(s[i]) && !ft_isalpha(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (flag);
}

int	msh_unset(char **args, t_list *envl)
{
	int		ret;
	int		i;
	// int		flag;

	ret = 0;
	// flag = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (!is_alphanum(args[i]))
		{
			ft_putstr_fd("msh: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		/*flag = */delete_env_var(args[i], &envl);
		/* if (flag == 1)*/
		i++;
	}
	return (ret);
}
