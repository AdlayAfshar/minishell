#include "minishell.h"

// match operator at position i and set how many chars were consumed 
static t_tok_type	match_op(const char *s, size_t i, size_t *consumed)
{
	*consumed = 1;
	if (s[i] == '|')
		return (TOK_PIPE);
	if (s[i] == '<' && s[i + 1] == '<')
	{
		*consumed = 2;
		return (TOK_HEREDOC);
	}
	if (s[i] == '>' && s[i + 1] == '>')
	{
		*consumed = 2;
		return (TOK_APPEND);
	}
	if (s[i] == '<')
		return (TOK_REDIR_IN);
	if (s[i] == '>')
		return (TOK_REDIR_OUT);
	if (s[i] == ';')
    	return (TOK_SEMI);
	*consumed = 0;
	return (TOK_WORD);
}

// try to read an operator token at s[*i]
int	lex_try_operator(const char *s, size_t *i, t_token **lst)
{
	size_t		consumed;
	t_tok_type	type;
	t_token		*node;

	if (!is_op_char(s[*i]))
		return (0);
	type = match_op(s, *i, &consumed);
	if (type == TOK_WORD)
		return (0);
	node = token_new(NULL, type);
	if (!node)
		return (-1);
	token_add_back(lst, node);
	*i += consumed;
	return (1);
}