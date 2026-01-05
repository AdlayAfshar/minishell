
#include "heredoc.h"
#include <errno.h>
#include <stdio.h>
#include <fcntl.h> 

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

int	hd_init(t_hd *h, t_redir *r, char **envp, int *last_status)
{
	h->delim = hd_unquote_delim(r->target);
	if (!h->delim)
		return (1);
	h->quoted = r->heredoc_quoted;
	h->envp = envp;
	h->last_status = (last_status ? *last_status : 0);
	return (0);
}

int	hd_make_and_open(t_hd *h, char **out_name)
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

void	hd_cleanup_parent(t_hd *h)
{
	if (h->fd >= 0)
		close(h->fd);
	if (h->delim)
		free(h->delim);
	h->fd = -1;
	h->delim = NULL;
}

int	hd_set_target(t_redir *r, char *fname)
{
	free(r->target);
	r->target = fname;
	return (0);
}