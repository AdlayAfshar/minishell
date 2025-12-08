#include "minishell.h"

// helper to clear token list and return NULL on error
static t_token	*lex_lex_error(t_token **lst)
{
	token_list_clear(lst);
	return (NULL);
}

// read one WORD token and append it to the list
static int	lex_add_word(const char *s, size_t *i, t_token **lst)
{
	char	*w;
	t_token	*node;

	w = read_word(s, i);
	if (!w)
		return (-1);
	node = token_new(w, TOK_WORD);
	if (!node)
	{
		free(w);
		return (-1);
	}
	token_add_back(lst, node);
	return (0);
}

// main lexer: builds a linked list of tokens from the input line
t_token	*lex_line(const char *s)
{
	size_t	i;
	t_token	*lst;
	int		r;

	if (!s)
		return (NULL);
	i = 0;
	lst = NULL;
	while (s[i])
	{
		skip_spaces(s, &i);
		if (!s[i])
			break ;
		r = lex_try_operator(s, &i, &lst);
		if (r < 0)
			return (lex_lex_error(&lst));
		if (r == 1)
			continue ;
		if (lex_add_word(s, &i, &lst) < 0)
			return (lex_lex_error(&lst));
	}
	return (lst);
}