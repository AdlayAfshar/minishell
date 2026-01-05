
#include "parser.h"

int	has_quote(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

static size_t	argv_count(char **argv)
{
	size_t	n;

	n = 0;
	if (argv == NULL)
		return (0);
	while (argv[n] != NULL)
		n++;
	return (n);
}

static char	**argv_alloc_copy(char **argv, size_t n)
{
	char	**nv;
	size_t	i;

	nv = (char **)malloc(sizeof(char *) * (n + 2));
	if (nv == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		nv[i] = argv[i];
		i++;
	}
	nv[n] = NULL;
	nv[n + 1] = NULL;
	return (nv);
}

char	**argv_push(char **argv, const char *s)
{
	size_t		n;
	char		**nv;
	const char	*src;

	n = argv_count(argv);
	nv = argv_alloc_copy(argv, n);
	if (nv == NULL)
		return (NULL);
	src = s;
	if (src == NULL)
		src = "";
	nv[n] = ft_strdup(src);
	if (nv[n] == NULL)
	{
		free(nv);
		return (NULL);
	}
	free(argv);
	return (nv);
}

t_redir	*redir_new(t_redir_type type, const char *target, int quoted)
{
	t_redir		*r;
	const char	*src;

	r = (t_redir *)malloc(sizeof(t_redir));
	if (r == NULL)
		return (NULL);
	src = target;
	if (src == NULL)
		src = "";
	r->type = type;
	r->target = ft_strdup(src);
	if (r->target == NULL)
	{
		free(r);
		return (NULL);
	}
	r->heredoc_quoted = quoted;
	r->next = NULL;
	return (r);
}