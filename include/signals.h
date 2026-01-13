#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_sig;

extern int						rl_catch_signals;
extern int						rl_catch_sigwinch;

void							sigint_handler(int sig);
void							set_sig_interactive(void);
void							set_sig_heredoc_parent(void);
void							set_sig_child_default(void);
void							set_sig_parent_exec(void);
void							set_sig_heredoc_child(void);

#endif