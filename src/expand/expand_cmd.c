#include "minishell.h"

static int	expand_argv(char ***pargv, char **envp, int last_status)
{
	char	**argv;
	int		i;
	char	*new;

	argv = *pargv;
	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
	{
		new = expand_word(argv[i], envp, last_status);
		if (!new)
			return (1);
		free(argv[i]);
		argv[i] = new;
		i++;
	}
	return (0);
}

static int	expand_redirs(t_redir *r, char **envp, int last_status)
{
	char	*new;

	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			r = r->next;
			continue ;
		}
		new = expand_word(r->target, envp, last_status);
		if (!new)
			return (1);
		free(r->target);
		r->target = new;
		r = r->next;
	}
	return (0);
}

static int	expand_cmd_list(t_cmd *cmds, char **envp, int last_status)
{
	t_cmd	*cur;

	cur = cmds;
	while (cur)
	{
		if (expand_argv(&cur->argv, envp, last_status))
			return (1);
		if (expand_redirs(cur->redirs, envp, last_status))
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	expand_all(t_cmd *cmds, char **envp, int last_status)
{
	if (!cmds)
		return (0);
	if (expand_cmd_list(cmds, envp, last_status))
		return (1);
	return (0);
}