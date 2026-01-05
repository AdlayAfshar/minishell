
#include "heredoc.h"

static int	hd_process_redirs(t_redir *r, char **envp, int *last_status)
{
	int	res;

	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			res = process_heredoc(r, envp, last_status);
			if (res != 0)
				return (res);
		}
		r = r->next;
	}
	return (0);
}

static int	hd_process_cmds(t_cmd *cmds, char **envp, int *last_status)
{
	t_cmd	*cur;
	int		res;

	cur = cmds;
	while (cur)
	{
		res = hd_process_redirs(cur->redirs, envp, last_status);
		if (res != 0)
			return (res);
		cur = cur->next;
	}
	return (0);
}

static int	hd_finish(int res)
{
	set_sig_interactive();
	if (res == 2)
		return (2);
	if (res != 0)
		return (1);
	return (0);
}

int	setup_heredocs(t_cmd *cmds, char **envp, int *last_status)
{
	int	res;

	g_sig = 0;
	set_sig_heredoc_parent();
	res = hd_process_cmds(cmds, envp, last_status);
	return (hd_finish(res));
}
