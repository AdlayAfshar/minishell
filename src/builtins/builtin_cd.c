
#include "builtins.h"
#include "libft.h"
#include "env.h"
#include "exec.h"
#include <unistd.h>

static void	print_cd_error(const char *msg, const char *arg)
{
	write(2, "minishell: cd: ", 15);
	write(2, msg, ft_strlen(msg));
	if (arg)
	{
		write(2, ": ", 2);
		write(2, arg, ft_strlen(arg));
	}
	write(2, "\n", 1);
}

static int	update_pwd_vars(char ***envp, char *oldpwd)
{
	char	*cwd;
	int		ret;

	ret = 0;
	if (oldpwd)
	{
		if (set_env_var(envp, "OLDPWD", oldpwd))
			ret = 1;
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		if (set_env_var(envp, "PWD", cwd))
			ret = 1;
		free(cwd);
	}
	return (ret);
}

static int	change_dir(const char *path, char ***envp)
{
	char	*oldpwd;
	int		ret;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		print_cd_error("cannot change directory", path);
		free(oldpwd);
		return (1);
	}
	ret = update_pwd_vars(envp, oldpwd);
	free(oldpwd);
	return (ret);
}

int	builtin_cd(char **argv, char ***envp)
{
	char	*target;

	/* case: cd */
	if (!argv[1])
	{
		target = get_env_val(*envp, "HOME");
		if (!target)
		{
			print_cd_error("HOME not set", NULL);
			return (1);
		}
		return (change_dir(target, envp));
	}

	/* case: cd <dir> <extra> → too many args */
	if (argv[2])
	{
		print_cd_error("too many arguments", NULL);
		return (1);
	}

	return (change_dir(argv[1], envp));
}