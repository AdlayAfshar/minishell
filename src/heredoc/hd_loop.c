#include "heredoc.h"

static int	hd_is_delim(const char *line, const char *delim)
{
	size_t	dlen;

	if (!line || !delim)
		return (0);
	dlen = ft_strlen(delim);
	return (ft_strncmp(line, delim, dlen + 1) == 0);
}

static char	*hd_expand_if_needed(t_hd *h, char *line, int *need_free)
{
	char	*exp;

	*need_free = 0;
	if (h->quoted)
		return (line);
	exp = expand_word(line, h->envp, h->last_status);
	*need_free = 1;
	return (exp);
}

static int	hd_handle_line(t_hd *h, char *line)
{
	char	*exp;
	int		need_free;

	exp = hd_expand_if_needed(h, line, &need_free);
	if (!exp)
		return (1);
	if (hd_write_line(h->fd, exp))
	{
		if (need_free)
			free(exp);
		return (1);
	}
	if (need_free)
		free(exp);
	return (0);
}

int	hd_read_loop(t_hd *h)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (hd_is_delim(line, h->delim))
		{
			free(line);
			break ;
		}
		if (hd_handle_line(h, line))
			return (free(line), 1);
		free(line);
	}
	return (0);
}