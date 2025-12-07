
#include "../include/minishell.h"

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
			token_list_clear(&ts);
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