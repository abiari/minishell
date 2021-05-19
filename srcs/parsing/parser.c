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
	int		*pipe_arr;
	t_list	*tmp;
	int		ret;

	tmp = NULL;
	ret = quotes_finder(cmd, &tmp);
	pipe_arr = pipes(cmd, &tmp);
	if (pipe_arr != NULL)
		return (check_pipes_helper(pipe, cmd, tmp, pipe_arr));
	return (0);
}

void lst_append_red(t_redirect **list, t_redirect *param) {
	if ((*list))
		lst_append_red(&(*list)->next, param);
	else
		(*list) = param;
}

char	*

t_redirect	*red_lst(char	**pipelist, char **red, char *cmd, t_pipeline *pipe_lst)
{
	t_redirect	*red_list;
	t_list	**quotes;
	t_list	**reds;
	int		v;

	v = quotes_finder(cmd, quotes);
	v = red_finder(cmd, reds, quotes);
	v = -1;
	while (red[++v])
	{
		red_list = malloc(sizeof(t_redirect));
		red_list->cmd = cmd_final(**red);
		red_list->file = red[v];
		red_list->type = red_type(&red, v);
		lst_append_red(&pipe_lst->redirections, red_list);
	}
	return (red_list);
}

void lst_append_pipe(t_pipeline **list, t_pipeline *param) {
	if ((*list))
		lst_append_pipe(&(*list)->next, param);
	else
		(*list) = param;
}


t_pipeline	*pipe_lst(char **pipelist, char **red, char *cmd, t_cmd *cmd_list)
{
	t_pipeline	*pipe_list;
	int			v;

	v = -1;
	while (pipelist[++v])
	{
		pipe_list = malloc(sizeof(t_pipeline));
		pipe_list->redirections = red_lst(pipelist, red, cmd, pipe_list);
		pipe_list->cmd	= pipelist[v];
		lst_append_pipe(&cmd_list->pipes, pipe_list);
	}
	return (pipe_list);
}

t_cmd	*cmd_lst(char **pipelist, char **red, char *cmd)
{
	t_cmd *cmd_list;

	cmd_list = malloc(sizeof(t_cmd));
	cmd_list->pipes = NULL;
	cmd_list->pipes = pipe_lst(pipelist, red, cmd, cmd_list);
	return(cmd_list);
}

t_list	**main_lst(void)
{
	int		i;
	int		j;
	char	**tab;
	char	**pipe;
	char	*cmd;
	char	**red;
	t_cmd	*cmd_list;
	t_list	**main_list;


	i = 0;
	tab = NULL;
	cmd = ft_strdup("allO>finek>>meh>>salam < XXXXX; echo hello > file 1 world > file 2 \\>meh  >| cat file 1  ");
	tab = split_cmds(cmd);
	if (tab)
		check_cmds(tab, cmd);
	while (tab[i])
	{
		pipe = pipe_it(tab[i]);
		if (pipe)
		{
			check_pipes(pipe, tab[i]);
			j = -1;
			while (pipe[++j])
			{
				red = reddit(pipe[j]);
				cmd_list = cmd_lst(red, pipe, pipe[j]);
				lst_append(main_list, cmd_list);
			}
		}
		i++;
	}
	free(cmd);
	return (main_list);
}

int	main(void)
{
	t_list **parser;
	t_list	*cmd;
	int		i;


	parser = main_lst();
	cmd = &parser;
	while (((t_cmd*)cmd->content)->next)
	{
		while(((t_cmd*)cmd->content)->pipes)
		{
			while(((t_cmd*)cmd->content)->pipes->redirections)
			{
				printf("#command : %s\n", ((t_cmd*)cmd->content)->pipes->redirections->cmd);
			}
		}
	}
}
