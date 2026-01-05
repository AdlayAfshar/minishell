
#include "heredoc.h"
#include "libft.h"

char	*hd_make_name(void)
{
	static int	idx;
	char		*num;
	char		*name;

	idx++;
	num = ft_itoa(idx);
	if (!num)
		return (NULL);
	name = ft_strjoin(".heredoc_", num);
	free(num);
	return (name);
}

char	*hd_unquote_delim(const char *s)
{
	size_t	i;
	size_t	j;
	char	*out;

	if (!s)
		return (NULL);
	out = (char *)malloc(ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			out[j++] = s[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}