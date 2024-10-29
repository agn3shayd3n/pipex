/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agnesgar <agnesgar@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-20 16:11:16 by agnesgar          #+#    #+#             */
/*   Updated: 2024-10-20 16:11:16 by agnesgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(const char *message, int error_code)
{
	write(2, message, ft_strlen(message));
	write(2, ": ", 2);
	write(2, strerror(error_code), ft_strlen(strerror(error_code)));
	write(2, "\n", 1);
	exit(error_code);
}

int	first_process(char **av, int *pid_fd, char **env)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("Error: Fork in 1 arg", 1);
	else if (pid == 0)
	{
		close(pid_fd[READ_END]);
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			exit(1);
		if (dup2(fd, STDIN_FILENO) == -1)
			handle_error("Error: dup2, stdin to file", 3);
		if (dup2(pid_fd[WRITE_END], STDOUT_FILENO) == -1)
			(close(fd), handle_error("Error: dup2, stdout to pipe", 4));
		close(pid_fd[WRITE_END]);
		if (exec_path(av[2], env) == -1)
			(handle_error(av[2], 127));
	}
	return (pid);
}

int	second_process(char **av, int *pid_fd, char **env)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error("Error: Fork in 2 arg", 1);
	else if (pid == 0)
	{
		close(pid_fd[WRITE_END]);
		fd = open_file(av[4], 1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			handle_error(av[4], 2);
		if (dup2(pid_fd[READ_END], STDIN_FILENO) == -1)
			(close(fd), handle_error("Error: dup2, stdout to file", 3));
		close(fd);
		close(pid_fd[READ_END]);
		if (exec_path(av[3], env) == -1)
			handle_error(av[3], 127);
	}
	return (pid);
}

int	main(int argc, char **av, char **env)
{
	int	pid_fd[2];
	int	pids[2];
	int	status1;
	int	status2;

	if (argc != 5)
		handle_error("Usage", 1);
	if ((open_file(av[1], 0) == -1) || (open_file(av[4], 1) == -1))
		handle_error("No such file or directory", 2);
	if (pipe(pid_fd) == -1)
		handle_error("Error: pipe", 1);
	pids[0] = first_process(av, pid_fd, env);
	pids[1] = second_process(av, pid_fd, env);
	close(pid_fd[READ_END]);
	close(pid_fd[WRITE_END]);
	waitpid(pids[0], &status1, 0);
	waitpid(pids[1], &status2, 0);
	if (WIFEXITED(status1) && WEXITSTATUS(status1) != 0)
		exit(WEXITSTATUS(status1));
	else if (WIFEXITED(status2) && WEXITSTATUS(status2) != 0)
		exit(WEXITSTATUS(status2));
	else if (WIFEXITED(status1) && WIFEXITED(status2))
		exit(0);
	return (0);
}
