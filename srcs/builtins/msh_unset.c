/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:45:23 by abiari            #+#    #+#             */
/*   Updated: 2021/03/10 15:51:07 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		msh_unset(char *args[], t_list *envl)
{
	int		ret;
	int		flag;
	int		i;

	ret = 0;
	flag = 0;
	i = 0;
	while (args[i] != NULL)
	{
		flag = delete_env_var(args[i], envl);
		if (flag = 1)
			ret = 1;
		i++;
	}
	return (ret);
}
