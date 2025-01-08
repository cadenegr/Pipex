/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:41 by cadenegr          #+#    #+#             */
/*   Updated: 2024/05/31 16:44:29 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd[2];
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
	if (!p.second_id_process)
		parent (av, fd, env, &p);
	waitpid(p.process_id, NULL, 0);
	waitpid(p.process_id, NULL, 0);
	return (EXIT_SUCCESS);
}
