
#include "minishell.h"

static int	parse_pipe(t_token **ts, t_cmd **cur, t_cmd **pipe)
{
	if (cur == NULL || *cur == NULL)
		return (syntax_err("|", pipe));
	if ((*cur)->argv == NULL && (*cur)->redirs == NULL)
		return (syntax_err("|", pipe));
	if (ts == NULL || *ts == NULL || (*ts)->next == NULL)
		return (syntax_err("|", pipe));
	if ((*ts)->next->type == TOK_PIPE)
		return (syntax_err("|", pipe));
	*cur = cmd_new();
	if (*cur == NULL)
	{
		free_cmds(*pipe);
		return (1);
	}
	cmd_push(pipe, *cur);
	*ts = (*ts)->next;
	return (0);
}

static int	parse_redir(t_token **ts, t_cmd *cur, t_cmd **pipe)
{
	t_redir_type	rt;
	t_redir			*r;
	int				quoted;

	if (ts == NULL || *ts == NULL)
		return (0);
	if (!tok_to_redir((*ts)->type, &rt))
		return (0);
	if ((*ts)->next == NULL || (*ts)->next->type != TOK_WORD)
		return (syntax_err("<redir>", pipe));
	quoted = 0;
	if (rt == R_HEREDOC && has_quote((*ts)->next->val))
		quoted = 1;
	r = redir_new(rt, (*ts)->next->val, quoted);
	if (r == NULL)
	{
		free_cmds(*pipe);
		return (1);
	}
	redir_push(&cur->redirs, r);
	*ts = (*ts)->next->next;
	return (2);
}

static int	parse_word(t_token **ts, t_cmd *cur, t_cmd **pipe)
{
	if (ts == NULL || *ts == NULL)
		return (0);
	cur->argv = argv_push(cur->argv, (*ts)->val);
	if (cur->argv == NULL)
	{
		free_cmds(*pipe);
		return (1);
	}
	*ts = (*ts)->next;
	return (0);
}

// static int	parse_handle_token(t_token **ts, t_cmd **cur, t_cmd **pipe)
// {
// 	t_redir_type	dummy;
// 	int				r;

// 	if ((*ts)->type == TOK_PIPE)
// 		return (parse_pipe(ts, cur, pipe));
// 	if (tok_to_redir((*ts)->type, &dummy))
// 	{
// 		r = parse_redir(ts, *cur, pipe);
// 		if (r != 2)
// 			return (r);
// 		return (0);
// 	}
// 	if ((*ts)->type == TOK_WORD)
// 		return (parse_word(ts, *cur, pipe));
// 	return (syntax_err(NULL, pipe));
// }

static int	parse_handle_token(t_token **ts, t_cmd **cur, t_cmd **pipe)
{
	t_redir_type	dummy;
	int				r;

	// if ((*ts)->type == TOK_SEMI)
	// {
	// 	*ts = (*ts)->next;
	// 	return (0);
	// 	// return (syntax_err(";", pipe));
	// }
	if ((*ts)->type == TOK_PIPE)
		return (parse_pipe(ts, cur, pipe));
	if (tok_to_redir((*ts)->type, &dummy))
	{
		r = parse_redir(ts, *cur, pipe);
		if (r != 2)
			return (r);
		return (0);
	}
	if ((*ts)->type == TOK_WORD)
		return (parse_word(ts, *cur, pipe));
	return (syntax_err(NULL, pipe));
}

t_cmd	*parse_tokens(t_token *ts)
{
	t_cmd	*pipe;
	t_cmd	*cur;

	pipe = NULL;
	cur = cmd_new();
	if (cur == NULL)
		return (NULL);
	cmd_push(&pipe, cur);
	while (ts != NULL)
	{
		if (parse_handle_token(&ts, &cur, &pipe) != 0)
			return (NULL);
	}
	if (pipe == NULL)
		return (NULL);
	if (pipe->argv == NULL && pipe->redirs == NULL)
	{
		syntax_err(NULL, &pipe);
		return (NULL);
	}
	return (pipe);
}