
#include "minishell.h"
#include <readline/readline.h>
#include "signals.h"

static void	shell_init(char **envp_in, char ***envp, int *exit_status)
{
	*exit_status = 0;
	*envp = dup_env(envp_in);
	ms_set_termios(0);
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	set_sig_interactive();
}

static int	shell_loop(char ***envp, int *exit_status)
{
	char	*line;
	int		st;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		trim_cr(line);
		st = process_pasted_lines(line, envp, exit_status);
		free(line);
		if (st >= EXIT_REQ_BASE)
		{
			*exit_status = (st - EXIT_REQ_BASE) & 255;
			break ;
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **envp_in)
{
	char	**envp;
	int		exit_status;

	(void)argc;
	(void)argv;
	shell_init(envp_in, &envp, &exit_status);
	if (!envp)
		return (1);
	shell_loop(&envp, &exit_status);
	free_env(envp);
	return (exit_status);
}
