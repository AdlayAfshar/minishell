
#include "exec.h"
#include <stdio.h>

int	is_str(char *s, const char *ref)
{
	int	i;

	if (!s || !ref)
		return (0);
	i = 0;
	while (s[i] && ref[i] && s[i] == ref[i])
		i++;
	if (s[i] == '\0' && ref[i] == '\0')
		return (1);
	return (0);
}

int	is_name(const char *n, const char *s)
{
	int	i;

	i = 0;
	while (n[i] && s[i] && n[i] == s[i])
		i++;
	if (n[i] != '\0' || s[i] != '\0')
		return (0);
	return (1);
}

int	pipe_or_init(t_cmd *cur, int pipe_fd[2], pid_t *pids)
{
	if (cur->next)
	{
		if (pipe(pipe_fd) < 0)
			return (free(pids), perror("pipe"), 1);
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
	return (0);
}

int	fork_or_fail(pid_t *pids, int i)
{
	pids[i] = fork();
	if (pids[i] < 0)
		return (free(pids), perror("fork"), 1);
	return (0);
}