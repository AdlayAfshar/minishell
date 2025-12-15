#include "minishell.h"

extern int	g_exit_status;

/*
** SIGINT handler در حالت پرامپت (interactive)
** وقتی Ctrl-C می‌زنی:
**   - یک خط جدید چاپ می‌کند
**   - خط فعلی را پاک می‌کند
**   - پرامپت جدید را نشان می‌دهد
*/
void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
** تنظیم سیگنال‌ها در حالت شل تعاملی (main loop)
**   - SIGINT → sigint_handler
**   - SIGQUIT → نادیده گرفته می‌شود
*/
void	set_sig_interactive(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/*
** تنظیم سیگنال‌ها برای parent در زمان heredoc:
**   - SIGINT → نادیده گرفته می‌شود (تا فقط child بمیرد)
**   - SIGQUIT → نادیده گرفته می‌شود
*/
void	set_sig_heredoc_parent(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/*
** تنظیم سیگنال‌ها برای child بعد از fork:
**   - SIGINT → رفتار پیش‌فرض (قطع شدن پروسه)
**   - SIGQUIT → رفتار پیش‌فرض
** این تابع را در child قبل از execve در exec_cmd_child صدا بزن.
*/
void	set_sig_child_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
////////////////////////////////////////
// #include "../include/minishell.h"
// #include <readline/readline.h>
// #include <readline/history.h>

// #ifdef __APPLE__
// void    rl_replace_line(const char *text, int clear_undo)
// {
//     (void)text;
//     (void)clear_undo;
// }
// #endif

// static void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// static void	sigquit_handler(int sig)
// {
// 	(void)sig;
// }

// void	handle_signals(void)
// {
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, sigquit_handler);
// }

// // #include "../include/minishell.h"
// // #include <signal.h>

// void	set_sig_interactive(void)
// {
// 	struct sigaction	sa;

// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;
// 	sa.sa_handler = sigint_handler; /* همونی که برای پرامپت نوشتی */
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	set_sig_heredoc_parent(void)
// {
// 	struct sigaction	sa;

// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sa.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }

/////////////////////////////////////////
// #include "../include/minishell.h"
// #include "../include/signal.h"

// volatile int g_signal = 0;


// static void	sigint_handler(int sig)
// {
// 	g_signal = sig;
// 	rl_done = 1;
// }
// /*Saves the signal to the global memory
//  rl_done = 1 makes readline terminate immediately → perfect*/
// /*static void sigquit_handler(int sig)
// {
// (void)sig;

// }
// } - not needed */

// void	handle_signals(void)
// {
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);//sigquit_handler);
// }
// /*Signal configuration. This is even better: it makes Ctrl-\ literally do nothing, like bash.

// You no longer need sigquit_handler.*/
// /* User presses Ctrl-C

// sigquit_handler executes

// rl_done = 1 → readline ends

// Return to the main loop with line = NULL or an empty string

// Your code detects that g_signal == SIGINT

// Clear line, print newline, and refresh prompt

// continue → goes to the next loop → new prompt like bash*/
