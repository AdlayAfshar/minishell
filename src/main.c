

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
extern int	rl_catch_signals;
extern int	rl_catch_sigwinch;

volatile sig_atomic_t	g_sig = 0;
static void	trim_cr(char *s)
{
	size_t	n;

	if (!s)
		return ;
	n = ft_strlen(s);
	if (n > 0 && s[n - 1] == '\r')
		s[n - 1] = '\0';
}

// static const char	*redir_type_str(t_redir_type type)
// {
// 	if (type == R_IN)
// 		return ("<");
// 	if (type == R_OUT)
// 		return (">");
// 	if (type == R_APPEND)
// 		return (">>");
// 	if (type == R_HEREDOC)
// 		return ("<<");
// 	return ("UNKNOWN");
// }

// static void	print_argv(char **argv)
// {
// 	int	i;

// 	if (!argv)
// 	{
// 		printf("argv: NULL\n");
// 		return ;
// 	}
// 	i = 0;
// 	while (argv[i])
// 	{
// 		printf("  argv[%d]: \"%s\"\n", i, argv[i]);
// 		i++;
// 	}
// }

// static void	print_redirs(t_redir *r)
// {
// 	int	i;

// 	if (!r)
// 	{
// 		printf("  redirs: NULL\n");
// 		return ;
// 	}
// 	i = 0;
// 	while (r)
// 	{
// 		printf("  redir[%d]: type= %s, target=\"%s\", heredoc_quoted=%d\n",
// 			i,
// 			redir_type_str(r->type),
// 			r->target ? r->target : "(null)",
// 			r->heredoc_quoted);
// 		r = r->next;
// 		i++;
// 	}
// }

// void	print_cmds(t_cmd *cmds)
// {
// 	t_cmd	*cur;
// 	int		i;

// 	cur = cmds;
// 	i = 0;
// 	while (cur)
// 	{
// 		printf("========== CMD %d ==========\n", i);
// 		print_argv(cur->argv);
// 		print_redirs(cur->redirs);
// 		printf("next: %s\n", cur->next ? "YES" : "NO");
// 		printf("\n");
// 		cur = cur->next;
// 		i++;
// 	}
// }

// static int	process_line(char *line, char ***envp, int *exit_status)
// {
// 	t_token		*ts;
// 	t_cmd		*cmds;
// 	int			hd;
// 	t_execctx	x;

// 	ts = lex_line(line); // تبدیل متن به توکن‌ها 
// 	if (!ts)
// 		return (0);
// 	cmds = parse_tokens(ts); // ساختن ساختار فرمان‌ها
// 	while (ts)
// 	{
// 		printf("type: %d", ts->type);
// 		if (ts->val)
// 			printf(", val: %s", ts->val);
// 		else
// 			printf(", val: NULL");
// 		printf("\n");
// 		ts = ts->next;
// 	}
// 	printf("\n");
// 	printf("----------------------------\n");
// 	printf("CMD: %s\n", line);
// 	print_cmds(cmds);
// 	token_list_clear(&ts); // آزادسازی توکن‌ها (دیگه لازم نیست)
// 	if (!cmds)
// 		return (0);
// 	if (expand_all(cmds, *envp, *exit_status))
// 	{
// 		free_cmds(cmds);
// 		return (0);
// 	}
// 	hd = setup_heredocs(cmds, *envp, exit_status);
// 	if (hd != 0)
// 	{
// 		free_cmds(cmds);
// 		return (0);
// 	}
// 	x.envp = envp;
// 	x.last_status = exit_status;
// 	*exit_status = exec_pipeline(cmds, &x);
// 	free_cmds(cmds);
// 	return (0);
// }
	// •	readline → یک string می‌دهد.
	// •	process_pasted_lines → اگر چند خط باشد، split می‌کند و هر خط را می‌فرستد process_line.
	// •	process_line:
	// 1.	lex_line → tokens
	// 2.	parse_tokens → cmds
	// 3.	expand_all → جایگزینی $ و…
	// 4.	setup_heredocs → آماده‌سازی heredocها (احتمالاً با fork/pipe/tempfile)
	// 5.	exec_pipeline → fork/exec/dup2/pipe و اجرای builtinها

	// 	•	process_line
	// 1.	lexer → شکستن متن
	// 2.	parser → ساخت ساختار اجرایی
	// 3.	expand → جایگزینی $VAR و $?
	// 4.	heredoc → آماده‌سازی ورودی‌ها
	// 5.	exec → fork / pipe / exec / builtin
	// 6.	ذخیره‌ی exit status



static int	process_line(char *line, char ***envp, int *exit_status)
{
	t_token		*ts;
	t_cmd		*cmds;
	int			hd;
	t_execctx	x;

	ts = lex_line(line);
	if (!ts)
		return (0);
	cmds = parse_tokens(ts);
	token_list_clear(&ts);
	if (!cmds)
		return (0);
	if (expand_all(cmds, *envp, *exit_status))
	{
		free_cmds(cmds);
		return (0);
	}
	hd = setup_heredocs(cmds, *envp, exit_status);
	if (hd != 0)
	{
		free_cmds(cmds);
		return (0);
	}
	x.envp = envp;
	x.last_status = exit_status;
	*exit_status = exec_pipeline(cmds, &x);
	free_cmds(cmds);
	return (0);
}

static void	process_pasted_lines(char *line, char ***envp, int *exit_status)
{
	size_t	i;
	size_t	start;
	char	*one;

	i = 0;
	start = 0;
	while (1)
	{
		if (line[i] == '\r')
			line[i] = '\n';
		if (line[i] == '\n' || line[i] == '\0')
		{
			one = ft_substr(line, start, i - start);
			if (one && one[0] != '\0')
			{
				trim_cr(one);
				add_history(one);
				process_line(one, envp, exit_status);
			}
			free(one);
			if (line[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp_in)
{
	char	*line;
	char	**envp;
	int		exit_status;

	(void)argc;
	(void)argv;
	exit_status = 0;
	envp = dup_env(envp_in);
	if (!envp)
		return (1);
	ms_set_termios(0);
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	set_sig_interactive();

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		trim_cr(line);
		process_pasted_lines(line, &envp, &exit_status);
		free(line);
	}
	free_env(envp);
	return (exit_status);
}

