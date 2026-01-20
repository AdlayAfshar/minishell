
#include "exec.h"
#include "shell.h"

static int	init_spawn(t_cmd *cmd, pid_t **pids, int *prev_fd)
{
	*pids = (pid_t *)malloc(sizeof(pid_t) * count_cmds(cmd));
	if (!*pids)
		return (1);
	*prev_fd = -1;
	return (0);
}

static void	init_spawnctx(t_spawn *s, char **envp, pid_t *pids, int *prev_fd)
{
	s->envp = envp;
	s->pids = pids;
	s->prev_fd = prev_fd;
	s->i = 0;
}

static int	finalize_spawn(pid_t *pids, int prev_fd, int count)
{
	if (prev_fd != -1)
		close(prev_fd);
	return (wait_for_children(pids, count));
}

int	spawn_cmds(t_cmd *cmd, t_shell_ctx *ctx)
{
	pid_t	*pids;
	int		prev_fd;
	t_spawn	s;
	int		count;

	if (!cmd)
		return (0);
	if (init_spawn(cmd, &pids, &prev_fd) != 0)
		return (1);
	init_spawnctx(&s, ctx->envp, pids, &prev_fd);
	if (spawn_all(cmd, &s, ctx, &count) != 0)
		return (cleanup_spawn_fail(pids, prev_fd));
	return (finalize_spawn(pids, prev_fd, count));
}
