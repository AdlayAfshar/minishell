
#include "exec.h"

static char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static void	free_split(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

static char	*search_paths(char **paths, char *cmd)
{
	char	*full;
	int		i;

	full = NULL;
	i = 0;
	while (paths[i] && !full)
	{
		full = join_path(paths[i], cmd);
		if (full && access(full, X_OK) != 0)
		{
			free(full);
			full = NULL;
		}
		i++;
	}
	return (full);
}

char	*find_in_path(char *cmd, char **envp)
{
	char	**paths;
	char	*env_path;
	char	*full;

	if (!cmd || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	env_path = get_env_val(envp, "PATH");
	if (!env_path || env_path[0] == '\0')
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	full = search_paths(paths, cmd);
	free_split(paths);
	return (full);
}
