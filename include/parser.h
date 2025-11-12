#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

/* انواع ریدایرکشن */
typedef enum e_redir_type
{
	R_IN = 0,     /* <  */
	R_OUT,        /* >  */
	R_APPEND,     /* >> */
	R_HEREDOC     /* << */
}	t_redir_type;

/* نود ریدایرکشن */
typedef struct s_redir
{
	t_redir_type	 type;
	char			 *target;        /* نام فایل یا delimiter (خام، با کوت‌های احتمالی) */
	int				 heredoc_quoted; /* برای << آیا delimiter کوت‌دار است؟ */
	struct s_redir	 *next;
}	t_redir;

/* یک فرمان در pipeline */
typedef struct s_cmd
{
	char			**argv;   /* NULL-terminated */
	t_redir			*redirs;
	struct s_cmd	*next;    /* فرمان بعدی در pipeline (پس از |) */
}	t_cmd;

/* API پارسر */
t_cmd	*parse_tokens(t_token *ts);
void	free_cmds(t_cmd *cmd);

#endif
