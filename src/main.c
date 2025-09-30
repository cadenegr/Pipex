/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:41 by cadenegr          #+#    #+#             */
/*   Updated: 2025/09/30 15:22:11 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		status1, status2;
	t_p		p;

	correct_argument(ac, env, &p);
	if (pipe(fd) == -1)
		is_error(2);
	p.process_id = fork();
	if (p.process_id == -1)
		is_error(3);
	if (!p.process_id)
		child(av, fd, env, &p);
	p.second_id_process = fork();
	if (p.second_id_process == -1)
		is_error(8);
	if (!p.second_id_process)
		parent (av, fd, env, &p);
	close(fd[0]);
	close(fd[1]);
	waitpid(p.process_id, &status1, 0);
	waitpid(p.second_id_process, &status2, 0);
	if (WEXITSTATUS(status1) != 0 || WEXITSTATUS(status2) != 0)
		return (1);
	return (EXIT_SUCCESS);
}
