#include "minishell.h"

static int	open_heredoc_file(t_redir *r)
{
	int	fd;

	fd = open(r->target, O_RDONLY);
	if (fd >= 0)
		unlink(r->target);
	return (fd);
}

static int	open_for_redir(t_redir *r)
{
	int	fd;

	fd = -1;
	if (r->type == R_IN)
		fd = open(r->target, O_RDONLY);
	else if (r->type == R_OUT)
		fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == R_APPEND)
		fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (r->type == R_HEREDOC)
		fd = open_heredoc_file(r);
	if (fd < 0)
		perror(r->target);
	return (fd);
}

static void	apply_single_redir(t_redir *r, int fd)
{
	if (r->type == R_IN || r->type == R_HEREDOC)
		dup2(fd, STDIN_FILENO);
	else if (r->type == R_OUT || r->type == R_APPEND)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

int	apply_redirs(t_redir *r)
{
	int	fd;

	while (r)
	{
		fd = open_for_redir(r);
		if (fd < 0)
			return (-1);
		apply_single_redir(r, fd);
		r = r->next;
	}
	return (0);
}