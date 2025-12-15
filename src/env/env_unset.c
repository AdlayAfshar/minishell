#include "minishell.h"

int	env_count(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	return (i);
}

int	find_env_index(char **envp, const char *key)
{
	int		i;
	int		klen;

	if (!envp || !key)
		return (-1);
	klen = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, klen)
			&& envp[i][klen] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	remove_index(char ***envp, int idx)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)malloc(sizeof(char *) * (env_count(*envp) + 1));
	if (!new_env)
		return (1);
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (i != idx)
			new_env[j++] = (*envp)[i];
		else
			free((*envp)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}

static int	unset_key(char ***envp, const char *key)
{
	int	idx;

	if (!envp || !*envp || !key)
		return (0);
	idx = find_env_index(*envp, key);
	if (idx < 0)
		return (0);
	return (remove_index(envp, idx));
}

int	builtin_unset(char **argv, char ***envp)
{
	int	i;
	int	ret;

	if (!argv || !envp)
		return (1);
	i = 1;
	ret = 0;
	while (argv[i])
	{
		if (unset_key(envp, argv[i]) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}