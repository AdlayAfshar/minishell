
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

// int	spawn_cmds(t_cmd *cmd, char **envp, int last_status)
// {
// 	pid_t		*pids;
// 	t_cmd		*cur;
// 	int			prev_fd;
// 	int			i;
// 	t_spawn		s;
// 	t_execctx	x;

// 	if (!cmd)
// 		return (0);
// 	if (init_spawn(cmd, &pids, &prev_fd) != 0)
// 		return (1);
// 	x.envp = &envp;
// 	x.last_status = &last_status;
// 	cur = cmd;
// 	i = 0;
// 	s.envp = envp;
// 	s.pids = pids;
// 	s.prev_fd = &prev_fd;
// 	while (cur)
// 	{
// 		s.i = i;
// 		if (spawn_one(cur, &s, &x) != 0)
// 		{
// 			if (prev_fd != -1)
// 				close(prev_fd);
// 			free(pids);
// 			return (1);
// 		}
// 		cur = cur->next;
// 		i++;
// 	}
// 	if (prev_fd != -1)
// 		close(prev_fd);
// 	return (wait_for_children(pids, i));
// }
