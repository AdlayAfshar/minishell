#include "heredoc.h"

static int	hd_open_outfile(const char *fname, int *fd)
{
	*fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (*fd < 0)
	{
		perror(fname);
		return (1);
	}
	return (0);
}

static void	hd_child_run(t_hd *h)
{
	set_sig_child_default();
	if (hd_read_loop(h))
	{
		close(h->fd);
		exit(1);
	}
	close(h->fd);
	exit(0);
}

static int	hd_wait_result(pid_t pid, int *out_status)
{
	if (waitpid(pid, out_status, 0) < 0)
	{
		perror("waitpid");
		return (1);
	}
	return (0);
}

// static int	hd_apply_status(int status, char *fname)
// {
// 	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
// 	{
// 		g_exit_status = 130;
// 		free(fname);
// 		return (2);
// 	}
// 	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
// 	{
// 		free(fname);
// 		return (1);
// 	}
// 	return (0);
// }

static int	hd_apply_status(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_exit_status = 130;
		return (2);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (1);
	return (0);
}

// #include "heredoc.h"

static int	hd_init(t_hd *h, t_redir *r, char **envp, int last_status)
{
	h->delim = hd_unquote_delim(r->target);
	if (!h->delim)
		return (1);
	h->quoted = r->heredoc_quoted;
	h->envp = envp;
	h->last_status = last_status;
	return (0);
}

static int	hd_make_and_open(t_hd *h, char **out_name)
{
	*out_name = hd_make_name();
	if (!*out_name)
		return (1);
	if (hd_open_outfile(*out_name, &h->fd))
	{
		free(*out_name);
		*out_name = NULL;
		return (1);
	}
	return (0);
}

// static int	hd_fork_and_wait(t_hd *h, char *fname)
// {
// 	pid_t	pid;
// 	int		status;
// 	int		res;

// 	pid = fork();
// 	if (pid < 0)
// 		return (perror("fork"), 1);
// 	if (pid == 0)
// 		hd_child_run(h);
// 	close(h->fd);
// 	if (hd_wait_result(pid, &status))
// 		return (1);
// 	res = hd_apply_status(status, fname);
// 	return (res);
// }

static int	hd_fork_and_wait(t_hd *h)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		hd_child_run(h);
	close(h->fd);
	if (hd_wait_result(pid, &status))
		return (1);
	return (hd_apply_status(status));
}

static void	hd_cleanup_parent(t_hd *h)
{
	if (h->fd >= 0)
		close(h->fd);
	if (h->delim)
		free(h->delim);
	h->fd = -1;
	h->delim = NULL;
}

static int	hd_set_target(t_redir *r, char *fname)
{
	free(r->target);
	r->target = fname;
	return (0);
}

int	process_heredoc(t_redir *r, char **envp, int last_status)
{
	t_hd	h;
	char	*fname;
	int		res;

	h.fd = -1;
	h.delim = NULL;
	if (hd_init(&h, r, envp, last_status))
		return (1);
	if (hd_make_and_open(&h, &fname))
		return (hd_cleanup_parent(&h), 1);
	// res = hd_fork_and_wait(&h, fname);
	// free(h.delim);
	// if (res != 0)
	// 	return (free(fname), res);
	// return (hd_set_target(r, fname));
	res = hd_fork_and_wait(&h);
	free(h.delim);
	h.delim = NULL;
	if (res != 0)
		return (unlink(fname), free(fname), res);
	return (hd_set_target(r, fname));
}


// int	process_heredoc(t_redir *r, char **envp, int last_status)
// {
// 	t_hd	h;
// 	char	*fname;
// 	pid_t	pid;
// 	int		status;
// 	int		res;

// 	h.delim = hd_unquote_delim(r->target);
// 	if (!h.delim)
// 		return (1);
// 	fname = hd_make_name();
// 	if (!fname)
// 		return (free(h.delim), 1);
// 	if (hd_open_outfile(fname, &h.fd))
// 		return (free(h.delim), free(fname), 1);
// 	h.quoted = r->heredoc_quoted;
// 	h.envp = envp;
// 	h.last_status = last_status;
// 	pid = fork();
// 	if (pid < 0)
// 		return (perror("fork"), close(h.fd), free(h.delim), free(fname), 1);
// 	if (pid == 0)
// 		hd_child_run(&h);
// 	close(h.fd);
// 	free(h.delim);
// 	if (hd_wait_result(pid, &status))
// 		return (free(fname), 1);
// 	res = hd_apply_status(status, fname);
// 	if (res != 0)
// 		return (res);
// 	free(r->target);
// 	r->target = fname;
// 	return (0);
// }