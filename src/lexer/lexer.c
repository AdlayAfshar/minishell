
#include "../../include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* --- Helpers --- */

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

static void	skip_spaces(const char *s, size_t *i)
{
	while (s[*i] && is_space(s[*i]))
		(*i)++;
}

static t_tok_type	match_op(const char *s, size_t i, size_t *consumed)
{
	if (s[i] == '|')
	{
		*consumed = 1;
		return (TOK_PIPE);
	}
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
	{
		*consumed = 1;
		return (TOK_REDIR_IN);
	}
	if (s[i] == '>')
	{
		*consumed = 1;
		return (TOK_REDIR_OUT);
	}
	*consumed = 0;
	return (TOK_WORD);
}

static char	*grow_buf(char *buf, size_t *cap, size_t need)
{
	char	*nbuf;
	size_t	ncap;

	if (*cap >= need)
		return (buf);
	ncap = (*cap == 0) ? 32 : *cap;
	while (ncap < need)
		ncap *= 2;
	nbuf = (char *)malloc(ncap);
	if (!nbuf)
	{
		free(buf);
		return (NULL);
	}
	if (buf)
		memcpy(nbuf, buf, *cap);
	free(buf);
	*cap = ncap;
	return (nbuf);
}

/* --- Reading words with quotes preserved --- */

static int	read_quoted(const char *s, size_t *i, char **buf, size_t *len,
		size_t *cap)
{
	char	q;

	q = s[*i];
	(*i)++;
	if (!s[*i])
		return (-1);
	while (s[*i] && s[*i] != q)
	{
		*buf = grow_buf(*buf, cap, *len + 2);
		if (!*buf)
			return (-2);
		(*buf)[(*len)++] = s[*i];
		(*i)++;
	}
	if (s[*i] != q)
		return (-1);
	(*i)++;
	return (0);
}

static char	*read_word(const char *s, size_t *i)
{
	char	*buf;
	size_t	len;
	size_t	cap;
	char	q;

	buf = NULL;
	len = 0;
	cap = 0;
	while (s[*i] && !is_space(s[*i]))
	{
		if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
			break ;
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			q = s[*i];
			/* اضافه‌کردن خود کاراکتر کوت باز */
			buf = grow_buf(buf, &cap, len + 2);
			if (!buf)
				return (NULL);
			buf[len++] = q;
			if (read_quoted(s, i, &buf, &len, &cap) != 0)
			{
				free(buf);
				return (NULL);
			}
			/* اضافه‌کردن خود کاراکتر کوت بسته */
			buf = grow_buf(buf, &cap, len + 2);
			if (!buf)
				return (NULL);
			buf[len++] = q;
			continue ;
		}
		buf = grow_buf(buf, &cap, len + 2);
		if (!buf)
			return (NULL);
		buf[len++] = s[*i];
		(*i)++;
	}
	if (!buf)
		return (strdup(""));
	buf[len] = '\0';
	return (buf);
}

/* --- Main lexing loop --- */

static int	add_op_token(t_token **lst, const char *s, size_t *i)
{
	size_t		cons;
	t_tok_type	t;
	t_token		*node;

	t = match_op(s, *i, &cons);
	if (cons == 0)
		return (0);
	node = tok_new(t, NULL, 0);
	if (!node)
		return (-1);
	tok_push(lst, node);
	*i += cons;
	return (1);
}

t_token	*lex_line(const char *s)
{
	size_t	i;
	t_token	*lst;
	int		r;
	char	*w;
	t_token	*node;

	if (!s)
		return (NULL);
	i = 0;
	lst = NULL;
	while (s[i])
	{
		skip_spaces(s, &i);
		if (!s[i])
			break ;
		r = add_op_token(&lst, s, &i);
		if (r < 0)
			return (free_tokens(lst), NULL);
		if (r > 0)
			continue ;
		{
			w = read_word(s, &i);
			if (!w)
				return (free_tokens(lst), NULL);
			node = tok_new(TOK_WORD, w, strlen(w));
			free(w);
			if (!node)
				return (free_tokens(lst), NULL);
			tok_push(&lst, node);
		}
	}
	return (lst);
}
