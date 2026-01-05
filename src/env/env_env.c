
#include "env.h"

void	copy_key_to_buf(char *s, const char *key, int klen)
{
	int	i;

	i = 0;
	while (i < klen)
	{
		s[i] = key[i];
		i++;
	}
}

void	copy_val_to_buf(char *s, const char *val, int start, int vlen)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (j < vlen)
	{
		s[i] = val[j];
		i++;
		j++;
	}
	s[i] = '\0';
}

static void	free_env_array(char **env, int count)
{
	while (count > 0)
	{
		count--;
		free(env[count]);
	}
	free(env);
}

char	**dup_env(char **envp)
{
	int		n;
	char	**new_env;
	int		i;

	if (!envp)
		return (NULL);
	n = env_count(envp);
	new_env = (char **)malloc(sizeof(char *) * (n + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			free_env_array(new_env, i);
			return (NULL);
		}
		i++;
	}
	new_env[n] = NULL;
	return (new_env);
}

void	free_env(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}