#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

typedef enum e_tok_type
{
	TOK_WORD = 0,
	TOK_PIPE,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_HEREDOC,
	TOK_APPEND
}	t_tok_type;

typedef struct s_token
{
	t_tok_type		type;
	char			*val;
	struct s_token	*next;
}	t_token;

/* ساخت/مدیریت توکن‌ها */
t_token	*tok_new(t_tok_type type, const char *val, size_t len);
void	tok_push(t_token **lst, t_token *node);
void	free_tokens(t_token *t);

/* لکسینگ خط ورودی */
t_token	*lex_line(const char *s);

#endif
