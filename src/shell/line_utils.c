
#include "minishell.h"
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

static void	process_one_subline(char *line, size_t start, size_t end,
		char ***envp, int *exit_status)
{
	char	*one;

	one = ft_substr(line, start, end - start);
	if (!one)
		return ;
	if (one[0] != '\0')
	{
		trim_cr(one);
		add_history(one);
		process_line(one, envp, exit_status);
	}
	free(one);
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

void	process_pasted_lines(char *line, char ***envp, int *exit_status)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	replace_cr_with_nl(line);
	while (1)
	{
		i = next_break_pos(line, start);
		process_one_subline(line, start, i, envp, exit_status);
		if (line[i] == '\0')
			break ;
		start = i + 1;
	}
}
