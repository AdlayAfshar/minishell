
#include "signals.h"
#include <readline/readline.h>

extern int	rl_done;

void	set_sig_heredoc_parent(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static void	sigint_heredoc_child(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	rl_done = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(0, TIOCSTI, "\n");
}

void	set_sig_heredoc_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_heredoc_child;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
