
#include "env.h"

static char	*make_env_pair(const char *key, const char *val)
{
	int		klen;
	int		vlen;
	char	*s;

	klen = ft_strlen(key);
	vlen = 0;
	if (val)
		vlen = ft_strlen(val);
	s = (char *)malloc(klen + 1 + vlen + 1);
	if (!s)
		return (NULL);
	copy_key_to_buf(s, key, klen);
	s[klen] = '=';
	copy_val_to_buf(s, val, klen + 1, vlen);
	return (s);
}

static int	replace_env(char **envp, int idx, const char *key, const char *val)
{
	char	*pair;

	pair = make_env_pair(key, val);
	if (!pair)
		return (1);
	free(envp[idx]);
	envp[idx] = pair;
	return (0);
}

static int	append_env_var(char ***envp, const char *key, const char *val)
{
	int		n;
	char	**new_env;
	int		i;

	n = env_count(*envp);
	new_env = (char **)malloc(sizeof(char *) * (n + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < n)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[i] = make_env_pair(key, val);
	if (!new_env[i])
	{
		free(new_env);
		return (1);
	}
	new_env[i + 1] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}

int	set_env_var(char ***envp, const char *key, const char *val)
{
	int	idx;

	if (!envp || !key)
		return (1);
	if (*envp)
	{
		idx = find_env_index(*envp, key);
		if (idx >= 0)
			return (replace_env(*envp, idx, key, val));
		return (append_env_var(envp, key, val));
	}
	*envp = (char **)malloc(sizeof(char *) * 2);
	if (!*envp)
		return (1);
	(*envp)[0] = make_env_pair(key, val);
	if (!(*envp)[0])
	{
		free(*envp);
		*envp = NULL;
		return (1);
	}
	(*envp)[1] = NULL;
	return (0);
}
