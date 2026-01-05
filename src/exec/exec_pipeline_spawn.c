
#include "minishell.h"

static int	spawn_one(t_cmd *cur, t_spawn *s, t_execctx *x)
{
	int	pipe_fd[2];

	if (pipe_or_init(cur, pipe_fd, s->pids) != 0)
		return (1);
	if (fork_or_fail(s->pids, s->i) != 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	if (s->pids[s->i] == 0)
		child_side(cur, *(s->prev_fd), pipe_fd, x);
	*(s->prev_fd) = parent_side(*(s->prev_fd), pipe_fd);
	return (0);
}

int	cleanup_spawn_fail(pid_t *pids, int prev_fd)
{
	if (prev_fd != -1)
		close(prev_fd);
	free(pids);
	return (1);
}

int	spawn_all(t_cmd *cmd, t_spawn *s, t_execctx *x, int *count)
{
	t_cmd	*cur;
	int		i;

	cur = cmd;
	i = 0;
	while (cur)
	{
		s->i = i;
		if (spawn_one(cur, s, x) != 0)
			return (1);
		cur = cur->next;
		i++;
	}
	*count = i;
	return (0);
}
