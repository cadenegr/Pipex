/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_init_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:10:51 by cadenegr          #+#    #+#             */
/*   Updated: 2025/09/30 15:13:43 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	display_enhanced_error(int error_type, const char *context)
{
	(void)error_type; // Mark as intentionally unused for now
	ft_putstr_fd("🚨 PIPEX ERROR ", 2);
	if (context)
	{
		ft_putstr_fd("(", 2);
		ft_putstr_fd((char *)context, 2);
		ft_putstr_fd("): ", 2);
	}
	else
		ft_putstr_fd(": ", 2);
}

void	is_error(int error_type)
{
	if (error_type == 0)
	{
		ft_putstr_fd("❌ Error: Invalid number of arguments.\n", 2);
		ft_putstr_fd("📖 Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		ft_putstr_fd("💡 Example: ./pipex infile \"ls -l\" \"wc -l\" outfile\n", 2);
		ft_putstr_fd("🔄 This simulates: < infile cmd1 | cmd2 > outfile\n", 2);
	}
	if (error_type == 1)
	{
		ft_putstr_fd("❌ Error: PATH environment variable not found.\n", 2);
		ft_putstr_fd("💡 Tip: Check your shell environment settings.\n", 2);
	}
	if (error_type == 2)
	{
		ft_putstr_fd("❌ Error: Failed to create pipe file descriptors.\n", 2);
		ft_putstr_fd("💡 Tip: System may be out of file descriptors.\n", 2);
	}
	if (error_type == 3)
	{
		ft_putstr_fd("❌ Error: Fork process creation failed.\n", 2);
		ft_putstr_fd("💡 Tip: System may be out of processes or memory.\n", 2);
	}
	if (error_type == 4)
	{
		ft_putstr_fd("❌ Error: Cannot open input file.\n", 2);
		ft_putstr_fd("💡 Tip: Check if file exists and has read permissions.\n", 2);
	}
	if (error_type == 5)
	{
		ft_putstr_fd("❌ Error: Cannot create or write to output file.\n", 2);
		ft_putstr_fd("💡 Tip: Check directory permissions and disk space.\n", 2);
	}
	if (error_type == 6)
	{
		ft_putstr_fd("❌ Error: Command execution failed.\n", 2);
		ft_putstr_fd("💡 Tip: Check if command exists and has execute permissions.\n", 2);
	}
	if (error_type == 7)
	{
		ft_putstr_fd("❌ Error: Failed to duplicate file descriptor.\n", 2);
		ft_putstr_fd("💡 Tip: File descriptor management issue.\n", 2);
	}
	if (error_type == 8)
	{
		ft_putstr_fd("❌ Error: Second fork process creation failed.\n", 2);
		ft_putstr_fd("💡 Tip: System resource limitation.\n", 2);
	}
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
