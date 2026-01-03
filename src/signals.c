#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
// extern int	rl_done;
/*
** SIGINT handler در حالت پرامپت (interactive)
** وقتی Ctrl-C می‌زنی:
**   - یک خط جدید چاپ می‌کند
**   - خط فعلی را پاک می‌کند
**   - پرامپت جدید را نشان می‌دهد
*/
// void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	g_sig = SIGINT;
// 	write(1, "\n", 1);
// 	// write(2, "H\n", 2);
// }

// void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	g_sig = SIGINT;
// 	rl_done = 1;
// 	write(1, "\n", 1);
// 	// write(2, "H\n", 2);
// }

void	sigint_handler(int sig)
{
	(void)sig;
	g_sig = SIGINT;
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
	// write(2, "INTERACTIVE_SIG\n", 16);
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	// sa.sa_flags = SA_RESTART;
	sa.sa_flags = 0;
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
	// write(2, "HD_PARENT_SIG\n", 14);
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

// static void	sigint_heredoc(int sig)
// {
// 	(void)sig;
// 	g_sig = SIGINT;
// 	write(1, "\n", 1);
// }

// void	set_sig_heredoc_parent(void)
// {
// 	struct sigaction	sa;

// 	g_sig = 0;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sa.sa_handler = sigint_heredoc;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }

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

// void	consume_sigint_interactive(int *exit_status)
// {
// 	if (g_sig == SIGINT)
// 	{
// 		*exit_status = 130;
// 		g_sig = 0;
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }


// init_interactive_signals
// 	•	قبل از هر چیزی اجرا می‌شود (معمولاً ابتدای برنامه)
// 	•	“سیستم دریافت سیگنال” را تنظیم می‌کند
// 	•	می‌گوید SIGINT را به چه handler بدهیم
// 	•	کاری به پاک کردن خط و پرامپت ندارد

// consume_sigint_interactive
// 	•	بعد از دریافت سیگنال اجرا می‌شود (مثلاً بعد از readline)
// 	•	نتیجه‌ی Ctrl+C را در شل اعمال می‌کند
// 	•	status و رابط کاربری را درست می‌کند

// static void	sigint_parent_exec(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// }

void	set_sig_parent_exec(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	// sa.sa_handler = sigint_parent_exec;
	sa.sa_handler = SIG_IGN; 
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
// nnn
extern int	rl_done;

static void	sigint_heredoc_child(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	rl_done = 1;
	write(1, "\n", 1);
}

// last

// static void	sigint_heredoc_child(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	_exit(130);
// }

void	set_sig_heredoc_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_heredoc_child;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}