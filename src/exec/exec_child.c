#include "minishell.h"
#include <errno.h>

static int	is_name(const char *n, const char *s)
{
	int	i;

	i = 0;
	while (n[i] && s[i] && n[i] == s[i])
		i++;
	if (n[i] != '\0' || s[i] != '\0')
		return (0);
	return (1);
}

static int	exec_child_builtin(t_cmd *cmd, char ***envp)
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
		return (builtin_env(av, *envp));
	if (is_name(n, "export"))
		return (builtin_export(av, envp));
	if (is_name(n, "exit"))
		return (builtin_exit(av));
	if (is_name(n, "cd"))
		return (builtin_cd(av, envp));
	if (is_name(n, "pwd"))
		return (builtin_pwd(av));
	if (is_name(n, "unset"))
		return (builtin_unset(av, envp));
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

// static void	exec_external(t_cmd *cmd, char **envp)
// {
// 	char	*path;

// 	// path = find_in_path(cmd->argv[0]);
// 	path = find_in_path(cmd->argv[0], envp);
// 	if (!path)
// 	{
// 		write(2, "minishell: command not found\n", 29);
// 		exit(127);
// 	}
// 	execve(path, cmd->argv, envp);
// 	perror(path);
// 	free(path);
// 	exit(126);
// }

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

	path = find_in_path(cmd->argv[0], envp);
	if (!path)
	{
		write(2, "minishell: command not found\n", 29);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	if (errno == ENOEXEC)
		exec_with_sh(path, envp);
	perror(path);
	free(path);
	exit(126);
}

void	exec_cmd_child(t_cmd *cmd, int in_fd, int out_fd, char **envp)
{
	int	status;

	set_sig_child_default();
	setup_child_fds(in_fd, out_fd);
	if (apply_redirs(cmd->redirs) < 0)
		exit(1);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	status = exec_child_builtin(cmd, &envp);
	if (status != -1)
		exit(status);
	exec_external(cmd, envp);
}
