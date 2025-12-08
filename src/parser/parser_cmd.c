#include "minishell.h"

void	redir_push(t_redir **lst, t_redir *node)
{
	t_redir	*p;

	if (lst == NULL || node == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	p = *lst;
	while (p->next != NULL)
		p = p->next;
	p->next = node;
}

t_cmd	*cmd_new(void)
{
	t_cmd	*c;

	c = (t_cmd *)malloc(sizeof(t_cmd));
	if (c == NULL)
		return (NULL);
	c->argv = NULL;
	c->redirs = NULL;
	c->next = NULL;
	return (c);
}

void	cmd_push(t_cmd **lst, t_cmd *node)
{
	t_cmd	*p;

	if (lst == NULL || node == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	p = *lst;
	while (p->next != NULL)
		p = p->next;
	p->next = node;
}

int	syntax_err(const char *near, t_cmd **pl)
{
	if (near != NULL)
		ft_putstr_fd("minishell: syntax error near `", 2);
	else
		ft_putstr_fd("minishell: syntax error", 2);
	if (near != NULL)
	{
		ft_putstr_fd((char *)near, 2);
		ft_putstr_fd("`\n", 2);
	}
	else
		ft_putstr_fd("\n", 2);
	if (pl != NULL && *pl != NULL)
		free_cmds(*pl);
	return (1);
}

int	tok_to_redir(t_tok_type t, t_redir_type *out)
{
	if (out == NULL)
		return (0);
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