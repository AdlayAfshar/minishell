
#include "minishell.h"
#include "shell.h"
#include <readline/history.h>

void	trim_cr(char *s)
{
	size_t	n;

	if (!s)
		return ;
	n = ft_strlen(s);
	if (n > 0 && s[n - 1] == '\r')
		s[n - 1] = '\0';
}

static size_t	next_break_pos(char *line, size_t i)
{
	while (line[i] && line[i] != '\n' && line[i] != '\r')
		i++;
	return (i);
}

static int	process_one_subline(char *line, size_t start, size_t end,
		t_line_ctx *ctx)
{
	char	*one;
	int		st;

	one = ft_substr(line, start, end - start);
	if (!one)
		return (0);
	st = 0;
	if (one[0] != '\0')
	{
		trim_cr(one);
		add_history(one);
		st = process_line(one, ctx->envp, ctx->exit_status);
	}
	free(one);
	return (st);
}

static void	replace_cr_with_nl(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\r')
			line[i] = '\n';
		i++;
	}
}

int	process_pasted_lines(char *line, char ***envp, int *exit_status)
{
	size_t		i;
	size_t		start;
	int			st;
	t_line_ctx	ctx;

	ctx.envp = envp;
	ctx.exit_status = exit_status;
	i = 0;
	start = 0;
	replace_cr_with_nl(line);
	while (1)
	{
		i = next_break_pos(line, start);
		st = process_one_subline(line, start, i, &ctx);
		if (st >= EXIT_REQ_BASE)
			return (st);
		if (line[i] == '\0')
			break ;
		start = i + 1;
	}
	return (0);
}
