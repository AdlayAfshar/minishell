#include "minishell.h"

// return 1 if c is a whitespace character, 0 otherwise
int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

// move index i forward while current char is a whitespace
void	skip_spaces(const char *s, size_t *i)
{
	while (s[*i] && is_space(s[*i]))
		(*i)++;
}

// return 1 if c can start an operator token, 0 otherwise
int	is_op_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

// int	is_op_char(char c)
// {
// 	return (c == '|' || c == '<' || c == '>' || c == ';');
// }