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

static int	run_single_builtin(t_cmd *cmd, t_execctx *x)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (!is_builtin_name(cmd->argv[0]))
		return (-1);
	return (exec_builtin(cmd, x));
}

int	exec_pipeline(t_cmd *cmd, t_execctx *x)
{
	int	cmd_count;
	int	status;

	if (!cmd)
		return (0);
	// write(2, "EXEC_PIPELINE1\n", 14);
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
	// new
	ms_set_termios(1);
	set_sig_parent_exec();
	status = spawn_cmds(cmd, *(x->envp), *(x->last_status));
	// new
	set_sig_interactive();
	ms_set_termios(0);
	*(x->last_status) = status;
	// write(2, "EXEC_PIPELINE2\n", 14);
	return (status);
}