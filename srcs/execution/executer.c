/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 14:08:40 by abiari            #+#    #+#             */
/*   Updated: 2021/05/08 14:01:51 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute(char **cmd, char **envp)
{
	t_list	*envl;

	envl = envp_to_envl(envp);
	cmd[0] = bin_path(cmd[0], envl);
	if (cmd[0] == NULL)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" :command not found", 2);
		exit(127);
	}
}
