
#include "expand.h"
#include "shell.h"

static void	init_exp(t_exp *e)
{
	e->buf = NULL;
	e->len = 0;
	e->cap = 0;
}

static int	expand_dollar(const char *s, size_t *i, t_exp *e, t_shell_ctx *ctx)
{
	(*i)++;
	if (!s[*i])
		return (append_char(e, '$'));
	if (s[*i] == '?')
		return (expand_status(i, e, ctx));
	if (ft_isdigit((unsigned char)s[*i]))
	{
		(*i)++;
		return (0);
	}
	if (!is_var_start(s[*i]))
		return (append_char(e, '$'));
	if (expand_env_var(s, i, e, ctx))
		return (1);
	return (0);
}

static int	handle_quotes(const char *s, size_t *i, int *in_s, int *in_d)
{
	if (s[*i] == '\'' && !(*in_d))
	{
		*in_s = !(*in_s);
		(*i)++;
		return (1);
	}
	if (s[*i] == '\"' && !(*in_s))
	{
		*in_d = !(*in_d);
		(*i)++;
		return (1);
	}
	return (0);
}

static int	handle_dollar_or_char(const char *s, size_t *i, t_exp *e, int in_s,
		t_shell_ctx *ctx)
{
	if (s[*i] == '$' && !in_s)
	{
		if (expand_dollar(s, i, e, ctx))
			return (1);
		return (0);
	}
	if (append_char(e, s[*i]))
		return (1);
	(*i)++;
	return (0);
}

char	*expand_word(const char *s, t_shell_ctx *ctx)
{
	t_exp	e;
	size_t	i;
	int		in_s;
	int		in_d;

	if (!s)
		return (NULL);
	init_exp(&e);
	i = 0;
	in_s = 0; // single quote
	in_d = 0; // double quote
	while (s[i])
	{
		if (handle_quotes(s, &i, &in_s, &in_d))
			continue ;
		if (handle_dollar_or_char(s, &i, &e, in_s, ctx))
			return (free(e.buf), NULL);
	}
	if (append_char(&e, '\0'))
		return (free(e.buf), NULL);
	return (e.buf);
}
