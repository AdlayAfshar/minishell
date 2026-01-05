
#include "minishell.h"
#include <readline/readline.h>

extern int	rl_catch_signals;
extern int	rl_catch_sigwinch;

// static void	trim_cr(char *s)
// {
// 	size_t	n;

// 	if (!s)
// 		return ;
// 	n = ft_strlen(s);
// 	if (n > 0 && s[n - 1] == '\r')
// 		s[n - 1] = '\0';
// }

// static t_cmd	*lex_parse_line(char *line)
// {
// 	t_token	*ts;
// 	t_cmd	*cmds;

// 	ts = lex_line(line);
// 	if (!ts)
// 		return (NULL);
// 	cmds = parse_tokens(ts);
// 	token_list_clear(&ts);
// 	return (cmds);
// }

// static int	expand_cmds(t_cmd *cmds, char **envp, int exit_status)
// {
// 	if (expand_all(cmds, envp, exit_status))
// 	{
// 		free_cmds(cmds);
// 		return (1);
// 	}
// 	return (0);
// }

// static int	run_heredocs(t_cmd *cmds, char **envp, int *exit_status)
// {
// 	int	hd;

// 	hd = setup_heredocs(cmds, envp, exit_status);
// 	if (hd != 0)
// 	{
// 		free_cmds(cmds);
// 		return (1);
// 	}
// 	return (0);
// }

// static void	exec_cmds(t_cmd *cmds, char ***envp, int *exit_status)
// {
// 	t_execctx	x;

// 	x.envp = envp;
// 	x.last_status = exit_status;
// 	*exit_status = exec_pipeline(cmds, &x);
// 	free_cmds(cmds);
// }

// static int	process_line(char *line, char ***envp, int *exit_status)
// {
// 	t_cmd	*cmds;

// 	cmds = lex_parse_line(line);
// 	if (!cmds)
// 		return (0);
// 	if (expand_cmds(cmds, *envp, *exit_status))
// 		return (0);
// 	if (run_heredocs(cmds, *envp, exit_status))
// 		return (0);
// 	exec_cmds(cmds, envp, exit_status);
// 	return (0);
// }

// static size_t	next_break_pos(char *line, size_t i)
// {
// 	while (line[i] && line[i] != '\n' && line[i] != '\r')
// 		i++;
// 	return (i);
// }

// static void	process_one_subline(char *line, size_t start, size_t end,
// 		char ***envp, int *exit_status)
// {
// 	char	*one;

// 	one = ft_substr(line, start, end - start);
// 	if (!one)
// 		return ;
// 	if (one[0] != '\0')
// 	{
// 		trim_cr(one);
// 		add_history(one);
// 		process_line(one, envp, exit_status);
// 	}
// 	free(one);
// }

// static void	replace_cr_with_nl(char *line)
// {
// 	size_t	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\r')
// 			line[i] = '\n';
// 		i++;
// 	}
// }

// static void	process_pasted_lines(char *line, char ***envp, int *exit_status)
// {
// 	size_t	i;
// 	size_t	start;

// 	i = 0;
// 	start = 0;
// 	replace_cr_with_nl(line);
// 	while (1)
// 	{
// 		i = next_break_pos(line, start);
// 		process_one_subline(line, start, i, envp, exit_status);
// 		if (line[i] == '\0')
// 			break ;
// 		start = i + 1;
// 	}
// }

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

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		trim_cr(line);
		process_pasted_lines(line, envp, exit_status);
		free(line);
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