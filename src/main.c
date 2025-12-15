

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int g_exit_status = 0;

static void	trim_cr(char *s)
{
	size_t	n;

	if (!s)
		return ;
	n = ft_strlen(s);
	if (n > 0 && s[n - 1] == '\r')
		s[n - 1] = '\0';
}

/* تنظیم شل در حالت عادی */
static void init_interactive_signals(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/* مدیریت خط ورودی */
static int process_line(char *line, char ***envp)
{
	t_token *ts;
	t_cmd   *cmds;
	int     hd;

	ts = lex_line(line);
	if (!ts)
		return (0);
	cmds = parse_tokens(ts);
	token_list_clear(&ts);
	if (!cmds)
		return (0);
	if (expand_all(cmds, *envp, g_exit_status))
	{
		free_cmds(cmds);
		return (0);
	}
	hd = setup_heredocs(cmds, *envp, g_exit_status);
	if (hd != 0)
	{
		free_cmds(cmds);
		return (0);
	}
	g_exit_status = exec_pipeline(cmds, envp);
	free_cmds(cmds);
	return (0);
}

static void	process_pasted_lines(char *line, char ***envp)
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
				process_line(one, envp);
			}
			free(one);
			if (line[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
}

int main(int argc, char **argv, char **envp_in)
{
	char	*line;
	char	**envp;

	(void)argc;
	(void)argv;
	envp = dup_env(envp_in);
// 	write(2, "envp_in count = ", 16);
// ft_putnbr_fd(env_count(envp_in), 2);
// write(2, "\n", 1);

// envp = dup_env(envp_in);

// write(2, "envp dup count = ", 17);
// ft_putnbr_fd(env_count(envp), 2);
// write(2, "\n", 1);
/////
	ms_set_termios();
	init_interactive_signals();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		trim_cr(line);
		// if (line[0] != '\0')
		// 	add_history(line);
		// process_line(line, &envp);
		process_pasted_lines(line, &envp);

// 		ft_putnbr_fd(env_count(envp), 2);
// write(2, "  <- before\n", 12);

// process_pasted_lines(line, &envp);

// ft_putnbr_fd(env_count(envp), 2);
// write(2, "  <- after\n", 11);
///
		free(line);
	}
	free_env(envp);
	return (g_exit_status);
}
