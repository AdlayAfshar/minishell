
#include "builtins.h"
#include "libft.h"

static int	is_flag_n(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] == '\0')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	if (s[i] != '\0')
		return (0);
	return (1);
}

static void	print_words(char **argv, int start)
{
	int	i;

	i = start;
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
}

int	builtin_echo(char **argv)
{
	int	i;
	int	print_nl;

	if (!argv || !argv[0])
		return (0);
	i = 1;
	print_nl = 1;
	while (argv[i] && is_flag_n(argv[i]))
	{
		print_nl = 0;
		i++;
	}
	if (argv[i])
		print_words(argv, i);
	if (print_nl)
		write(1, "\n", 1);
	return (0);
}