
#include "./minishell.h"

// #include <readline/readline.h>
// #include <readline/history.h>

void	ft_error(const char *msg)
{
	if (msg)
		perror(msg);
	exit(EXIT_FAILURE);
}

// static char	*find_in_paths(char **paths, char *cmd)
// {
// 	char	*tmp;
// 	char	*full_path;
// 	int		i;

// 	i = 0;
// 	if (!paths || !cmd)
// 		return (NULL);
// 	while (paths[i])
// 	{
// 		tmp = ft_strjoin(paths[i], "/");
// 		if (!tmp)
// 			return (NULL);
// 		full_path = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (!full_path)
// 			return (NULL);
// 		if (access(full_path, X_OK) == 0)
// 			return (full_path);
// 		free(full_path);
// 		i++;
// 	}
// 	return (NULL);
// }

static char	**get_paths_from_envp(char **envp)
{
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

// char	*get_cmd_path(char *cmd, char **envp)
// {
// 	char	**paths;
// 	char	*full_path;

// 	if (!cmd)
// 		return (NULL);
// 	if (access(cmd, X_OK) == 0)
// 		return (ft_strdup(cmd));
// 	paths = get_paths_from_envp(envp);
// 	if (!paths)
// 		return (NULL);
// 	full_path = find_in_paths(paths, cmd);
// 	free_split(paths);
// 	return (full_path);
// }

// void	first_child(char **argv, char **envp, int *pipefd)
// {
// 	int		file1;
// 	char	**cmd_args;
// 	char	*cmd_path;

// 	file1 = open(argv[1], O_RDONLY);
// 	if (file1 < 0)
// 	{
// 		ft_error("Error opening file1");
// 	}
// 	dup2(file1, STDIN_FILENO);
// 	dup2(pipefd[1], STDOUT_FILENO);
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	close(file1);
// 	cmd_args = ft_split(argv[2], ' ');
// 	cmd_path = get_cmd_path(cmd_args[0], envp);
// 	if (!cmd_path)
// 	{
// 		free_split(cmd_args);
// 		ft_error("Command not found");
// 	}
// 	execve(cmd_path, cmd_args, envp);
// 	free(cmd_path);
// 	free_split(cmd_args);
// 	ft_error("Execve failed");
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	int		pipefd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int		status1;

// 	if (argc != 5)
// 	{
// 		ft_error("Usage: ./pipex file1 cmd1 cmd2 file2");
// 	}
// 	if (!envp || !*envp)
// 	{
// 		ft_error("Usage: ./pipex file1 cmd1 cmd2 file2");
// 	}
// 	if (pipe(pipefd) == -1)
// 		ft_error("Pipe failed");
// 	pid1 = fork();
// 	if (pid1 == -1)
// 		handle_fork_error("Fork failed for child1", pipefd);
// 	if (pid1 == 0)
// 	{
// 		first_child(argv, envp, pipefd);
// 	}
// 	pid2 = fork();
// 	if (pid2 == -1)
// 		handle_fork_error("Fork failed for child2", pipefd);
// 	if (pid2 == 0)
// 	{
// 		second_child(argv, envp, pipefd);
// 	}
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid1, &status1, 0);
// 	waitpid(pid2, &status1, 0);
// 	if (WIFEXITED(status1) && WEXITSTATUS(status1) != 0)
// 		return (WEXITSTATUS(status1));
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	**paths;
	char	**cmd_args;

	if (argc < 1)
	{
		ft_error("Usage: ./pipex file1 cmd1 cmd2 file2");
	}
	i = 0;
	cmd_args = ft_split(argv[2], ' ');
	printf("XOX:[%d]: %s", i, cmd_args[i]);
	printf("\n\n");
	paths = get_paths_from_envp(envp);
	printf("-------------------envp-----------------\n");
	while (envp[i])
	{
		printf("envp:[%d]: %s\n", i, envp[i]);
		i++;
	}
	printf("\n\n");
	i = 0;
	printf("-------------------paths-----------------\n");
	while (paths[i])
	{
		printf("pathes:[%d]: %s\n", i, paths[i]);
		i++;
	}
	// char	*input;
	// while (1)
	// {
	// 	input = readline("myshell> ");
	// 	if (!input)
	// 	{
	// 		break ;
	// 	}
	// 	if (*input)
	// 	{
	// 		add_history(input);
	// 	}
	// 	printf("You typed: %s\n", input);
	// 	free(input);
	// }
	return (0);
}
