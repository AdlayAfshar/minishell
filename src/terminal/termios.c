
#include "terminal.h"
#include "shell.h"

void	ms_set_termios(int on)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return ;
	if (on)
		t.c_lflag |= ECHOCTL;
	else
		t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void	ms_restore_termios(t_shell_ctx *ctx)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &ctx->term_orig);
}

