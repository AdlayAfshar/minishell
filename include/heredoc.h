#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"

typedef struct s_hd
{
	int		fd;
	char	*delim;
	int		quoted;
	char	**envp;
	int		last_status;
}	t_hd;

char	*hd_make_name(void);
char	*hd_unquote_delim(const char *s);

int		hd_write_line(int fd, const char *s);

int		hd_read_loop(t_hd *h);

int     process_heredoc(t_redir *r, char **envp, int *last_status);
int		setup_heredocs(t_cmd *cmds, char **envp, int *last_status);

#endif