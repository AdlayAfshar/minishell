
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

extern int	g_exit_status;

void	ms_set_termios(void);

#endif
