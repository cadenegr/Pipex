/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:19:27 by cadenegr          #+#    #+#             */
/*   Updated: 2024/05/31 17:24:49 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"

typedef struct s_pipe
{
	int		error_type;
	int		path_position;
	pid_t	process_id;
	pid_t	second_id_process;
	char	**cmd_arg;
	char	**path_parts;
	char	*exec_cmd;
	char	*path;
	char	*substr;
}	t_p;

//arg_init_error.c
int		correct_argument(int ac, char **env, t_p *p);
void	init_struct(t_p *p);
void	is_error(int error_type);

//exec_env_access.c
void	execute(char *cmd, char **env, t_p *p);
void	which_path(char *cmd, char **env, t_p *p);
void	ft_access(char *cmd, t_p *p);

//parent_child.c
void	parent(char **av, int *fd, char **env, t_p *p);
void	child(char **av, int *fd, char **env, t_p *p);

#endif