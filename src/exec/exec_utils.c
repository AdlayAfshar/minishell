#include "minishell.h"

int	is_str(char *s, const char *ref)
{
	int	i;

	if (!s || !ref)
		return (0);
	i = 0;
	while (s[i] && ref[i] && s[i] == ref[i])
		i++;
	if (s[i] == '\0' && ref[i] == '\0')
		return (1);
	return (0);
}

int	is_name(const char *n, const char *s)
{
	int	i;

	i = 0;
	while (n[i] && s[i] && n[i] == s[i])
		i++;
	if (n[i] != '\0' || s[i] != '\0')
		return (0);
	return (1);
}