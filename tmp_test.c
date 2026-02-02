#include <stdio.h>
#include <unistd.h>

char	*ft_itoa(int n);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);

int	main(void)
{
	char	*pid_s;
	char	*joined;

	pid_s = ft_itoa((int)getpid());
	joined = ft_strjoin(".heredoc_", pid_s);
	printf("pid_s: '%s'\n", pid_s);
	printf("joined: '%s'\n", joined);
	return (0);
}
