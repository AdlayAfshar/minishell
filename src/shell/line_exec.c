
#include "minishell.h"

// static const char	*tokens_type_str(t_tok_type type)
// {
// 	if (type == TOK_WORD)
// 		return ("WORD    ,");
// 	if (type == TOK_PIPE)
// 		return ("PIPE    ,");
// 	if (type == TOK_SEMI)
// 		return ("SEMI    ,");
// 	if (type == TOK_REDIR_IN)
// 		return ("RE_IN   ,");
// 	if (type == TOK_REDIR_OUT)
// 		return ("RE_OUT  ,");
// 	if (type == TOK_HEREDOC)
// 		return ("HEREDOC ,");
// 	if (type == TOK_APPEND)
// 		return ("APPEND  ,");
// 	return ("UNKNOWN");
// }

// static void	print_tokens(t_token	*cur)
// {
// 	t_token	*ts;
// 	// int		i;

// 	ts = cur;
// 	// i = 0;

// 	printf("========== tokens ==========\n");
// 	while (ts)
// 	{
// 		printf("type: %s", tokens_type_str(ts->type));
// 		// printf("type: %d", ts->type);
// 		if (ts->val)
// 			printf(" val: %s", ts->val);
// 		else
// 			printf(" val: -");
// 		printf("\n");
// 		ts = ts->next;
// 	}
// }

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

// static void	print_cmds(t_cmd *cmds)
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

// static t_cmd	*lex_parse_line(char *line)
// {
// 	t_token	*ts;
// 	t_cmd	*cmds;

// 	ts = lex_line(line);
// 	if (!ts)
// 		return (NULL);
// 	cmds = parse_tokens(ts);

// 	printf("\n");
// 	printf("----------------------------\n");
// 	print_tokens(ts);
// 	printf("\n");
// 	printf("----------------------------\n");
// 	printf("CMD: %s\n", line);
// 	print_cmds(cmds);
// 	token_list_clear(&ts);
// 	return (cmds);
// }

static t_cmd	*lex_parse_line(char *line)
{
	t_token	*ts;
	t_cmd	*cmds;

	ts = lex_line(line);
	if (!ts)
		return (NULL);
	cmds = parse_tokens(ts);
	token_list_clear(&ts);
	return (cmds);
}

static int	expand_cmds(t_cmd *cmds, char **envp, int exit_status)
{
	if (expand_all(cmds, envp, exit_status))
	{
		// free_cmds(cmds); // maybe error: double free 1
		return (1);
	}
	return (0);
}

// for porablem: 2 ==> process_line + file => hd_process.c  => func:hd_apply_status
static int	run_heredocs(t_cmd *cmds, char **envp, int *exit_status)
{
	int	hd;

	hd = setup_heredocs(cmds, envp, exit_status);
	if (hd == 2)
		return (2);
	if (hd != 0)
	{
		if (exit_status)
			*exit_status = 1;
		return (1);
	}
	return (0);
}
// for porablem: 2 

// static int	run_heredocs(t_cmd *cmds, char **envp, int *exit_status)
// {
// 	int	hd;

// 	hd = setup_heredocs(cmds, envp, exit_status);
// 	if (hd != 0)
// 	{
// 		free_cmds(cmds); // maybe error: double free 2
// 		return (1);
// 	}
// 	return (0);
// }

static void	exec_cmds(t_cmd *cmds, char ***envp, int *exit_status)
{
	t_execctx	x;

	x.envp = envp;
	x.last_status = exit_status;
	*exit_status = exec_pipeline(cmds, &x);
	free_cmds(cmds);
}

// for porablem: 2 ==> run_heredocs + file => hd_process.c  => func:hd_apply_status

int	process_line(char *line, char ***envp, int *exit_status)
{
	t_cmd	*cmds;
	int		st;

	cmds = lex_parse_line(line);
	if (!cmds)
		return (0);
	if (expand_cmds(cmds, *envp, *exit_status))
	{
		free_cmds(cmds);
		return (1);
	}
	st = run_heredocs(cmds, *envp, exit_status);
	if (st != 0)
	{
		free_cmds(cmds);
		if (st == 2)
			return (*exit_status);
		return (1);
	}
	exec_cmds(cmds, envp, exit_status);
	st = *exit_status;
	return (st);
}

// or
// int	process_line(char *line, char ***envp, int *exit_status)
// {
// 	t_cmd	*cmds;
// 	int		st;

// 	cmds = lex_parse_line(line);
// 	if (!cmds)
// 		return (0);

// 	if (expand_cmds(cmds, *envp, *exit_status))
// 	{
// 		free_cmds(cmds);
// 		if (exit_status)
// 			*exit_status = 1;
// 		return (1);
// 	}

// 	st = run_heredocs(cmds, *envp, exit_status);
// 	if (st != 0)
// 	{
// 		free_cmds(cmds);
// 		if (st == 2)
// 			return (*exit_status);
// 		if (exit_status)
// 			*exit_status = 1;
// 		return (1);
// 	}

// 	exec_cmds(cmds, envp, exit_status);
// 	free_cmds(cmds);
// 	return (*exit_status);
// }

// for porablem: 2

// int	process_line(char *line, char ***envp, int *exit_status)
// {
// 	t_cmd	*cmds;
// 	int		st;

// 	cmds = lex_parse_line(line);
// 	if (!cmds)
// 		return (0);
// 	if (expand_cmds(cmds, *envp, *exit_status))
// 	{
// 		free_cmds(cmds); // maybe error: double free 1
// 		return (1);
// 	}
// 	if (run_heredocs(cmds, *envp, exit_status))
// 	{
// 		free_cmds(cmds); // maybe error: double free 2
// 		return (1);
// 	}
// 	exec_cmds(cmds, envp, exit_status);
// 	st = *exit_status;
// 	return (st);
// }
