
#include "minishell.h"

static t_cmd	*lex_parse_line(char *line)
{
	t_token	*ts;
	t_cmd	*cmds;

	ts = lex_line(line);
	if (!ts)
		return (NULL);
	cmds = parse_tokens(ts);
	token_list_clear(&ts);
	return (cmds);
}

static int	expand_cmds(t_cmd *cmds, char **envp, int exit_status)
{
	if (expand_all(cmds, envp, exit_status))
	{
		free_cmds(cmds);
		return (1);
	}
	return (0);
}

static int	run_heredocs(t_cmd *cmds, char **envp, int *exit_status)
{
	int	hd;

	hd = setup_heredocs(cmds, envp, exit_status);
	if (hd != 0)
	{
		free_cmds(cmds);
		return (1);
	}
	return (0);
}

static void	exec_cmds(t_cmd *cmds, char ***envp, int *exit_status)
{
	t_execctx	x;

	x.envp = envp;
	x.last_status = exit_status;
	*exit_status = exec_pipeline(cmds, &x);
	free_cmds(cmds);
}

int	process_line(char *line, char ***envp, int *exit_status)
{
	t_cmd	*cmds;

	cmds = lex_parse_line(line);
	if (!cmds)
		return (0);
	if (expand_cmds(cmds, *envp, *exit_status))
		return (0);
	if (run_heredocs(cmds, *envp, exit_status))
		return (0);
	exec_cmds(cmds, envp, exit_status);
	return (0);
}
