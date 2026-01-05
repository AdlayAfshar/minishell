
#include "heredoc.h"
#include "signals.h"
#include "libft.h"
#include <errno.h>

extern int	rl_catch_signals;
extern int	rl_catch_sigwinch;

static void	hd_child_run(t_hd *h)
{
	int	res;

	set_sig_heredoc_child();
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	g_sig = 0;

	res = hd_read_loop(h);
	close(h->fd);
	if (res == 2)
		exit(130);
	if (res != 0)
		exit(1);
	exit(0);
}

static int	hd_apply_status(int status, int *last_status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		if (last_status)
			*last_status = 1;
		return (2);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		if (last_status)
			*last_status = 1;
		return (2);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (1);
	return (0);
}

static int	hd_fork_and_wait(t_hd *h, int *last_status)
{
	pid_t	pid;
	int		status;
	int		ret;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
		hd_child_run(h);
	close(h->fd);
	while (1)
	{
		ret = waitpid(pid, &status, 0);
		if (ret == -1)
		{
			if (errno == EINTR)
				continue ;
			perror("waitpid");
			return (1);
		}
		break ;
	}
	return (hd_apply_status(status, last_status));
}

int	process_heredoc(t_redir *r, char **envp, int *last_status)
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
	res = hd_fork_and_wait(&h, last_status);
	free(h.delim);
	h.delim = NULL;
	if (res != 0)
		return (unlink(fname), free(fname), res);
	return (hd_set_target(r, fname));
}