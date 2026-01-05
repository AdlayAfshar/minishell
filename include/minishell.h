
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "builtins.h"
# include "env.h"
# include "expand.h"
# include "heredoc.h"
# include "signals.h"

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <errno.h>

extern volatile sig_atomic_t	g_sig;
#define EXIT_REQ_BASE 1000

void	ms_set_termios(int on);

#endif
