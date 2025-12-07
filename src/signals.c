
#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

#ifdef __APPLE__
void    rl_replace_line(const char *text, int clear_undo)
{
    (void)text;
    (void)clear_undo;
}
#endif

static void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
}

void	handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
