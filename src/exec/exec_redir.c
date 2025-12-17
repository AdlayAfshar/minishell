#include "minishell.h"
// #include <string.h>   // strerror
// #include <errno.h>
// #include <unistd.h>

// static void dbg_target(const char *t)
// {
// 	size_t i = 0;
// 	char   buf[64];

// 	write(2, "redir target bytes: ", 20);
// 	while (t && t[i])
// 	{
// 		int n = snprintf(buf, sizeof(buf), "%02X ", (unsigned char)t[i]);
// 		write(2, buf, n);
// 		i++;
// 	}
// 	write(2, "\n", 1);
// }

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

// static int	open_for_redir(t_redir *r)
// {
// 	int		fd;
// 	char	cwd[1024];

// 	fd = -1;

// 	if (getcwd(cwd, sizeof(cwd)))
// 	{
// 		write(2, "cwd: ", 5);
// 		write(2, cwd, ft_strlen(cwd));
// 		write(2, "\n", 1);
// 	}

// 	write(2, "target: ", 8);
// 	if (r && r->target)
// 		write(2, r->target, ft_strlen(r->target));
// 	write(2, "\n", 1);
// 	dbg_target(r->target);

// 	if (r->type == R_IN)
// 		fd = open(r->target, O_RDONLY);
// 	else if (r->type == R_OUT)
// 		fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else if (r->type == R_APPEND)
// 		fd = open(r->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else if (r->type == R_HEREDOC)
// 		fd = open_heredoc_file(r);

// 	if (fd < 0)
// 	{
// 		char msg[128];
// 		int n = snprintf(msg, sizeof(msg),
// 			"open errno=%d (%s)\n", errno, strerror(errno));
// 		write(2, msg, n);
// 		perror(r->target);
// 	}
// 	return (fd);
// }

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