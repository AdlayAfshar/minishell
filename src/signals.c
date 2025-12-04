
#include "../include/minishell.h"
#include "../include/signal.h"

volatile int g_signal = 0;


static void	sigint_handler(int sig)
{
	g_signal = sig;
	rl_done = 1;
}
/*Saves the signal to the global memory
 rl_done = 1 makes readline terminate immediately → perfect*/
/*static void sigquit_handler(int sig)
{
(void)sig;

}
} - not needed */

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);//sigquit_handler);
}
/*Signal configuration. This is even better: it makes Ctrl-\ literally do nothing, like bash.

You no longer need sigquit_handler.*/
/* User presses Ctrl-C

sigquit_handler executes

rl_done = 1 → readline ends

Return to the main loop with line = NULL or an empty string

Your code detects that g_signal == SIGINT

Clear line, print newline, and refresh prompt

continue → goes to the next loop → new prompt like bash*/