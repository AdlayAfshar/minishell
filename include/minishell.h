
// #ifndef MINISHELL_H
// # define MINISHELL_H

// # include <unistd.h>
// # include <fcntl.h>
// # include <stdlib.h>
// # include <sys/wait.h>
// # include <stdio.h>
// # include "./libft/libft.h"

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	handle_signals(void);

#endif
