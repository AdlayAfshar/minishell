#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_spawn
{
	char	**envp;
	pid_t	*pids;
	int		*prev_fd;
	int		i;
}	t_spawn;

typedef struct s_execctx
{
	char	***envp;
	int		*last_status;
}	t_execctx;

#define EXIT_REQ_BASE 1000

void	exec_cmd_child(t_cmd *cmd, int in_fd, int out_fd, t_execctx *x);
int     apply_redirs(t_redir *r);

char	*find_in_path(char *cmd, char **envp);
char	*get_env_val(char **envp, const char *key);

int		wait_for_children(pid_t *pids, int count);
int		pipe_or_init(t_cmd *cur, int pipe_fd[2], pid_t *pids);
int		fork_or_fail(pid_t *pids, int i);

void	child_side(t_cmd *cur, int prev_fd, int pipe_fd[2], t_execctx *x);
int		parent_side(int prev_fd, int pipe_fd[2]);
int		exec_pipeline(t_cmd *cmd, t_execctx *x);

int		count_cmds(t_cmd *cmd);
int 	spawn_cmds(t_cmd *cmd, char **envp, int last_status);
int		spawn_all(t_cmd *cmd, t_spawn *s, t_execctx *x, int *count);
int		cleanup_spawn_fail(pid_t *pids, int prev_fd);

int		is_str(char *s, const char *ref);
int		is_name(const char *n, const char *s);


#endif