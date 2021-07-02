/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:45:23 by abiari            #+#    #+#             */
/*   Updated: 2021/07/01 17:48:49 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_alphanum(char *s)
{
	int		i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && !ft_isalpha(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	msh_unset(char **args, t_list *envl)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (!is_alphanum(args[i]))
		{
			ft_putstr_fd("msh: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		delete_env_var(args[i], &envl);
		i++;
	}
	return (ret);
}
