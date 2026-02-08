#include "builtins.h"
#include <limits.h>

static int	parse_sign(const char **s, int *sign)
{
	*sign = 1;
	if (!*s || !**s)
		return (0);
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			*sign = -1;
		(*s)++;
	}
	if (!**s)
		return (0);
	return (1);
}

static int	parse_digits(const char *s, unsigned long long limit,
		unsigned long long *acc)
{
	unsigned long long	d;

	*acc = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		d = (unsigned long long)(*s - '0');
		if (*acc > (limit - d) / 10ULL)
			return (0);
		*acc = *acc * 10ULL + d;
		s++;
	}
	return (1);
}

static void	apply_sign(int sign, unsigned long long acc, long long *out)
{
	if (sign == -1)
	{
		if (acc == (unsigned long long)LLONG_MAX + 1ULL)
			*out = LLONG_MIN;
		else
			*out = -(long long)acc;
	}
	else
		*out = (long long)acc;
}

int	ms_atoll_strict(const char *s, long long *out)
{
	int					sign;
	unsigned long long	acc;
	unsigned long long	limit;

	if (!s || !out)
		return (0);
	if (!parse_sign(&s, &sign))
		return (0);
	limit = (unsigned long long)LLONG_MAX;
	if (sign == -1)
		limit = (unsigned long long)LLONG_MAX + 1ULL;
	if (!parse_digits(s, limit, &acc))
		return (0);
	apply_sign(sign, acc, out);
	return (1);
}
