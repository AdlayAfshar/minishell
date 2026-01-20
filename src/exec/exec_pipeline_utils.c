
#include "exec.h"
#include "shell.h"
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

static int	handle_child_status(int status, int *printed)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			if (!*printed)
			{
				write(1, "\n", 1);
				*printed = 1;
			}
			return (130);
		}
		return (128 + WTERMSIG(status));
	}
	return (0);
}

static int	wait_one(pid_t pid, int *status)
{
	int	ret;

	ret = waitpid(pid, status, 0);
	if (ret == -1 && errno == EINTR)
		return (0);
	if (ret == -1)
	{
		perror("waitpid");
		return (-1);
	}
	return (1);
}

int	wait_for_children(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	last;
	int	printed;
	int	ret;

	i = 0;
	last = 0;
	printed = 0;
	while (i < count)
	{
		ret = wait_one(pids[i], &status);
		if (ret == -1)
			break ;
		if (ret == 1)
			last = handle_child_status(status, &printed);
		i++;
	}
	return (last);
}

void	child_side(t_cmd *cur, int prev_fd, int pipe_fd[2], t_shell_ctx *ctx)
{
	if (pipe_fd[1] != -1)
		close(pipe_fd[0]);
	exec_cmd_child(cur, prev_fd, pipe_fd[1], ctx);
}

int	parent_side(int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
		close(prev_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	return (pipe_fd[0]);
}
