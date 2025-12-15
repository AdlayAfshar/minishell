#include "minishell.h"

int	is_valid_key(const char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!(ft_isalpha((unsigned char)key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum((unsigned char)key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}