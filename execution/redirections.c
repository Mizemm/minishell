/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:57:53 by abdennac          #+#    #+#             */
/*   Updated: 2024/11/01 01:52:23 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_redirection_helper(t_cmd *cmd, int fd_in)
{
	int	i;

	if (cmd->input_file)
	{
		i = -1;
		while (cmd->input_file[++i])
		{
			if (access(cmd->input_file[i], F_OK) == 0)
			{
				if (access(cmd->input_file[i], R_OK) != 0)
					return (error("Permission denied"));
			}
			else
				return (error("Input file not found"));
			fd_in = open(cmd->input_file[i], O_RDONLY);
			if (fd_in < 0)
				return (error("Input file open error"));
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
	}
}

void	handle_input_redirection(t_cmd *cmd, t_main *main, int *prev_pipe_fd)
{
	int	fd_in;

	fd_in = -1;
	if (prev_pipe_fd[0] != -1)
	{
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		close(prev_pipe_fd[0]);
		close(prev_pipe_fd[1]);
	}
	if (cmd->heredoc_delimiter)
	{
		fd_in = open(main->heredoc_files[main->file_count], O_RDONLY);
		if (fd_in < 0)
			return (error("Heredoc file open error"));
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	input_redirection_helper(cmd, fd_in);
}

void	pipe_help(t_cmd *cmd, int *pipe_fd)
{
	if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	handle_output_redirection(t_cmd *cmd, int *pipe_fd)
{
	int		fd_out;
	t_out	*tmp;

	pipe_help(cmd, pipe_fd);
	if (cmd->output_files)
	{
		tmp = cmd->output_files;
		while (tmp)
		{
			if (access(tmp->output, F_OK) == 0)
			{
				if (access(tmp->output, W_OK) != 0)
					error("Permission denied");
			}
			if (tmp->type == 1)
				fd_out = open(tmp->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (tmp->type == 0)
				fd_out = open(tmp->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_out < 0)
				error("Failed to open file");
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			tmp = tmp->next;
		}
	}
}
