#ifndef BUILTINS_H
# define BUILTINS_H

int     builtin_echo(char **argv);
int     builtin_cd(char **argv, char ***envp);
int     builtin_pwd(char **argv);
int     builtin_env(char **argv, char **envp);
int     builtin_export(char **argv, char ***envp);
int     builtin_unset(char **argv, char ***envp);
int	    builtin_exit(char **argv, int last_status);

int     is_builtin_name(char *name);
int		exec_builtin(t_cmd *cmd, t_execctx *x);
int     is_valid_key(const char *key);


#endif