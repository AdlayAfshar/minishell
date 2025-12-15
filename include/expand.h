#ifndef EXPAND_H
# define EXPAND_H

# include "parser.h"

typedef struct s_exp
{
	char	*buf;
	size_t	len;
	size_t	cap;
	char	**envp;
	int		last_status;
}	t_exp;


/* از اینا در expand_word.c استفاده می‌کنیم */
int		is_var_start(char c);
int		is_var_char(char c);
char	*exp_get_env_val(const char *name, char **envp);

/* expand یک کلمه (argv[i] یا target ریدایرکشن) */
char	*expand_word(const char *s, char **envp, int last_status);

/* expand روی کل لیست فرمان‌ها (argv + redirs) */
int		expand_all(t_cmd *cmds, char **envp, int last_status);

int		grow_buf(t_exp *e, size_t need);
int		append_char(t_exp *e, char c);
int		append_str(t_exp *e, const char *str);
int		expand_status(size_t *i, t_exp *e);
int		expand_env_var(const char *s, size_t *i, t_exp *e);


#endif