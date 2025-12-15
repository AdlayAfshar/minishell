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