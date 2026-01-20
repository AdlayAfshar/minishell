
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

static int	process_one_subline(t_shell_ctx *ctx, size_t start, size_t end)
{
	char	*line;
	int		st;

	line = ft_substr(ctx->line, start, end - start);
	if (!line)
		return (0);
	st = 0;
	if (line[0] != '\0')
	{
		trim_cr(line);
		add_history(line);
		st = process_line(ctx);
	}
	free(line);
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

int	process_pasted_lines(t_shell_ctx *ctx)
{
	size_t	i;
	size_t	start;
	int		st;

	i = 0;
	start = 0;
	replace_cr_with_nl(ctx->line);
	while (1)
	{
		i = next_break_pos(ctx->line, start);
		st = process_one_subline(ctx, start, i);
		if (st >= EXIT_REQ_BASE)
			return (st);
		else
			ctx->exit_status = st;
		if (ctx->line[i] == '\0')
			break ;
		start = i + 1;
	}
	return (0);
}
