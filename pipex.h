/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agnesgar <agnesgar@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-20 16:11:32 by agnesgar          #+#    #+#             */
/*   Updated: 2024-10-20 16:11:32 by agnesgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include "./libft/libft.h"

# define READ_END 0 // index pipe 0 reading
# define WRITE_END 1 // index pipe 1 writing

void	ft_free(char **str);
char	*find_executable(char *command, char **env);
int		exec_path(char *path, char **env);
char	*find_env(char *str, char **env);
int		open_file(char *file, int option);
void	handle_error(const char *message, int error_code);

#endif