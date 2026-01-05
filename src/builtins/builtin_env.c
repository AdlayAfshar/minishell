
#include "builtins.h"
#include "libft.h"

static void	print_env(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

int	builtin_env(char **argv, char **envp)
{
	if (argv && argv[1])
	{
		write(2, "minishell: env: too many arguments\n", 35);
		return (1);
	}
	print_env(envp);
	return (0);
}