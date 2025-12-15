#include "minishell.h"

int	grow_buf(t_exp *e, size_t need)
{
	char	*nbuf;
	size_t	ncap;

	if (e->cap >= need)
		return (0);
	ncap = e->cap;
	if (ncap == 0)
		ncap = 32;
	while (ncap < need)
		ncap *= 2;
	nbuf = (char *)malloc(ncap);
	if (!nbuf)
		return (1);
	if (e->buf && e->len > 0)
		ft_memcpy(nbuf, e->buf, e->len);
	free(e->buf);
	e->buf = nbuf;
	e->cap = ncap;
	return (0);
}

int	append_char(t_exp *e, char c)
{
	if (grow_buf(e, e->len + 2))
		return (1);
	e->buf[e->len++] = c;
	return (0);
}

int	append_str(t_exp *e, const char *str)
{
	size_t	j;

	if (!str)
		return (0);
	if (grow_buf(e, e->len + ft_strlen(str) + 1))
		return (1);
	j = 0;
	while (str[j])
	{
		e->buf[e->len++] = str[j];
		j++;
	}
	return (0);
}

int	expand_status(size_t *i, t_exp *e)
{
	char	*tmp;
	int		res;

	tmp = ft_itoa(e->last_status);
	if (!tmp)
		return (1);
	res = append_str(e, tmp);
	free(tmp);
	if (res)
		return (1);
	(*i)++;
	return (0);
}

int	expand_env_var(const char *s, size_t *i, t_exp *e)
{
	char	name[256];
	size_t	j;
	char	*val;

	j = 0;
	while (s[*i] && is_var_char(s[*i]) && j < 255)
	{
		name[j] = s[*i];
		j++;
		(*i)++;
	}
	name[j] = '\0';
	val = exp_get_env_val(name, e->envp);
	if (append_str(e, val))
		return (1);
	return (0);
}