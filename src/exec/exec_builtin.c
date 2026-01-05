
#include "minishell.h"

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

static int	run_builtin_cmd(t_cmd *cmd, t_execctx *x)
{
	char	**av;

	av = cmd->argv;
	if (!av || !av[0])
		return (0);
	if (is_str(av[0], "echo"))
		return (builtin_echo(av));
	if (is_str(av[0], "cd"))
		return (builtin_cd(av, x->envp));
	if (is_str(av[0], "pwd"))
		return (builtin_pwd(av));
	if (is_str(av[0], "env"))
		return (builtin_env(av, *(x->envp)));
	if (is_str(av[0], "export"))
		return (builtin_export(av, x->envp));
	if (is_str(av[0], "unset"))
		return (builtin_unset(av, x->envp));
	if (is_str(av[0], "exit"))
		return (builtin_exit(av, *(x->last_status)));
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

static void	restore_stdio(int saved[2])
{
	dup2(saved[0], STDIN_FILENO);
	dup2(saved[1], STDOUT_FILENO);
	close(saved[0]);
	close(saved[1]);
}

int	exec_builtin(t_cmd *cmd, t_execctx *x)
{
	int	saved[2];
	int	status;
	int	code;

	if (dup_stdio(saved) < 0)
		return (1);
	if (apply_redirs(cmd->redirs) < 0)
	{
		restore_stdio(saved);
		return (1);
	}
	status = run_builtin_cmd(cmd, x);
	if (status >= EXIT_REQ_BASE)
	{
		code = status - EXIT_REQ_BASE;
		restore_stdio(saved);
		exit(code);
	}
	restore_stdio(saved);
	return (status);
}
