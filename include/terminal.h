#ifndef TERMINAL_H
# define TERMINAL_H

# include <termios.h>
# include <unistd.h>
# include <shell.h>

void	ms_set_termios(int on);
void	ms_restore_termios(t_shell_ctx *ctx);

#endif