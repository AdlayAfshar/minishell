
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

void	handle_signals(void);
void	exec_pipeline(t_cmd *cmds, char **envp);
// void    rl_replace_line(const char *text, int clear_undo);

#endif
