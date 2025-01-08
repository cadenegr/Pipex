/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:47:56 by cadenegr          #+#    #+#             */
/*   Updated: 2024/05/31 16:41:24 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_access(char *cmd, t_p *p)
{
	int	i;

	i = 0;
	while (p->path_parts[i])
	{
		p->path = ft_strjoin(p->path_parts[i], "/");
		p->exec_cmd = ft_strjoin(p->path, cmd);
		free (p->path);
		p->path = NULL;
		if (access(p->exec_cmd, F_OK | X_OK) == 0)
		{
			ft_free_arr (p->path_parts);
			return ;
		}
		free (p->exec_cmd);
		p->exec_cmd = NULL;
		i++;
	}
	ft_free_arr (p->cmd_arg);
	ft_free_arr (p->path_parts);
	is_error(6);
}

void	which_path(char *cmd, char **env, t_p *p)
{
	int	path_len;

	path_len = ft_strlen(env[p->path_position]);
	p->path = ft_substr (env[p->path_position], 5, path_len - 5);
	p->path_parts = ft_split (p->path, ':');
	if (p->path == NULL && p->path_parts == NULL)
		is_error (1);
	free (p->path);
	p->path = NULL;
	ft_access(cmd, p);
}

void	execute(char *cmd, char **env, t_p *p)
{
	p->cmd_arg = ft_split(cmd, ' ');
	if (!p->cmd_arg)
		is_error(6);
	which_path (p->cmd_arg[0], env, p);
	if (execve (p->exec_cmd, p->cmd_arg, env) == -1)
		is_error (7);
}
