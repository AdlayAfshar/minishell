
#include "signals.h"
#include <readline/readline.h>

volatile sig_atomic_t	g_sig = 0;

void	set_signal_handler(int sig, void (*handler)(int)     )
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(sig, &sa, NULL);
}

static void	sigint_handler(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_sig_interactive(void)
{
	set_signal_handler(SIGINT, sigint_handler);
	set_signal_handler(SIGQUIT, SIG_IGN);
}

void	set_sig_child_default(void)
{
	set_signal_handler(SIGINT, SIG_DFL);
	set_signal_handler(SIGQUIT, SIG_DFL);
}

void	set_sig_parent_ignore(void)
{
	set_signal_handler(SIGINT, SIG_IGN);
	set_signal_handler(SIGQUIT, SIG_IGN);
}

// void	set_sig_parent_exec(void)
// {
// 	struct sigaction	sa;

// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sa.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }
