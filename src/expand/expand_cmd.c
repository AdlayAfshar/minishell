
#include "expand.h"
#include "shell.h"

static int	expand_argv(char ***pargv, t_shell_ctx *ctx)
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
		new = expand_word(argv[i], ctx);
		if (!new)
			return (1);
		free(argv[i]);
		argv[i] = new;
		i++;
	}
	return (0);
}

static int	expand_redirs(t_redir *r, t_shell_ctx *ctx)
{
	char	*new;

	while (r)
	{
		if (r->type == R_HEREDOC)
		{
			r = r->next;
			continue ;
		}
		new = expand_word(r->target, ctx);
		if (!new)
			return (1);
		free(r->target);
		r->target = new;
		r = r->next;
	}
	return (0);
}

static int	expand_cmd_list(t_shell_ctx *ctx)
{
	t_cmd	*cur;

	cur = ctx->cmds;
	while (cur)
	{
		if (expand_argv(&cur->argv, ctx))
			return (1);
		if (expand_redirs(cur->redirs, ctx))
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	expand_all(t_shell_ctx *ctx)
{
	if (!ctx->cmds)
		return (0);
	if (expand_cmd_list(ctx))
		return (1);
	return (0);
}