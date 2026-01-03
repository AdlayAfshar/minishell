#include "minishell.h"

#include <errno.h>
#include <sys/wait.h>

//new
int	wait_for_children(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	last;
	int	ret;
	int printed;

	printed = 0;
	i = 0;
	last = 0;
	while (i < count)
	{
		ret = waitpid(pids[i], &status, 0);
		if (ret == -1)
		{
			if (errno == EINTR)
				continue ;
			perror("waitpid");
			break ;
		}
		if (WIFEXITED(status))
			last = WEXITSTATUS(status);
		// else if (WIFSIGNALED(status))
		// 	last = 128 + WTERMSIG(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
			{
				last = 130;
				if (!printed)
				{
					write(1, "\n", 1);
					printed = 1;
				}
			}
			else
				last = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(pids);
	return (last);
}

//old
// int	wait_for_children(pid_t *pids, int count)
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

int	pipe_or_init(t_cmd *cur, int pipe_fd[2], pid_t *pids)
{
	if (cur->next)
	{
		if (pipe(pipe_fd) < 0)
			return (free(pids), perror("pipe"), 1);
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
	return (0);
}

int	fork_or_fail(pid_t *pids, int i)
{
	pids[i] = fork();
	if (pids[i] < 0)
		return (free(pids), perror("fork"), 1);
	return (0);
}

void	child_side(t_cmd *cur, int prev_fd, int pipe_fd[2], t_execctx *x)
{
	if (pipe_fd[1] != -1)
		close(pipe_fd[0]);
	exec_cmd_child(cur, prev_fd, pipe_fd[1], x);
}

int	parent_side(int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	return (pipe_fd[0]);
}