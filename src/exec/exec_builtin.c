
#include "minishell.h"

static int	is_str(char *s, const char *ref)
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

int	is_builtin_name(char *name)
{
	if (!name)
		return (0);
	if (is_str(name, "echo"))
		return (1);
	if (is_str(name, "cd"))
		return (1);
	if (is_str(name, "pwd"))
		return (1);
	if (is_str(name, "env"))
		return (1);
	if (is_str(name, "export"))
		return (1);
	if (is_str(name, "unset"))
		return (1);
	if (is_str(name, "exit"))
		return (1);
	return (0);
}

static int	run_builtin_cmd(t_cmd *cmd, char ***envp)
{
	char	**av;

	av = cmd->argv;
	if (!av || !av[0])
		return (0);
	if (is_str(av[0], "echo"))
		return (builtin_echo(av));
	if (is_str(av[0], "cd"))
		return (builtin_cd(av, envp));
	if (is_str(av[0], "pwd"))
		return (builtin_pwd(av));
	if (is_str(av[0], "env"))
		return (builtin_env(av, *envp));
	if (is_str(av[0], "export"))
		return (builtin_export(av, envp));
	if (is_str(av[0], "unset"))
		return (builtin_unset(av, envp));
	if (is_str(av[0], "exit"))
		return (builtin_exit(av));
	return (0);
}

static int	dup_stdio(int saved[2])
{
	saved[0] = dup(STDIN_FILENO);
	if (saved[0] < 0)
		return (-1);
	saved[1] = dup(STDOUT_FILENO);
	if (saved[1] < 0)
	{
		close(saved[0]);
		return (-1);
	}
	return (0);
}

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	int	saved[2];
	int	status;

	if (dup_stdio(saved) < 0)
		return (1);
	if (apply_redirs(cmd->redirs) < 0)
	{
		dup2(saved[0], STDIN_FILENO);
		dup2(saved[1], STDOUT_FILENO);
		close(saved[0]);
		close(saved[1]);
		return (1);
	}
	status = run_builtin_cmd(cmd, envp);
	dup2(saved[0], STDIN_FILENO);
	dup2(saved[1], STDOUT_FILENO);
	close(saved[0]);
	close(saved[1]);
	return (status);
}
