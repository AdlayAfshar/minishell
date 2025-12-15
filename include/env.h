#ifndef ENV_H
# define ENV_H

int	    set_env_var(char ***envp, const char *key, const char *val);
char	**dup_env(char **envp);
void	free_env(char **envp);
int		set_env_var(char ***envp, const char *key, const char *val);
int	    env_count(char **envp);
int	    find_env_index(char **envp, const char *key);
void	copy_key_to_buf(char *s, const char *key, int klen);
void	copy_val_to_buf(char *s, const char *val, int start, int vlen);

#endif