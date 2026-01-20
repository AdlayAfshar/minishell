#ifndef SHELL_H
# define SHELL_H

typedef struct s_cmd	t_cmd;
typedef struct s_shell_ctx
{
	char				*line;
	t_cmd				*cmds;
	char				**envp;
	int					exit_status;

}						t_shell_ctx;

int						process_line(t_shell_ctx *ctx);
int						process_pasted_lines(t_shell_ctx *ctx);
void					trim_cr(char *s);

#endif