
#include "exec.h"
#include "shell.h"

static int	spawn_one(t_cmd *cur, t_shell_ctx *ctx, int i)
{
	int	pipe_fd[2];

	if (pipe_or_init(cur, pipe_fd, ctx->pids) != 0)
		return (1);
	if (fork_or_fail(ctx->pids, i) != 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	if (ctx->pids[i] == 0)
		child_side(cur, ctx->prev_fd, pipe_fd, ctx);
	ctx->prev_fd = parent_side(ctx->prev_fd, pipe_fd);
	return (0);
}

int	cleanup_spawn_fail(t_shell_ctx *ctx, int prev_fd)
{
	if (prev_fd != -1)
		close(prev_fd);
	free(ctx->pids);
	ctx->pids = NULL;
	return (1);
}

int	spawn_all(t_shell_ctx *ctx, int *count)
{
	t_cmd	*cur;
	int		proc_count;

	cur = ctx->cmds;
	proc_count = 0;
	while (cur)
	{
		if (spawn_one(cur, ctx, proc_count) != 0)
			return (1);
		cur = cur->next;
		proc_count++;
	}
	*count = proc_count;
	return (0);
}
