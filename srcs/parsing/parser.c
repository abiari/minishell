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

int	main(void)
{
	int		i;
	char	**tab;
	char	*cmd;

	i = 0;
	tab = NULL;
	cmd = ft_strdup("hello; allo; ';;;'; makayn walou\\;");
	tab = split_cmds(cmd);
	if (tab)
		check_cmds(tab, cmd);
	free(cmd);
}
