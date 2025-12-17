#include "minishell.h"

int	count_cmds(t_cmd *cmd)
{
	int	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

// static int	run_single_builtin(t_cmd *cmd, char ***envp)
static int	run_single_builtin(t_cmd *cmd, t_execctx *x)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (!is_builtin_name(cmd->argv[0]))
		return (-1);
	// return (exec_builtin(cmd, envp));
	return (exec_builtin(cmd, x));
}

// int	exec_pipeline(t_cmd *cmd, char ***envp)
// int	exec_pipeline(t_cmd *cmd, t_execctx *x)
// {
// 	int	cmd_count;
// 	int	status;

// 	if (!cmd)
// 		return (0);
// 	cmd_count = count_cmds(cmd);
// 	if (cmd_count == 1)
// 	{
// 		status = run_single_builtin(cmd, x);
// 		if (status >= 0)
// 		{
// 			g_exit_status = status;
// 			return (status);
// 		}
// 	}
// 	status = spawn_cmds(cmd, *envp);
// 	g_exit_status = status;
// 	return (status);
// }

// int	exec_pipeline(t_cmd *cmd, t_execctx *x)
// {
// 	int	cmd_count;
// 	int	status;

// 	if (!cmd)
// 		return (0);
// 	cmd_count = count_cmds(cmd);
// 	if (cmd_count == 1)
// 	{
// 		status = run_single_builtin(cmd, x);
// 		if (status >= 0)
// 		{
// 			*(x->last_status) = status;
// 			return (status);
// 		}
// 	}
// 	status = spawn_cmds(cmd, *(x->envp));
// 	*(x->last_status) = status;
// 	return (status);
// }

// bad az dorost shodane: spawn_cmds
int	exec_pipeline(t_cmd *cmd, t_execctx *x)
{
	int	cmd_count;
	int	status;

	if (!cmd)
		return (0);
	cmd_count = count_cmds(cmd);
	if (cmd_count == 1)
	{
		status = run_single_builtin(cmd, x);
		if (status >= 0)
		{
			*(x->last_status) = status;
			return (status);
		}
	}
	status = spawn_cmds(cmd, *(x->envp), *(x->last_status));
	*(x->last_status) = status;
	return (status);
}