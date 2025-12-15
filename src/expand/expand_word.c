
#include "minishell.h"

static void	init_exp(t_exp *e, char **envp, int last_status)
{
	e->buf = NULL;
	e->len = 0;
	e->cap = 0;
	e->envp = envp;
	e->last_status = last_status;
}

static int	expand_dollar(const char *s, size_t *i, t_exp *e)
{
	(*i)++;
	if (!s[*i])
		return (append_char(e, '$'));
	if (s[*i] == '?')
		return (expand_status(i, e));
	if (!is_var_start(s[*i]))
		return (append_char(e, '$'));
	if (expand_env_var(s, i, e))
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

static int	handle_dollar_or_char(const char *s, size_t *i,
				t_exp *e, int in_s)
{
	if (s[*i] == '$' && !in_s)
	{
		if (expand_dollar(s, i, e))
			return (1);
		return (0);
	}
	if (append_char(e, s[*i]))
		return (1);
	(*i)++;
	return (0);
}

char	*expand_word(const char *s, char **envp, int last_status)
{
	t_exp	e;
	size_t	i;
	int		in_s;
	int		in_d;

	if (!s)
		return (NULL);
	init_exp(&e, envp, last_status);
	i = 0;
	in_s = 0;
	in_d = 0;
	while (s[i])
	{
		if (handle_quotes(s, &i, &in_s, &in_d))
			continue ;
		if (handle_dollar_or_char(s, &i, &e, in_s))
			return (free(e.buf), NULL);
	}
	if (append_char(&e, '\0'))
		return (free(e.buf), NULL);
	return (e.buf);
}

//////////////

// #include "minishell.h"

// static int	grow_buf(t_exp *e, size_t need)
// {
// 	char	*nbuf;
// 	size_t	ncap;

// 	if (e->cap >= need)
// 		return (0);
// 	ncap = e->cap;
// 	if (ncap == 0)
// 		ncap = 32;
// 	while (ncap < need)
// 		ncap *= 2;
// 	nbuf = (char *)malloc(ncap);
// 	if (!nbuf)
// 		return (1);
// 	if (e->buf && e->len > 0)
// 		ft_memcpy(nbuf, e->buf, e->len);
// 	free(e->buf);
// 	e->buf = nbuf;
// 	e->cap = ncap;
// 	return (0);
// }

// static int	append_char(t_exp *e, char c)
// {
// 	if (grow_buf(e, e->len + 2))
// 		return (1);
// 	e->buf[e->len++] = c;
// 	return (0);
// }

// static int	append_str(t_exp *e, const char *str)
// {
// 	size_t	j;

// 	if (!str)
// 		return (0);
// 	if (grow_buf(e, e->len + ft_strlen(str) + 1))
// 		return (1);
// 	j = 0;
// 	while (str[j])
// 	{
// 		e->buf[e->len++] = str[j];
// 		j++;
// 	}
// 	return (0);
// }

// static void	init_exp(t_exp *e, char **envp, int last_status)
// {
// 	e->buf = NULL;
// 	e->len = 0;
// 	e->cap = 0;
// 	e->envp = envp;
// 	e->last_status = last_status;
// }

// static int	expand_status(size_t *i, t_exp *e)
// {
// 	char	*tmp;
// 	int		res;

// 	tmp = ft_itoa(e->last_status);
// 	if (!tmp)
// 		return (1);
// 	res = append_str(e, tmp);
// 	free(tmp);
// 	if (res)
// 		return (1);
// 	(*i)++;
// 	return (0);
// }

// static int	expand_env_var(const char *s, size_t *i, t_exp *e)
// {
// 	char	name[256];
// 	size_t	j;
// 	char	*val;

// 	j = 0;
// 	while (s[*i] && is_var_char(s[*i]) && j < 255)
// 	{
// 		name[j] = s[*i];
// 		j++;
// 		(*i)++;
// 	}
// 	name[j] = '\0';
// 	val = exp_get_env_val(name, e->envp);
// 	if (append_str(e, val))
// 		return (1);
// 	return (0);
// }

// static int	expand_dollar(const char *s, size_t *i, t_exp *e)
// {
// 	(*i)++;
// 	if (!s[*i])
// 		return (append_char(e, '$'));
// 	if (s[*i] == '?')
// 		return (expand_status(i, e));
// 	if (!is_var_start(s[*i]))
// 		return (append_char(e, '$'));
// 	if (expand_env_var(s, i, e))
// 		return (1);
// 	return (0);
// }

// static int	handle_quotes(const char *s, size_t *i, int *in_s, int *in_d)
// {
// 	if (s[*i] == '\'' && !(*in_d))
// 	{
// 		*in_s = !(*in_s);
// 		(*i)++;
// 		return (1);
// 	}
// 	if (s[*i] == '\"' && !(*in_s))
// 	{
// 		*in_d = !(*in_d);
// 		(*i)++;
// 		return (1);
// 	}
// 	return (0);
// }

// static int	handle_dollar_or_char(const char *s, size_t *i,
// 				t_exp *e, int in_s)
// {
// 	if (s[*i] == '$' && !in_s)
// 	{
// 		if (expand_dollar(s, i, e))
// 			return (1);
// 		return (0);
// 	}
// 	if (append_char(e, s[*i]))
// 		return (1);
// 	(*i)++;
// 	return (0);
// }


// char	*expand_word(const char *s, char **envp, int last_status)
// {
// 	t_exp	e;
// 	size_t	i;
// 	int		in_s;
// 	int		in_d;

// 	if (!s)
// 		return (NULL);
// 	init_exp(&e, envp, last_status);
// 	i = 0;
// 	in_s = 0;
// 	in_d = 0;
// 	while (s[i])
// 	{
// 		if (handle_quotes(s, &i, &in_s, &in_d))
// 			continue ;
// 		if (handle_dollar_or_char(s, &i, &e, in_s))
// 			return (free(e.buf), NULL);
// 	}
// 	if (append_char(&e, '\0'))
// 		return (free(e.buf), NULL);
// 	return (e.buf);
// }
///////////////
// #include "minishell.h"

// static int	grow_buf(t_exp *e, size_t need)
// {
// 	char	*nbuf;
// 	size_t	ncap;
// 	size_t	i;

// 	if (e->cap >= need)
// 		return (0);
// 	ncap = e->cap;
// 	if (ncap == 0)
// 		ncap = 32;
// 	while (ncap < need)
// 		ncap *= 2;
// 	nbuf = (char *)malloc(ncap);
// 	if (!nbuf)
// 		return (1);
// 	i = 0;
// 	while (i < e->len)
// 	{
// 		nbuf[i] = e->buf[i];
// 		i++;
// 	}
// 	free(e->buf);
// 	e->buf = nbuf;
// 	e->cap = ncap;
// 	return (0);
// }

// // 51 line
// static int	expand_dollar(const char *s, size_t *i, t_exp *e)
// {
// 	char	name[256];
// 	size_t	j;
// 	char	*val;
// 	char	*tmp;

// 	(*i)++;
// 	if (!s[*i])
// 	{
// 		if (grow_buf(e, e->len + 2))
// 			return (1);
// 		e->buf[e->len++] = '$';
// 		return (0);
// 	}
// 	if (s[*i] == '?')
// 	{
// 		tmp = ft_itoa(e->last_status);
// 		if (!tmp)
// 			return (1);
// 		if (grow_buf(e, e->len + ft_strlen(tmp) + 1))
// 			return (free(tmp), 1);
// 		j = 0;
// 		while (tmp[j])
// 			e->buf[e->len++] = tmp[j++];
// 		free(tmp);
// 		(*i)++;
// 		return (0);
// 	}
// 	if (!is_var_start(s[*i]))
// 	{
// 		if (grow_buf(e, e->len + 2))
// 			return (1);
// 		e->buf[e->len++] = '$';
// 		return (0);
// 	}
// 	j = 0;
// 	while (s[*i] && is_var_char(s[*i]) && j < 255)
// 	{
// 		name[j++] = s[*i];
// 		(*i)++;
// 	}
// 	name[j] = '\0';
// 	val = exp_get_env_val(name, e->envp);
// 	if (!val)
// 		return (0);
// 	if (grow_buf(e, e->len + ft_strlen(val) + 1))
// 		return (1);
// 	j = 0;
// 	while (val[j])
// 		e->buf[e->len++] = val[j++];
// 	return (0);
// }

// // 45 line
// char	*expand_word(const char *s, char **envp, int last_status)
// {
// 	t_exp	e;
// 	size_t	i;
// 	int		in_s;
// 	int		in_d;

// 	if (!s)
// 		return (NULL);
// 	e.buf = NULL;
// 	e.len = 0;
// 	e.cap = 0;
// 	e.envp = envp;
// 	e.last_status = last_status;
// 	i = 0;
// 	in_s = 0;
// 	in_d = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '\'' && !in_d)
// 		{
// 			in_s = !in_s;
// 			i++;
// 			continue ;
// 		}
// 		if (s[i] == '\"' && !in_s)
// 		{
// 			in_d = !in_d;
// 			i++;
// 			continue ;
// 		}
// 		if (s[i] == '$' && !in_s)
// 		{
// 			if (expand_dollar(s, &i, &e))
// 				return (free(e.buf), NULL);
// 			continue ;
// 		}
// 		if (grow_buf(&e, e.len + 2))
// 			return (free(e.buf), NULL);
// 		e.buf[e.len++] = s[i];
// 		i++;
// 	}
// 	if (grow_buf(&e, e.len + 1))
// 		return (free(e.buf), NULL);
// 	e.buf[e.len] = '\0';
// 	return (e.buf);
// }