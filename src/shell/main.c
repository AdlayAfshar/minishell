
#include "minishell.h"
#include "signals.h"
#include <readline/readline.h>

static void	shell_init(char **envp_in, t_shell_ctx *ctx)
{
	ctx->exit_status = 0;
	ctx->prev_fd = -1;
	ctx->pids = NULL;
	ctx->envp = dup_env(envp_in);
	tcgetattr(STDIN_FILENO, &ctx->term_orig);
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
			st = EXIT_REQ_BASE + (ctx->exit_status & 255);
			break ;
		}
		// trim_cr(ctx->line);
		st = process_pasted_lines(ctx);
		free(ctx->line);
		if (st >= EXIT_REQ_BASE)
		{
			write(1, "exit\n", 5);
			ctx->exit_status = (st - EXIT_REQ_BASE) & 255;
			break ;
		}
	}
	return (0);
}

void	exit_and_clear_ctx(int exit_code, t_shell_ctx *ctx)
{
	free_ctx(ctx);
	exit(exit_code);
}

void	free_ctx(t_shell_ctx *ctx)
{
	// write(2, "free_ctx called\n", 16);

	free_env(ctx->envp);
	ctx->envp = NULL;
	free_cmds(ctx->cmds);
	// free(ctx->line);
	if (ctx->current_subline)
		free(ctx->current_subline);
	if (ctx->pids)
		free(ctx->pids);
}

int	main(int argc, char **argv, char **envp_in)
{
	t_shell_ctx	ctx;

	(void)argc;
	(void)argv;
	ft_bzero(&ctx, sizeof(ctx));
	shell_init(envp_in, &ctx);
	shell_loop(&ctx);
	free_ctx(&ctx);
	return (ctx.exit_status);
}
