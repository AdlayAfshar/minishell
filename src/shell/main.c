
#include "minishell.h"
#include "signals.h"
#include <readline/readline.h>

static void	shell_init(char **envp_in, t_shell_ctx *ctx)
{
	ctx->exit_status = 0;
	ctx->envp = dup_env(envp_in);
	ms_set_termios(0);
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	set_sig_interactive();
}

static int	shell_loop(t_shell_ctx *ctx)
{
	int	st;

	while (1)
	{
		ctx->line = readline("minishell> ");
		if (!ctx->line)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		trim_cr(ctx->line);
		st = process_pasted_lines(ctx);
		free(ctx->line);
		if (st >= EXIT_REQ_BASE)
		{
			ctx->exit_status = (st - EXIT_REQ_BASE) & 255;
			break ;
		}
	}
	return (0);
}

void	free_ctx(t_shell_ctx *ctx)
{
	free_env(ctx->envp);
}

int	main(int argc, char **argv, char **envp_in)
{
	t_shell_ctx	ctx;

	(void)argc;
	(void)argv;
	shell_init(envp_in, &ctx);
	shell_loop(&ctx);
	free_ctx(&ctx);
	return (ctx.exit_status);
}
