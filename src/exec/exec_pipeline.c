#include "../../include/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

static int	open_outfile(t_redir *r)
{
	int	fd;

	if (r->type == R_OUT)
		fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror(r->target);
	return (fd);
}

static int	open_infile(t_redir *r)
{
	int	fd;

	fd = open(r->target, O_RDONLY);
	if (fd < 0)
		perror(r->target);
	return (fd);
}

static void	apply_redirs(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == R_IN)
		{
			fd = open_infile(r);
			if (fd >= 0)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
		}
		else if (r->type == R_OUT || r->type == R_APPEND)
		{
			fd = open_outfile(r);
			if (fd >= 0)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		r = r->next;
	}
}

static void	exec_cmd(t_cmd *cmd, char **envp)
{
    (void)envp;

	if (!cmd->argv || !cmd->argv[0])
		_exit(0);
	execvp(cmd->argv[0], cmd->argv);
	perror(cmd->argv[0]);
	_exit(127);
}

void	exec_pipeline(t_cmd *cmds, char **envp)
{
	int		prev_fd;
	int		pipe_fd[2];
	pid_t	pid;

	prev_fd = -1;
	while (cmds)
	{
		if (cmds->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			if (cmds->next)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			apply_redirs(cmds);
			exec_cmd(cmds, envp);
		}
		else if (pid < 0)
			perror("fork");
		if (prev_fd != -1)
			close(prev_fd);
		if (cmds->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		cmds = cmds->next;
	}
	while (wait(NULL) > 0)
		;
}