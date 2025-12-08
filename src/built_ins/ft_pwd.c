//#include "../../includes/built_ins.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include "../ft_printf/ft_printf.h" - doesn't link with the path to my ft_printf

typedef struct s_command
{
    // Placeholder for command structure
    // Add relevant fields as necessary
} t_command;
typedef struct s_env
{
    // Placeholder for environment structure
    // Add relevant fields as necessary
} t_env;

int ft_pwd(t_command *cmd, t_env **env)
{
    char	*cwd;

    (void)cmd;
    (void)env;
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("pwd");
        return (1);
    }
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}

int main(void)
{
    // Example usage of ft_pwd
    t_command cmd;
    t_env *env = NULL;

    return ft_pwd(&cmd, &env);
}