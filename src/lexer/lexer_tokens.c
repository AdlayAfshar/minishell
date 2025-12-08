#include "minishell.h"

// allocate and initialize a new token with given value and type
t_token	*token_new(char *value, t_tok_type type)
{
	t_token	*t;

	t = malloc(sizeof(*t));
	if (!t)
		return (NULL);
	t->type = type;
	t->val = value; 
	t->next = NULL;
	return (t);
}

// append token 'new' to the end of the list *lst
void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*cur;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

// free the whole token list and set *lst to NULL
void	token_list_clear(t_token **lst)
{
	t_token	*tmp;

	while (lst && *lst)
	{
		tmp = (*lst)->next;
		free((*lst)->val);
		free(*lst);
		*lst = tmp;
	}
}