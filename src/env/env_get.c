#include "env.h"
#include "expand.h"

char	*get_env_val(char **envp, const char *key)
{
	return (exp_get_env_val(key, envp));
}