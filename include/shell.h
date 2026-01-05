#ifndef SHELL_H
# define SHELL_H


int	    process_line(char *line, char ***envp, int *exit_status);
void	process_pasted_lines(char *line, char ***envp, int *exit_status);
void	trim_cr(char *s);

#endif