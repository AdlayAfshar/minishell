
#include "signals.h"
#include <readline/readline.h>

extern int	rl_done;

// void	set_sig_heredoc_parent(void)
// {
// 	struct sigaction	sa;

// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sa.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }

static void	sigint_heredoc_child(int sig)
{
	g_sig = sig;
	rl_done = 1;
	ioctl(0, TIOCSTI, "\n");
	write(0, "arman\n", 6);
	// rl_replace_line("", 0);
	// rl_on_new_line();
}

void	set_sig_heredoc_parent(void)
{
	set_signal_handler(SIGINT, SIG_IGN);
	set_signal_handler(SIGQUIT, SIG_IGN);
}

void	set_sig_heredoc_child(void)
{
	set_signal_handler(SIGINT, sigint_heredoc_child);
	set_signal_handler(SIGQUIT, SIG_IGN);
}
