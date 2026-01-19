
#include "signals.h"
#include <readline/readline.h>

volatile sig_atomic_t	g_sig = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_sig_interactive(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	set_sig_child_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_sig_parent_ignore(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN; 
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
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
