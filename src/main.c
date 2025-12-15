

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int g_exit_status = 0;

/* چاپ پرامپت جدید بعد از Ctrl-C */
// void sigint_handler(int sig)
// {
// 	(void)sig;
// 	g_exit_status = 130;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

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
		if (line[0] != '\0')
			add_history(line);
		// process_line(line, &envp);
		process_pasted_lines(line, &envp);
		free(line);
	}
	free_env(envp);
	return (g_exit_status);
}

////////////////
// #include "minishell.h"

// int	g_exit_status = 0;

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_token	*ts;
// 	t_cmd	*pl;
// 	char	**env;
// 	int		status;

// 	(void)argc;
// 	(void)argv;
// 	handle_signals();
// 	env = dup_env(envp);
// 	if (!env)
// 	{
// 		perror("minishell: dup_env");
// 		return (1);
// 	}
// 	pl = NULL;
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*input)
// 			add_history(input);
// 		ts = lex_line(input);
// 		if (!ts)
// 		{
// 			fprintf(stderr, "minishell: lexer error\n");
// 			free(input);
// 			continue ;
// 		}
// 		pl = parse_tokens(ts);
// 		token_list_clear(&ts);
// 		if (!pl)
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		if (expand_all(pl, env, g_exit_status))
// 		{
// 			free_cmds(pl);
// 			free(input);
// 			continue ;
// 		}
// 		if (setup_heredocs(pl, env, g_exit_status))
// 		{
// 			free_cmds(pl);
// 			free(input);
// 			continue ;
// 		}
// 		status = exec_pipeline(pl, &env);
// 		g_exit_status = status;
// 		free_cmds(pl);
// 		free(input);
// 	}
// 	/* اینجا اگر خواستی env رو هم free کن */
// 	return (0);
// }

///////////////////////
// extern char	**environ;

// int main(int argc, char **argv, char **envp)
// {
//     char    *input;
//     t_token *ts;
//     t_cmd   *pl = NULL;   // 🔴 init fix
//     char    **env;

//     (void)argc;
//     (void)argv;
//     handle_signals();

//     env = envp;

//     while (1)
//     {
//         input = readline("minishell> ");
//         if (!input)
//         {
//             printf("exit\n");
//             break;
//         }

//         if (*input)
//             add_history(input);

//         ts = lex_line(input);

//         if (!ts)
//             fprintf(stderr, "lexer error\n");
//         else
//         {
//             pl = parse_tokens(ts);
//             if (pl)
//             {
//                 exec_pipeline(pl, &env);
//                 free_cmds(pl);
//             }
//             token_list_clear(&ts);
//         }

//         free(input);
//     }

//     return 0;
// }

// int main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_token	*ts;
// 	// t_cmd	*pl;
// 	t_cmd   *pl = NULL; 
// 	char	**env;
// 	int		status;

// 	(void)argc;
//     (void)argv;
// 	handle_signals();

// 	// فعلاً همون envp سیستم رو استفاده می‌کنیم.
// 	// اگر بعداً تابع dup_env نوشتی، می‌تونی این‌جا کپی‌اش کنی:
// 	// env = dup_env(envp);
// 	env = dup_env(envp);
// 	if (!env)
//     {
//         perror("minishell: dup_env");
//         return (1);
//     }

// 	status = exec_pipeline(pl, &env);
// 	(void)status;
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*input)
// 			add_history(input);
// 		ts = lex_line(input);
// 		// if (!ts)
// 		// 	fprintf(stderr, "lexer error\n");
// 		if (!ts)
// 		{
// 			fprintf(stderr, "minishell: lexer error\n");
// 			free(input);
// 			continue;
// 		}
// 		pl = parse_tokens(ts);
// 		token_list_clear(&ts);
// 		if (!pl)
// 		{
// 			free(input);
// 			continue;
// 		}
// 		if (expand_all(pl, envp, g_exit_status))
// 		{
// 			free_cmds(pl);
// 			free(input);
// 			continue;
// 		}

// 		if (setup_heredocs(pl, envp, g_exit_status))
// 		{
// 			free_cmds(pl);
// 			free(input);
// 			continue;
// 		}
// 		// if (expand_all(pl, envp, g_exit_status) != 0)
// 		// {
// 		// 	fprintf(stderr, "minishell: expand: malloc error\n");
// 		// 	free_cmds(pl);
// 		// 	free(input);
// 		// 	continue;
// 		// }
// 		status = exec_pipeline(pl, &envp);
// 		g_exit_status = status;
// 		free_cmds(pl);
// 		// else
// 		// {
// 		// 	pl = parse_tokens(ts);
// 		// 	if (pl)
// 		// 	{
// 		// 		// ⚠️ این‌جا فرق اصلی با نسخه‌ی قبلی‌ته:
// 		// 		// قبلاً: exec_pipeline(pl, envp);
// 		// 		// الان:  exec_pipeline(pl, &env);
// 		// 		exec_pipeline(pl, &env);
// 		// 		free_cmds(pl);
// 		// 	}
// 		// 	token_list_clear(&ts);
// 		// }
// 		free(input);
// 	}
// 	// اگر env رو کپی کرده بودی (dup_env)، این‌جا free_env(env) صدا می‌زدی.
// 	return (0);
// }
////////////////////
// int	g_exit_status = 0;

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_token	*ts;
// 	t_cmd	*pl;
// 	char	**env;

