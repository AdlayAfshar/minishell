

#include "minishell.h"

static int	init_spawn(t_cmd *cmd, pid_t **pids, int *prev_fd)
{
	*pids = (pid_t *)malloc(sizeof(pid_t) * count_cmds(cmd));
	if (!*pids)
		return (1);
	*prev_fd = -1;
	return (0);
}

static int	spawn_one(t_cmd *cur, t_spawn *s)
{
	int	pipe_fd[2];

	if (pipe_or_init(cur, pipe_fd, s->pids) != 0)
		return (1);
	if (fork_or_fail(s->pids, s->i) != 0)
		return (1);
	if (s->pids[s->i] == 0)
		child_side(cur, *(s->prev_fd), pipe_fd, s->envp);
	*(s->prev_fd) = parent_side(*(s->prev_fd), pipe_fd);
	return (0);
}

int	spawn_cmds(t_cmd *cmd, char **envp)
{
	pid_t	*pids;
	t_cmd	*cur;
	int		prev_fd;
	int		i;
	t_spawn	s;

	if (init_spawn(cmd, &pids, &prev_fd) != 0)
		return (1);
	cur = cmd;
	i = 0;
	s.envp = envp;
	s.pids = pids;
	s.prev_fd = &prev_fd;
	while (cur)
	{
		s.i = i;
		if (spawn_one(cur, &s) != 0)
			return (1);
		cur = cur->next;
		i++;
	}
	if (prev_fd != -1)
		close(prev_fd);
	return (wait_for_children(pids, i));
}
///////

// #include "minishell.h"

// static int	init_spawn(t_cmd *cmd, pid_t **pids, int *prev_fd)
// {
// 	*pids = (pid_t *)malloc(sizeof(pid_t) * count_cmds(cmd));
// 	if (!*pids)
// 		return (1);
// 	*prev_fd = -1;
// 	return (0);
// }

// static int	spawn_one(t_cmd *cur, char **envp, pid_t *pids, int *prev_fd, int i)
// {
// 	int	pipe_fd[2];

// 	if (pipe_or_init(cur, pipe_fd, pids) != 0)
// 		return (1);
// 	if (fork_or_fail(pids, i) != 0)
// 		return (1);
// 	if (pids[i] == 0)
// 		child_side(cur, *prev_fd, pipe_fd, envp);
// 	*prev_fd = parent_side(*prev_fd, pipe_fd);
// 	return (0);
// }

// int	spawn_cmds(t_cmd *cmd, char **envp)
// {
// 	pid_t	*pids;
// 	t_cmd	*cur;
// 	int		prev_fd;
// 	int		i;

// 	if (init_spawn(cmd, &pids, &prev_fd) != 0)
// 		return (1);
// 	cur = cmd;
// 	i = 0;
// 	while (cur)
// 	{
// 		if (spawn_one(cur, envp, pids, &prev_fd, i) != 0)
// 			return (1);
// 		cur = cur->next;
// 		i++;
// 	}
// 	if (prev_fd != -1)
// 		close(prev_fd);
// 	return (wait_for_children(pids, i));
// }