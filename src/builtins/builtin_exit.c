
#include "builtins.h"
#include "exec.h"

static int	is_numeric(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_error(const char *msg, const char *arg)
{
	write(2, "minishell: exit: ", 18);
	if (arg)
		write(2, arg, ft_strlen(arg));
	if (msg)
	{
		write(2, ": ", 2);
		write(2, msg, ft_strlen(msg));
	}
	write(2, "\n", 1);
}

static int	handle_exit_args(char **argv, int last_status, int *should_exit)
{
	if (!argv[1])
	{
		*should_exit = 1;
		return (last_status);
	}
	if (!is_numeric(argv[1]))
	{
		exit_error("numeric argument required", argv[1]);
		*should_exit = 1;
		return (255);
	}
	if (argv[2])
	{
		exit_error("too many arguments", NULL);
		*should_exit = 0;
		return (1);
	}
	*should_exit = 1;
	return (ft_atoi(argv[1]));
}

int	builtin_exit(char **argv, int last_status)
{
	int	status;
	int	should_exit;

	status = handle_exit_args(argv, last_status, &should_exit);
	if (should_exit)
		return (EXIT_REQ_BASE + (status & 255));
	return (status);
}