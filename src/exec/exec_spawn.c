
#include "exec.h"
#include "shell.h"

static int	init_spawn(t_cmd *cmd, int *prev_fd, t_shell_ctx *ctx)
{
	ctx->pids = (pid_t *)malloc(sizeof(pid_t) * count_cmds(cmd));
	if (!ctx->pids)
		return (1);
	*prev_fd = -1;
	return (0);
}

static int	finalize_spawn(t_shell_ctx *ctx, int prev_fd, int count)
{
	int	status;

	if (prev_fd != -1)
		close(prev_fd);
	status = wait_for_children(ctx->pids, count);
	free(ctx->pids);
	ctx->pids = NULL;
	return (status);
}

int	spawn_cmds(t_cmd *cmd, t_shell_ctx *ctx)
{
	int	prev_fd;
	int	count;

	if (!cmd)
		return (0);
	if (init_spawn(cmd, &prev_fd, ctx) != 0)
		return (1);
	if (spawn_all(ctx, &count) != 0)
		return (cleanup_spawn_fail(ctx, prev_fd));
	return (finalize_spawn(ctx, prev_fd, count));
}
