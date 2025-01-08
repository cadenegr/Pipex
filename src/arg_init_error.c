/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_init_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:10:51 by cadenegr          #+#    #+#             */
/*   Updated: 2024/05/31 17:24:56 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	is_error(int error_type)
{
	if (error_type == 0)
		ft_putstr_fd("Not enough arguments.\n", 2);
	if (error_type == 1)
		ft_putstr_fd("There is no PATH.\n", 2);
	if (error_type == 2)
		ft_putstr_fd("The file discriptors couldn't be forcked.\n", 2);
	if (error_type == 3)
		ft_putstr_fd("Process id failed.\n", 2);
	if (error_type == 4)
		ft_putstr_fd("File cannot be open.\n", 2);
	if (error_type == 5)
		ft_putstr_fd("Problem with the output file.\n", 2);
	if (error_type == 6)
		ft_putstr_fd("Error with the command\n", 2);
	if (error_type == 7)
		ft_putstr_fd("Error duplicating file descriptor.\n", 2);
	if (error_type == 8)
		ft_putstr_fd("Second fork failed.\n", 2);
	exit (1);
}

void	init_struct(t_p *p)
{
	p->error_type = -1;
	p->path_position = -1;
	p->cmd_arg = NULL;
	p->path = NULL;
	p->exec_cmd = NULL;
	p->path_parts = NULL;
	p->substr = NULL;
}

int	correct_argument(int ac, char **env, t_p *p)
{
	int	i;

	init_struct(p);
	if (ac != 5)
		is_error (0);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (p->path_position = i);
		i++;
	}
	is_error (1);
	return (0);
}
