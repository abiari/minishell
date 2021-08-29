/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 15:08:56 by abiari            #+#    #+#             */
/*   Updated: 2021/07/08 18:03:29 by abiari           ###   ########.fr       */
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
			g_vars.exit_code = 131; // WIFSIGNALED && WTERMSIG
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
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sign_num == SIGQUIT)
	{
		ft_putchar_fd('\r', 1);
		rl_on_new_line();
		rl_redisplay();
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
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (sign_num == SIGQUIT)
		{
			ft_putchar_fd('\r', 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
