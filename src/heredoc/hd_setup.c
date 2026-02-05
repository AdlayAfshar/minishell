
#include "heredoc.h"
#include "shell.h"
#include "signals.h"
#include "terminal.h"

static int	hd_process_redirs(t_redir *r, t_shell_ctx *ctx)
{
	int	res;

	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			res = process_heredoc(r, ctx);
			if (res != 0)
				return (res);
		}
		r = r->next;
	}
	return (0);
}

static int	hd_process_cmds(t_shell_ctx *ctx)
{
	t_cmd	*cur;
	int		res;

	cur = ctx->cmds;
	while (cur)
	{
		res = hd_process_redirs(cur->redirs, ctx);
		if (res != 0)
			return (res);
		cur = cur->next;
	}
	return (0);
}

static int	hd_finish(t_shell_ctx *ctx, int res)
{
	set_sig_interactive();
	ms_restore_termios(ctx);
	ms_set_termios(0);
	if (res == 2)
		return (2);
	if (res != 0)
		return (1);
	return (0);
}

// static int	hd_finish(int res)
// {
// 	set_sig_interactive();
// 	ms_set_termios(0);
// 	if (res == 2)
// 		return (2);
// 	if (res != 0)
// 		return (1);
// 	return (0);
// }

int	setup_heredocs(t_shell_ctx *ctx)
{
	int	res;

	g_sig = 0;
	set_sig_ignore();
	res = hd_process_cmds(ctx);
	return (hd_finish(ctx, res));
}
