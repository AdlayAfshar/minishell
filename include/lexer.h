#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <stdio.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// # include "libft.h"

// tokens 

typedef enum e_tok_type
{
	TOK_WORD,
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

// buffer used while reading a word
typedef struct s_wbuf
{
	char	*data;
	size_t	len;
	size_t	cap;
}	t_wbuf;


t_token	*lex_line(const char *s);
void	token_list_clear(t_token **lst);

int	    is_space(char c);
void	skip_spaces(const char *s, size_t *i);
int		is_op_char(char c);
char	*read_word(const char *s, size_t *i);
int		process_word_char(const char *s, size_t *i, t_wbuf *b);
int		lex_try_operator(const char *s, size_t *i, t_token **lst);

t_token	*token_new(char *value, t_tok_type type);
void	token_add_back(t_token **lst, t_token *new);

#endif