// 	(void)argc;
// 	(void)argv;
// 	handle_signals();

// 	// فعلاً همون envp سیستم رو استفاده می‌کنیم.
// 	// اگر بعداً تابع dup_env نوشتی، می‌تونی این‌جا کپی‌اش کنی:
// 	// env = dup_env(envp);
// 	env = envp;

// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*input)
// 			add_history(input);
// 		ts = lex_line(input);
// 		if (!ts)
// 			fprintf(stderr, "lexer error\n");
// 		else
// 		{
// 			pl = parse_tokens(ts);
// 			if (pl)
// 			{
// 				// ⚠️ این‌جا فرق اصلی با نسخه‌ی قبلی‌ته:
// 				// قبلاً: exec_pipeline(pl, envp);
// 				// الان:  exec_pipeline(pl, &env);
// 				exec_pipeline(pl, &env);
// 				free_cmds(pl);
// 			}
// 			token_list_clear(&ts);
// 		}
// 		free(input);
// 	}
// 	// اگر env رو کپی کرده بودی (dup_env)، این‌جا free_env(env) صدا می‌زدی.
// 	return (0);
// }

// extern volatile int g_signal;
// extern char	**environ;
// //---------------------------------execve----------------------------------

// int	main(void)
// {
// 	char	*input;
// 	t_token	*ts;
// 	t_cmd	*pl;
// 	int		status;
// 	char	**envp;

// 	envp = environ;
// 	handle_signals();
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if(g_signal == SIGINT)
// 		{
// 			g_signal = 0;
// 			rl_done = 0;
// 			write(1, "\n", 1);
// 			rl_replace_line("", 0);
// 			rl_on_new_line();
// 			rl_redisplay();
// 			free(input);
// 			continue ;
// 		}
// 		/* The handler doesn't call non-async-safe functions → it only sets g_signal = sig
// ✔ You use rl_done = 1 to force readline() to finish → clean behavior
// ✔ In the main loop, you process the signal correctly
// ✔ You don't violate the subject rule (only 1 global and no global structures)*/
// 		if (*input)
// 			add_history(input);
// 		ts = lex_line(input);
// 		// if (!ts)
// 		// 	fprintf(stderr, "lexer error\n");
// 		if (!ts)
// 		{
// 			fprintf(stderr, "minishell: lexer error\n");
// 			free(input);
// 			continue ;
// 		}
// 		pl = parse_tokens(ts);
// 		token_list_clear(&ts);
// 		if (pl)
// 		{
// 			status = exec_pipeline(pl, envp);
// 			/* اینجا می‌تونی status رو برای $? نگه داری */
// 			(void)status;
// 			free_cmds(pl);
// 		}
// 		free(input);
// 	}
// 	return (0);
// }
// // #include "../include/minishell.h"

// //---------------------------------execve----------------------------------

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_token	*ts;
// 	t_cmd	*pl;

// 	(void)argc;
// 	(void)argv;
// 	handle_signals();
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*input)
// 			add_history(input);
// 		ts = lex_line(input);
// 		if (!ts)
// 			fprintf(stderr, "lexer error\n");
// 		else
// 		{
// 			pl = parse_tokens(ts);
// 			if (pl)
// 			{
// 				exec_pipeline(pl, envp);
// 				free_cmds(pl);
// 			}
// 			token_list_clear(&ts);
// 		}
// 		free(input);
// 	}
// 	return (0);
// }
//---------------------------------parsing----------------------------------

// static void	print_cmds(t_cmd *c)
// {
// 	size_t		i;
// 	t_redir		*r;
// 	const char	*t;
// 	const char	*quoted;

// 	while (c)
// 	{
// 		fprintf(stdout, "CMD: ");
// 		if (c->argv)
// 		{
// 			i = 0;
// 			while (c->argv[i])
// 			{
// 				fprintf(stdout, "[%s] ", c->argv[i]);
// 				i++;
// 			}
// 		}
// 		if (c->redirs)
// 		{
// 			r = c->redirs;
// 			while (r)
// 			{
// 				if (r->type == R_IN)
// 					t = "<";
// 				else if (r->type == R_OUT)
// 					t = ">";
// 				else if (r->type == R_APPEND)
// 					t = ">>";
// 				else
// 					t = "<<";
// 				if (r->type == R_HEREDOC)
// 					quoted = " (quoted)";
// 				else
// 					quoted = "";
// 				fprintf(stdout, "{%s %s%s} ", t, r->target, quoted);
// 				r = r->next;
// 			}
// 		}
// 		fprintf(stdout, "\n");
// 		c = c->next;
// 	}
// }

// int	main(void)
// {
// 	char	*input;
// 	t_token	*ts;
// 	t_cmd	*pl;

// 	handle_signals();
// 	while (1)
// 	{

// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*input)
// 			add_history(input);
// 		ts = lex_line(input);
// 		if (!ts)
// 			fprintf(stderr, "minishell: lexer error (unclosed quote?)\n");
// 		else
// 		{
// 			pl = parse_tokens(ts);
// 			if (pl)
// 			{
// 				print_cmds(pl);
// 				free_cmds(pl);
// 			}
// 			token_list_clear(&ts);
// 		}
// 		free(input);
// 	}
// 	return (0);
// }

//---------------------------------lexer----------------------------------
// static const char	*tok_name(int t)
// {
// 	if (t == TOK_WORD)
// 		return ("WORD");
// 	if (t == TOK_PIPE)
// 		return ("PIPE");
// 	if (t == TOK_REDIR_IN)
// 		return ("REDIR_IN");
// 	if (t == TOK_REDIR_OUT)
// 		return ("REDIR_OUT");
// 	if (t == TOK_HEREDOC)
// 		return ("HEREDOC");
// 	if (t == TOK_APPEND)
// 		return ("APPEND");
// 	return ("?");
// }

// int	main(void)
// {
// 	char	*input;
// 	t_token	*ts;
// 	t_token	*cur;

// 	handle_signals();
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*input)
// 			add_history(input);
// 		ts = lex_line(input);
// 		if (!ts)
// 			fprintf(stderr, "minishell: lexer error (unclosed quote?)\n");
		
// 		/*
// 			We assign `cur = ts` because `ts` must always point to the head of the
// 			token list. We traverse the list using `cur` so that we don't lose the
// 			original pointer. If we advanced `ts` directly, we would lose access to
// 			the list and would not be able to free it or reuse it later.
// 		*/
// 		cur = ts;
// 		while (cur)
// 		{
// 			if (cur->val)
// 				printf("[%s:\"%s\"] ", tok_name(cur->type), cur->val);
// 			else
// 				printf("[%s] ", tok_name(cur->type));
// 			cur = cur->next;
// 		}
// 		if (ts)
// 			printf("\n");
// 		token_list_clear(&ts);
// 		free(input);
// 	}
// 	return (0);
// }

// int	main(void)
// {
// 	char	*input;

// 	handle_signals();
// 	while (1)
// 	{
// 		input = readline("yash> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (*input)
// 			add_history(input);
// 		printf("You typed: %s\n", input);
// 		free(input);
// 	}
// 	return (0);
// }

// minishell> echo "hello world"
// 			[WORD:"echo"] [WORD:""hello world""] 
// minishell> echo "hello world" | grep hello >> out.txt
// 			[WORD:"echo"] [WORD:""hello world""] [PIPE] [WORD:"grep"] [WORD:"hello"] [APPEND] [WORD:"out.txt"] 
// minishell> ls -la
// 			[WORD:"ls"] [WORD:"-la"] 
// minishell> echo hi>file
// 			[WORD:"echo"] [WORD:"hi"] [REDIR_OUT] [WORD:"file"] 
// minishell> echo hi
// 			[WORD:"echo"] [WORD:"hi"] 
// minishell> ls -la /usr/bin
// 			[WORD:"ls"] [WORD:"-la"] [WORD:"/usr/bin"] 
// minishell> echo hello | grep h
// 			[WORD:"echo"] [WORD:"hello"] [PIPE] [WORD:"grep"] [WORD:"h"] 
// minishell> echo hi|grep h
// 			[WORD:"echo"] [WORD:"hi"] [PIPE] [WORD:"grep"] [WORD:"h"] 
// minishell> cat < file
// 			[WORD:"cat"] [REDIR_IN] [WORD:"file"] 
// minishell> echo hi >> log.txt
// 			[WORD:"echo"] [WORD:"hi"] [APPEND] [WORD:"log.txt"] 
// minishell> echo hi>file>
// 			[WORD:"echo"] [WORD:"hi"] [REDIR_OUT] [WORD:"file"] [REDIR_OUT]
// minishell> echo "hello world"
// 			[WORD:"echo"] [WORD:""hello world""] 
// minishell> echo "a|b" | grep b
// 			[WORD:"echo"] [WORD:""a|b""] [PIPE] [WORD:"grep"] [WORD:"b"] 
// minishell> cat << EOF
// 			[WORD:"cat"] [HEREDOC] [WORD:"EOF"] 
// minishell> cat < infile | grep foo >> results.txt
// 			[WORD:"cat"] [REDIR_IN] [WORD:"infile"] [PIPE] [WORD:"grep"] [WORD:"foo"] [APPEND] [WORD:"results.txt"] 
// minishell>  
// 			minishell: lexer error (unclosed quote?)
// minishell> | ls
// 			[PIPE] [WORD:"ls"] 
// minishell> cat<<EOF>>out
// 			[WORD:"cat"] [HEREDOC] [WORD:"EOF"] [APPEND] [WORD:"out"] 
// minishell> echo "'hello'"
// 			[WORD:"echo"] [WORD:""'hello'""] 
// minishell> cmd1|cmd2 < in > out
// 			[WORD:"cmd1"] [PIPE] [WORD:"cmd2"] [REDIR_IN] [WORD:"in"] [REDIR_OUT] [WORD:"out"] 