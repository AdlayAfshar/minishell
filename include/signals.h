#ifndef SIGNALS_H
# define SIGNALS_H

void    sigint_handler(int sig);
void    set_sig_interactive(void);
void    set_sig_heredoc_parent(void);
void    set_sig_child_default(void);
void	consume_sigint_interactive(int *exit_status);

#endif