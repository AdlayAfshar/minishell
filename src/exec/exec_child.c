
#include "minishell.h"

static int	exec_child_builtin(t_cmd *cmd, t_execctx *x)
{
	char	**av;
	char	*n;

	av = cmd->argv;
	if (!av || !av[0])
		return (-1);
	n = av[0];
	if (is_name(n, "echo"))
		return (builtin_echo(av));
	if (is_name(n, "env"))
		return (builtin_env(av, *(x->envp)));
	if (is_name(n, "export"))
		return (builtin_export(av, x->envp));
	if (is_name(n, "unset"))
		return (builtin_unset(av, x->envp));
	if (is_name(n, "cd"))
		return (builtin_cd(av, x->envp));
	if (is_name(n, "pwd"))
		return (builtin_pwd(av));
	if (is_name(n, "exit"))
		return (builtin_exit(av, *(x->last_status)));
	return (-1);
}

static void	setup_child_fds(int in_fd, int out_fd)
{
	if (in_fd != -1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

static void	exec_with_sh(char *path, char **envp)
{
	char	*av[3];

	av[0] = "/bin/sh";
	av[1] = path;
	av[2] = NULL;
	execve("/bin/sh", av, envp);
}

static void	exec_external(t_cmd *cmd, char **envp)
{
	char	*path;
	int		e;

	path = find_in_path(cmd->argv[0], envp);
	if (!path)
	{
		write(2, "minishell: command not found\n", 29);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	e = errno;
	if (e == ENOEXEC)
		exec_with_sh(path, envp);
	perror(path);
	free(path);
	if (e == ENOENT)
		exit(127);
	if (e == EACCES || e == EISDIR)
		exit(126);
	exit(126);
}

void	exec_cmd_child(t_cmd *cmd, int in_fd, int out_fd, t_execctx *x)
{
	int	status;

	set_sig_child_default();
	setup_child_fds(in_fd, out_fd);
	if (apply_redirs(cmd->redirs) < 0)
		exit(1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	status = exec_child_builtin(cmd, x);
	if (status != -1)
	{
		if (status >= EXIT_REQ_BASE)
			status -= EXIT_REQ_BASE;
		exit(status & 255);
	}
		// hh
// 	int i = 0;
// while (cmd->argv && cmd->argv[i])
// {
//     fprintf(stderr, "argv[%d]=[%s]\n", i, cmd->argv[i]);
//     i++;
// }
// end
	exec_external(cmd, *(x->envp));
}
