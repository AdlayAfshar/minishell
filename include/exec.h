#ifndef EXEC_H
# define EXEC_H


# include <fcntl.h>
# include <errno.h>

typedef struct s_spawn
{
	char	**envp;
	pid_t	*pids;
	int		*prev_fd;
	int		i;
}	t_spawn;


void	exec_cmd_child(t_cmd *cmd, int in_fd, int out_fd, char **envp);
int     apply_redirs(t_redir *r);
char	*find_in_path(char *cmd, char **envp);
char	*get_env_val(char **envp, const char *key);

int		wait_for_children(pid_t *pids, int count);
int		pipe_or_init(t_cmd *cur, int pipe_fd[2], pid_t *pids);
int		fork_or_fail(pid_t *pids, int i);
void	child_side(t_cmd *cur, int prev_fd, int pipe_fd[2], char **envp);
int		parent_side(int prev_fd, int pipe_fd[2]);
int		exec_pipeline(t_cmd *cmd, char ***envp);

int		count_cmds(t_cmd *cmd);
int		spawn_cmds(t_cmd *cmd, char **envp);


#endif