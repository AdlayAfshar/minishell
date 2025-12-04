
#include "../include/minishell.h"

extern volatile int g_signal;
//---------------------------------execve----------------------------------

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*ts;
	t_cmd	*pl;

	(void)argc;
	(void)argv;
	handle_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if(g_signal == SIGINT)
		{
			g_signal = 0;
			rl_done = 0;
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			free(input);
			continue ;
		}
		/* ✔ El handler no llama a funciones no–async-safe → solo pone g_signal = sig
✔ Utilizas rl_done = 1 para forzar que readline() termine → comportamiento limpio
✔ En el bucle principal procesas la señal correctamente
✔ No violas la regla del subject (solo 1 global y no usas estructuras globales)*/
		if (*input)
			add_history(input);
		ts = lex_line(input);
		if (!ts)
			fprintf(stderr, "lexer error\n");
		else
		{
			pl = parse_tokens(ts);
			if (pl)
			{
				exec_pipeline(pl, envp);
				free_cmds(pl);
			}
			free_tokens(ts);
		}
		free(input);
	}
	return (0);
}
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
// 			free_tokens(ts);
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
// 		free_tokens(ts);
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
