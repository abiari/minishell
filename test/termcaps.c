/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:44:46 by abiari            #+#    #+#             */
/*   Updated: 2021/03/30 15:14:53 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>
// #include <curses.h>
#define KEY_UP 183
#define KEY_DOWN 184
#define KEY_LEFT 186
#define KEY_RIGHT 185
#define ENTER 10
#define KEY_REMOVE 127
#define KEY_TAB 9
#define CTRL_D 4

int get_char()
{
	char c;
	int total;
	struct termios term, init;
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("Not a terminal\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	tcgetattr(STDIN_FILENO, &term);
	tcgetattr(STDIN_FILENO, &init);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	total = 0;
	while (read(STDIN_FILENO, &c, 1) <= 0)
		;
	total += c;
	while (read(STDIN_FILENO, &c, 1) > 0)
		total += c;
	tcsetattr(STDIN_FILENO, TCSANOW, &init);
	return (total);
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;
	int	c;

	while (1)
	{
		c = get_char();
		if (c == '\004')
			break ;
		else if (c >= 32 && c <= 126)
		{
			printf("%c = %d\n", c, c);
		}
		else
			printf("%d\n", c);
	}
	return 0;
}
