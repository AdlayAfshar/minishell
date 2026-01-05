
#include "minishell.h"

static void	print_export_error(const char *name)
{
	write(2, "minishell: export: invalid identifier: ", 40);
	if (name)
		write(2, name, ft_strlen(name));
	write(2, "\n", 1);
}

static void	print_export_list(char **envp)
{
	int		i;
	char	*eq;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		write(1, "declare -x ", 11);
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			write(1, envp[i], (size_t)(eq - envp[i]) + 1);
			write(1, "\"", 1);
			write(1, eq + 1, ft_strlen(eq + 1));
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

static int	handle_no_equal(char *arg, char ***envp)
{
	if (!is_valid_key(arg))
	{
		print_export_error(arg);
		return (1);
	}
	if (set_env_var(envp, arg, "") != 0)
		return (1);
	return (0);
}

static int	handle_with_equal(char *arg, char ***envp)
{
	char	key[256];
	char	*eq;
	char	*val;
	size_t	klen;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return (1);
	klen = (size_t)(eq - arg);
	if (klen == 0 || klen >= sizeof(key))
		return (1);
	ft_strlcpy(key, arg, klen + 1);
	val = eq + 1;
	if (!is_valid_key(key))
	{
		print_export_error(key);
		return (1);
	}
	if (set_env_var(envp, key, val) != 0)
		return (1);
	return (0);
}

int	builtin_export(char **argv, char ***envp)
{
	int	i;
	int	res;

	if (!argv || !envp)
		return (1);
	if (!argv[1])
	{
		print_export_list(*envp);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
			res = handle_with_equal(argv[i], envp);
		else
			res = handle_no_equal(argv[i], envp);
		if (res)
			return (1);
		i++;
	}
	return (0);
}