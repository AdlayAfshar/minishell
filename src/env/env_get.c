#include "minishell.h"

// static int	key_match(const char *entry, const char *key)
// {
// 	int	i;

// 	i = 0;
// 	while (key[i] && entry[i] && entry[i] == key[i])
// 		i++;
// 	if (key[i] != '\0')
// 		return (0);
// 	if (entry[i] != '=')
// 		return (0);
// 	return (1);
// }

// char	*get_env_val(char **envp, const char *key)
// {
// 	int	i;

// 	if (!envp || !key || !key[0])
// 		return (NULL);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (key_match(envp[i], key))
// 			return (envp[i] + ft_strlen(key) + 1);
// 		i++;
// 	}
// 	return (NULL);
// }

char	*get_env_val(char **envp, const char *key)
{
	return (exp_get_env_val(key, envp));
}