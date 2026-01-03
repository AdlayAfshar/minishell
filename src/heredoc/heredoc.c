//delete
#include "minishell.h"

typedef struct s_hd
{
	int		fd;
	char	*delim;
	int		quoted;
	char	**envp;
	int		last_status;
}	t_hd;

static char	*hd_make_name(void)
{
	static int	idx;
	char		*num;
	char		*name;

	idx++;
	num = ft_itoa(idx);
	if (!num)
		return (NULL);
	name = ft_strjoin(".heredoc_", num);
	free(num);
	if (!name)
		return (NULL);
	return (name);
}

static char	*hd_unquote_delim(const char *s)
{
	size_t	i;
	size_t	j;
	char	*out;

	if (!s)
		return (NULL);
	out = (char *)malloc(ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i++;
			continue ;
		}
		out[j++] = s[i++];
	}
	out[j] = '\0';
	return (out);
}

static int	hd_write_line(int fd, const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (write(fd, s, len) < 0)
		return (1);
	if (write(fd, "\n", 1) < 0)
		return (1);
	return (0);
}

// 33line
static int	hd_read_loop(t_hd *h)
{
	char	*line;
	char	*exp;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
        if (ft_strncmp(line, h->delim, ft_strlen(h->delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		exp = line;
		if (!h->quoted)
		{
			exp = expand_word(line, h->envp, h->last_status);
			free(line);
			if (!exp)
				return (1);
		}
		if (hd_write_line(h->fd, exp))
		{
			if (!h->quoted)
				free(exp);
			return (1);
		}
		if (!h->quoted)
			free(exp);
	}
	return (0);
}

static int	heredoc_child(t_hd *h)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (hd_read_loop(h))
	{
		close(h->fd);
		exit(1);
	}
	close(h->fd);
	exit(0);
}

// 52 line
static int	process_heredoc(t_redir *r, char **envp, int last_status)
{
	t_hd	h;
	char	*fname;
	pid_t	pid;
	int		status;

	h.delim = hd_unquote_delim(r->target);
	if (!h.delim)
		return (1);
	fname = hd_make_name();
	if (!fname)
		return (free(h.delim), 1);
	h.fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (h.fd < 0)
	{
		perror(fname);
		free(h.delim);
		free(fname);
		return (1);
	}
	h.quoted = r->heredoc_quoted;
	h.envp = envp;
	h.last_status = last_status;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(h.fd);
		free(h.delim);
		free(fname);
		return (1);
	}
    if (pid == 0)
    {
        set_sig_child_default();
        heredoc_child(&h); /* یا هر اسمی که گذاشتی */
    }
	close(h.fd);
	free(h.delim);
	if (waitpid(pid, &status, 0) < 0)
		return (free(fname), 1);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		// g_exit_status = 130;
		free(fname);
		return (2);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (free(fname), 1);
	free(r->target);
	r->target = fname;
	return (0);
}

// 30 line
int	setup_heredocs(t_cmd *cmds, char **envp, int last_status)
{
	t_cmd	*cur;
	t_redir	*r;
	int		res;

	set_sig_heredoc_parent();
	cur = cmds;
	while (cur)
	{
		r = cur->redirs;
		while (r)
		{
			if (r->type == R_HEREDOC)
			{
				res = process_heredoc(r, envp, last_status);
				if (res != 0)
				{
					set_sig_interactive();
					if (res == 2)
						return (2);
					return (1);
				}
			}
			r = r->next;
		}
		cur = cur->next;
	}
	set_sig_interactive();
	return (0);
}