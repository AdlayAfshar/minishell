
#include "signals.h"
#include <readline/readline.h>

extern int	rl_done;

static void	sigint_heredoc_child(int sig)
{
	g_sig = sig;
	rl_done = 1;
	ioctl(0, TIOCSTI, "\n");
}

void	set_sig_heredoc_child(void)
{
	set_signal_handler(SIGINT, sigint_heredoc_child);
	set_signal_handler(SIGQUIT, SIG_IGN);
}
