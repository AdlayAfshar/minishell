
#include "../../include/lexer.h"
#include <stdlib.h>
#include <string.h>

t_token	*tok_new(t_tok_type type, const char *val, size_t len)
{
	t_token	*t;

	t = (t_token *)malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->type = type;
	t->val = NULL;
	t->next = NULL;
	if (val && len > 0)
	{
		t->val = (char *)malloc(len + 1);
		if (!t->val)
		{
			free(t);
			return (NULL);
		}
		memcpy(t->val, val, len);
		t->val[len] = '\0';
	}
	return (t);
}

void	tok_push(t_token **lst, t_token *node)
{
	t_token	*cur;

	if (!lst || !node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = node;
}

void	free_tokens(t_token *t)
{
	t_token	*nx;

	while (t)
	{
		nx = t->next;
		if (t->val)
			free(t->val);
		free(t);
		t = nx;
	}
}
