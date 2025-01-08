/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:47:43 by cadenegr          #+#    #+#             */
/*   Updated: 2024/05/31 16:45:00 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char **av, int *fd, char **env, t_p *p)
{
	int	file_d;

	file_d = open (av[1], O_RDONLY, 0777);
	if (file_d == -1)
		is_error(4);
	dup2 (file_d, STDIN_FILENO);
	dup2 (fd[1], STDOUT_FILENO);
	close (file_d);
	close(fd[1]);
	close (fd[0]);
	execute(av[2], env, p);
}

void	parent(char **av, int *fd, char **env, t_p *p)
{
	int		file_d;

	file_d = open (av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_d == -1)
		is_error (5);
	dup2 (file_d, STDOUT_FILENO);
	dup2 (fd[0], STDIN_FILENO);
	close (file_d);
	close(fd[0]);
	close (fd[1]);
	execute (av[3], env, p);
}
