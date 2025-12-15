#include "minishell.h"

// int	exec_pipeline(t_cmd *cmd, char ***envp);

// int	count_cmds(t_cmd *cmd);
// static int	run_single_builtin(t_cmd *cmd, char ***envp);

int	count_cmds(t_cmd *cmd)
{
	int	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

static int	run_single_builtin(t_cmd *cmd, char ***envp)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (!is_builtin_name(cmd->argv[0]))
		return (-1);
	return (exec_builtin(cmd, envp));
}

int	exec_pipeline(t_cmd *cmd, char ***envp)
{
	int	cmd_count;
	int	status;

	if (!cmd)
		return (0);
	cmd_count = count_cmds(cmd);
	if (cmd_count == 1)
	{
		status = run_single_builtin(cmd, envp);
		if (status >= 0)
		{
			g_exit_status = status;
			return (status);
		}
	}
	status = spawn_cmds(cmd, *envp);
	g_exit_status = status;
	return (status);
}
// ///////////////
// #include "minishell.h"

// // 1 more 25 line
// static int	count_cmds(t_cmd *cmd)
// {
// 	int	n;

// 	n = 0;
// 	while (cmd)
// 	{
// 		n++;
// 		cmd = cmd->next;
// 	}
// 	return (n);
// }

// static int	run_single_builtin(t_cmd *cmd, char ***envp)
// {
// 	if (!cmd || !cmd->argv || !cmd->argv[0])
// 		return (0);
// 	if (!is_builtin_name(cmd->argv[0]))
// 		return (-1);
// 	return (exec_builtin(cmd, envp)); //  این‌جا دیگه exec_builtin_parent نیست
// }

// static int	wait_for_children(pid_t *pids, int count)
// {
// 	int	i;
// 	int	status;
// 	int	last;

// 	i = 0;
// 	last = 0;
// 	while (i < count)
// 	{
// 		if (waitpid(pids[i], &status, 0) > 0)
// 		{
// 			if (WIFEXITED(status))
// 				last = WEXITSTATUS(status);
// 			else if (WIFSIGNALED(status))
// 				last = 128 + WTERMSIG(status);
// 		}
// 		i++;
// 	}
// 	free(pids);
// 	return (last);
// }

// // #include "minishell.h"

// static int	pipe_or_init(t_cmd *cur, int pipe_fd[2], pid_t *pids)
// {
// 	if (cur->next)
// 	{
// 		if (pipe(pipe_fd) < 0)
// 			return (free(pids), perror("pipe"), 1);
// 	}
// 	else
// 	{
// 		pipe_fd[0] = -1;
// 		pipe_fd[1] = -1;
// 	}
// 	return (0);
// }

// static int	fork_or_fail(pid_t *pids, int i)
// {
// 	pids[i] = fork();
// 	if (pids[i] < 0)
// 		return (free(pids), perror("fork"), 1);
// 	return (0);
// }

// static void	child_side(t_cmd *cur, int prev_fd, int pipe_fd[2], char **envp)
// {
// 	if (pipe_fd[1] != -1)
// 		close(pipe_fd[0]);
// 	exec_cmd_child(cur, prev_fd, pipe_fd[1], envp);
// }

// static int	parent_side(int prev_fd, int pipe_fd[2])
// {
// 	if (prev_fd != -1)
// 		close(prev_fd);
// 	if (pipe_fd[1] != -1)
// 		close(pipe_fd[1]);
// 	return (pipe_fd[0]);
// }

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

// static int	spawn_cmds(t_cmd *cmd, char **envp)
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

// int	exec_pipeline(t_cmd *cmd, char ***envp)
// {
// 	int	cmd_count;
// 	int	status;

// 	if (!cmd)
// 		return (0);
// 	cmd_count = count_cmds(cmd);
// 	if (cmd_count == 1)
// 	{
// 		status = run_single_builtin(cmd, envp);
// 		if (status >= 0)
// 		{
// 			g_exit_status = status;
// 			return (status);
// 		}
// 	}
// 	status = spawn_cmds(cmd, *envp);
// 	g_exit_status = status;
// 	return (status);
// }




// static int	spawn_cmds(t_cmd *cmd, char **envp)
// {
// 	int		prev_fd;
// 	int		pipe_fd[2];
// 	pid_t	*pids;
// 	t_cmd	*cur;
// 	int		i;

// 	pids = (pid_t *)malloc(sizeof(pid_t) * count_cmds(cmd));
// 	if (!pids)
// 		return (1);
// 	prev_fd = -1;
// 	cur = cmd;
// 	i = 0;
// 	while (cur)
// 	{
// 		if (pipe_or_init(cur, pipe_fd, pids) != 0)
// 			return (1);
// 		if (fork_or_fail(pids, i) != 0)
// 			return (1);
// 		if (pids[i] == 0)
// 			child_side(cur, prev_fd, pipe_fd, envp);
// 		prev_fd = parent_side(prev_fd, pipe_fd);
// 		cur = cur->next;
// 		i++;
// 	}
// 	if (prev_fd != -1)
// 		close(prev_fd);
// 	return (wait_for_children(pids, i));
// }

// 40 line
// static int	spawn_cmds(t_cmd *cmd, char **envp)
// {
// 	int		prev_fd;
// 	int		pipe_fd[2];
// 	pid_t	*pids;
// 	t_cmd	*cur;
// 	int		i;

// 	pids = (pid_t *)malloc(sizeof(pid_t) * count_cmds(cmd));
// 	if (!pids)
// 		return (1);
// 	prev_fd = -1;
// 	cur = cmd;
// 	i = 0;
// 	while (cur)
// 	{
// 		if (cur->next && pipe(pipe_fd) < 0)
// 			return (free(pids), perror("pipe"), 1);
// 		if (!cur->next)
// 		{
// 			pipe_fd[0] = -1;
// 			pipe_fd[1] = -1;
// 		}
// 		pids[i] = fork();
// 		if (pids[i] < 0)
// 			return (free(pids), perror("fork"), 1);
// 		if (pids[i] == 0)
// 		{
// 			if (pipe_fd[1] != -1)
// 				close(pipe_fd[0]);
// 			exec_cmd_child(cur, prev_fd, pipe_fd[1], envp);
// 		}
// 		if (prev_fd != -1)
// 			close(prev_fd);
// 		if (pipe_fd[1] != -1)
// 			close(pipe_fd[1]);
// 		prev_fd = pipe_fd[0];
// 		cur = cur->next;
// 		i++;
// 	}
// 	if (prev_fd != -1)
// 		close(prev_fd);
// 	return (wait_for_children(pids, i));
// }