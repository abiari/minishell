#include "../../includes/minishell.h"

char	**parse_line(char *line)
{
	char	**tab;

	tab = split_cmds(line);
	if (tab)
		if (check_cmds(tab, line) == 1)
			return (NULL);
	return (tab);
}

int	check_pipes(char **pipe, char *cmd)
{
	int		i;
	int		*pipe_arr;
	t_list	*tmp;
	int		ret;

	tmp = NULL;
	ret = quotes_finder(cmd, &tmp);
	pipe_arr = pipes(cmd, &tmp);
	if (pipe_arr != NULL)
		return (check_pipes_helper(pipe, cmd, tmp, pipe_arr));
	i = 0;
	while (pipe[i])
	{
		printf("%s\n", pipe[i]);
		i++;
	}
	//ft_free(pipe, i);
	return (0);
}

int	main(void)
{
	int		i;
	char	**tab;
	char	**pipe;
	char	*cmd;
	char	**red;


	i = 0;
	tab = NULL;
	cmd = ft_strdup("echo |||||| hello; \\| tesst | allo ;\"test \" | allo ;allo ';' | allo ; \"|\"; echo allo | | cat -e");
	tab = split_cmds(cmd);
	if (tab)
		check_cmds(tab, cmd);
	while (tab[i])
	{
		pipe = pipe_it(tab[i]);
		if (pipe)
			check_pipes(pipe, tab[i]);
		i++;
	}
	i = 0;
	while (pipe[i])
	{
		red = reddit(pipe[i]);
		if(red)
			check_reds(red, red[i]);
		i++;
	}
	free(cmd);
	while(1);
}
