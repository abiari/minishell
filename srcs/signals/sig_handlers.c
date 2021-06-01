/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 15:08:56 by abiari            #+#    #+#             */
/*   Updated: 2021/05/31 10:26:12 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process(int sign_num)
{
	if (!kill(g_vars.pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_vars.exit_code = 131;
		}
		else if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_vars.exit_code = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_vars.exit_code = 1;
		msh_prompt();
	}
}

void	sig_handler(int sign_num)
{
	if ((sign_num == SIGINT || sign_num == SIGQUIT) && g_vars.pid != 0)
		process(sign_num);
	else
	{
		if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_vars.exit_code = 1;
			msh_prompt();
		}
		else if (sign_num == SIGQUIT)
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}
