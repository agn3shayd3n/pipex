/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agnesgar <agnesgar@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-20 16:40:38 by agnesgar          #+#    #+#             */
/*   Updated: 2024-10-20 16:40:38 by agnesgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_executable(char *command, char **env)
{
	size_t	len;
	size_t	i;
	char	**directories;
	char	*check_path;

	directories = ft_split(find_env("PATH", env), ':');
	i = 0;
	while (directories[i])
	{
		len = ft_strlen(directories[i]) + ft_strlen(command) + 2;
		check_path = (char *)malloc(sizeof(char) * len);
		if (!check_path)
			(perror("couldn't allocate memory\n"), exit(1));
		ft_strlcpy(check_path, directories[i], len);
		ft_strlcat(check_path, "/", len);
		ft_strlcat(check_path, command, len);
		if (access(check_path, F_OK) == 0)
		{
			ft_free(directories);
			return (check_path);
		}
		free(check_path);
		i++;
	}
	return (ft_free(directories), NULL);
}

int	exec_path(char *path, char **env)
{
	char	**command;
	char	*executable;
	int		exec_status;

	command = ft_split(path, ' ');
	if (!command)
		handle_error("couldn't split path", 1);
	executable = find_executable(command[0], env);
	if (!executable)
	{
		handle_error(command[0], 127);
		ft_free(command);
	}
	exec_status = execve(executable, command, env);
	if ((exec_status) == -1)
	{
		handle_error("couldn't execute command", 1);
		ft_free(command);
		free(executable);
	}
	ft_free(command);
	return (free(executable), exec_status);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	*find_env(char *str, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == str[j] && str[j])
			j++;
		if (env[i][j] == '=' && !str[j])
			return (env[i] + j + 1);
		i++;
	}
	return (NULL);
}

int	open_file(char *file, int option)
{
	int	fd;

	if (option == 0)
		fd = open(file, O_RDONLY);
	else if (option == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (option == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		handle_error("Error: couldn't open file", 1);
	return (fd);
}
