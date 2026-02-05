#ifndef SHELL_H
# define SHELL_H
# include <sys/types.h>
# include <termios.h>

typedef struct s_cmd	t_cmd;
typedef struct s_shell_ctx
{
	char				*line;
	char				*current_subline;
	t_cmd				*cmds;
	char				**envp;
	pid_t				*pids;
	int					prev_fd;
	int					exit_status;
	struct termios		term_orig;

}						t_shell_ctx;

void					exit_and_clear_ctx(int exit_code, t_shell_ctx *ctx);
void					free_ctx(t_shell_ctx *ctx);
int						process_line(t_shell_ctx *ctx);
int						process_pasted_lines(t_shell_ctx *ctx);
void					trim_cr(char *s);

#endif