
#include "minishell.h"

// void	ms_set_termios(void)
// {
// 	struct termios	t;

// 	if (tcgetattr(STDIN_FILENO, &t) == -1)
// 		return ;
// 	t.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &t);
// }
void	ms_set_termios(int on)
{
	struct termios	t;

	if (tcgetattr(STDIN_FILENO, &t) == -1)
		return ;
	if (on)
		t.c_lflag |= ECHOCTL;
	else
		t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

// static void	ms_set_echoctl(int on)
// {
// 	struct termios	t;

// 	if (tcgetattr(STDIN_FILENO, &t) == -1)
// 		return ;
// 	if (on)
// 		t.c_lflag |= ECHOCTL;
// 	else
// 		t.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &t);
// }

// ECHOCTL فلگی است که باعث می‌شود کاراکترهای کنترلی به شکل قابل دیدن چاپ شوند.
// 	~ECHOCTL یعنی «برعکسِ ECHOCTL» 
//&= یعنی «روی فلگ‌ها عمل AND انجام بده و نتیجه را ذخیره کن»

// این تابع کلاً چه کار می‌کند؟
// این تابع تنظیمات ترمینال را طوری تغییر می‌دهد که:
// وقتی کاربر کلیدهای کنترلی مثل Ctrl+C را می‌زند،
// علامت‌هایی مثل ^C روی صفحه چاپ نشوند.

// t.c_lflag &= ~ECHOCTL;
// این مهم‌ترین خط تابع است.
// معنی ساده‌اش:
// 	•	ترمینال یک سری «فلگ رفتاری» دارد
// 	•	یکی از آن‌ها باعث می‌شود کلیدهای کنترلی دیده شوند
// 	•	این خط آن فلگ را خاموش می‌کند
// بعد از این:
// 	•	وقتی Ctrl+C بزنی
// 	•	دیگر ^C روی صفحه چاپ نمی‌شود

// tcsetattr(STDIN_FILENO, TCSANOW, &t);
// این خط:
// 	•	تنظیمات جدیدی که تغییر دادیم
// 	•	را همین الان
// 	•	روی ترمینال اعمال می‌کند

// از این لحظه به بعد، رفتار ترمینال تغییر کرده است.


// --------------
// What does this function do?
// This function modifies the terminal settings so that:
// Control characters like Ctrl+C are not printed as ^C on the screen.
// It only affects how input is displayed, not how signals work.

// if (tcgetattr(STDIN_FILENO, &t) == -1)
    // return;
// This line:
// 	•	reads the current terminal settings
// 	•	associated with standard input
// 	•	and stores them in t
// If it fails:
// 	•	the function exits immediately
// 	•	nothing is changed

// t.c_lflag &= ~ECHOCTL;
// This is the key line.
// It:
// 	•	accesses the local behavior flags of the terminal
// 	•	disables the flag responsible for echoing control characters
// After this:
// 	•	pressing Ctrl+C will no longer print ^C

// tcsetattr(STDIN_FILENO, TCSANOW, &t);
// This line:
// 	•	applies the modified terminal settings
// 	•	immediately
// 	•	to standard input
// From this point on, the terminal behavior is changed.
