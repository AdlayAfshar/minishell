
#include "../../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- ابزارهای کوچک ---- */

static int	has_quote(const char *s)
{
	while (s && *s)
	{
		if (*s == '\'' || *s == '\"')
			return (1);
		s++;
	}
	return (0);
}

static char	**argv_push(char **argv, const char *s)
{
	size_t	n;
	char	**nv;

	n = 0;
	if (argv)
		while (argv[n])
			n++;
	nv = (char **)malloc(sizeof(char *) * (n + 2));
	if (!nv)
		return (NULL);
	for (size_t i = 0; i < n; i++)
		nv[i] = argv[i];
	nv[n] = strdup(s ? s : "");
	if (!nv[n])
	{
		free(nv);
		return (NULL);
	}
	nv[n + 1] = NULL;
	free(argv);
	return (nv);
}

static t_redir	*redir_new(t_redir_type type, const char *target, int quoted)
{
	t_redir	*r;

	r = (t_redir *)malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->target = strdup(target ? target : "");
	if (!r->target)
		return (free(r), NULL);
	r->heredoc_quoted = quoted;
	r->next = NULL;
	return (r);
}

static void	redir_push(t_redir **lst, t_redir *node)
{
	t_redir	*p;

	if (!*lst)
	{
		*lst = node;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = node;
}

static t_cmd	*cmd_new(void)
{
	t_cmd	*c;

	c = (t_cmd *)malloc(sizeof(t_cmd));
	if (!c)
		return (NULL);
	c->argv = NULL;
	c->redirs = NULL;
	c->next = NULL;
	return (c);
}

static void	cmd_push(t_cmd **lst, t_cmd *node)
{
	t_cmd	*p;

	if (!*lst)
	{
		*lst = node;
		return ;
	}
	p = *lst;
	while (p->next)
		p = p->next;
	p->next = node;
}

/* پیام خطای ساده (می‌تونی بعداً سبک bash کنی) */
static int	syntax_err(const char *near, t_cmd **pl)
{
	if (near)
		fprintf(stderr, "minishell: syntax error near `%s`\n", near);
	else
		fprintf(stderr, "minishell: syntax error\n");
	if (pl && *pl)
		free_cmds(*pl);
	return (1);
}

/* ---- مپ توکن -> نوع ریدایرکشن ---- */

static int	tok_to_redir(t_tok_type t, t_redir_type *out)
{
	if (t == TOK_REDIR_IN)
	{
		*out = R_IN;
		return (1);
	}
	if (t == TOK_REDIR_OUT)
	{
		*out = R_OUT;
		return (1);
	}
	if (t == TOK_APPEND)
	{
		*out = R_APPEND;
		return (1);
	}
	if (t == TOK_HEREDOC)
	{
		*out = R_HEREDOC;
		return (1);
	}
	return (0);
}

/* ---- هستهٔ پارس ---- */

t_cmd	*parse_tokens(t_token *ts)
{
	t_cmd			*pipe;
	t_cmd			*cur;
	t_redir_type	rt;
	int				quoted;
	t_redir			*r;

	pipe = NULL;
	cur = cmd_new();
	if (!cur)
		return (NULL);
	cmd_push(&pipe, cur);
	while (ts)
	{
		if (ts->type == TOK_PIPE)
		{
			/* pipe نباید پشت‌سر هم بیاید یا اول/آخر باشد */
			if ((!cur->argv && !cur->redirs) || !ts->next
				|| ts->next->type == TOK_PIPE)
				return (syntax_err("|", &pipe), NULL);
			cur = cmd_new();
			if (!cur)
				return (free_cmds(pipe), NULL);
			cmd_push(&pipe, cur);
			ts = ts->next;
			continue ;
		}
		/* ریدایرکشن‌ها: باید بعدش WORD بیاید */
		{
			if (tok_to_redir(ts->type, &rt))
			{
				if (!ts->next || ts->next->type != TOK_WORD)
					return (syntax_err(ts->val ? ts->val : (rt == R_IN ? "<" : rt == R_OUT ? ">" : rt == R_APPEND ? ">>" : "<<"),
							&pipe), NULL);
				{
					quoted = (rt == R_HEREDOC) && has_quote(ts->next->val);
					r = redir_new(rt, ts->next->val, quoted);
					if (!r)
						return (free_cmds(pipe), NULL);
					redir_push(&cur->redirs, r);
				}
				ts = ts->next->next;
				continue ;
			}
		}
		/* WORD → argv */
		if (ts->type == TOK_WORD)
		{
			cur->argv = argv_push(cur->argv, ts->val);
			if (!cur->argv)
				return (free_cmds(pipe), NULL);
			ts = ts->next;
			continue ;
		}
		/* نوع ناشناخته (نمی‌رسیم به این حالت با lexer فعلی) */
		return (syntax_err(NULL, &pipe), NULL);
	}
	/* آخر کار: نباید فرمان خالی بماند */
	if (!pipe || (!pipe->argv && !pipe->redirs))
		return (syntax_err(NULL, &pipe), NULL);
	return (pipe);
}
