#ifndef HEREDOC_H
# define HEREDOC_H

# include "parser.h"

typedef struct s_hd
{
	int		fd;
	char	*delim;
	int		quoted;
	char	**envp;
	int		last_status;
}			t_hd;

// extern int	rl_catch_signals;
// extern int	rl_catch_sigwinch;

char		*hd_make_name(void);
char		*hd_unquote_delim(const char *s);

int			hd_write_line(int fd, const char *s);

int			hd_read_loop(t_hd *h);

int			process_heredoc(t_redir *r, char **envp, int *last_status);
int			setup_heredocs(t_cmd *cmds, char **envp, int *last_status);

int			hd_init(t_hd *h, t_redir *r, char **envp, int *last_status);
int			hd_make_and_open(t_hd *h, char **out_name);
void		hd_cleanup_parent(t_hd *h);
int			hd_set_target(t_redir *r, char *fname);

#endif