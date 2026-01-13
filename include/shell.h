#ifndef SHELL_H
# define SHELL_H

typedef struct s_line_ctx
{
	char	***envp;
	int		*exit_status;
}			t_line_ctx;

int			process_line(char *line, char ***envp, int *exit_status);
int			process_pasted_lines(char *line, char ***envp, int *exit_status);
void		trim_cr(char *s);

#endif