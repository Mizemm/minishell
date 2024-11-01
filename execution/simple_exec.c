/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:35:20 by abdennac          #+#    #+#             */
/*   Updated: 2024/11/02 00:38:46 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	simple_input_utill(t_cmd *cmd, int fd_in, int i)
{
	while (cmd->input_file[++i])
	{
		if (access(cmd->input_file[i], F_OK) == 0)
		{
			if (access(cmd->input_file[i], R_OK) != 0)
				return (error("Permission denied"), 1);
		}
		else
			return (error("No such file or directory"), 1);
		fd_in = open(cmd->input_file[i], O_RDONLY);
		if (fd_in < 0)
			return (error("Failed to open file"), 1);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (0);
}

int	simple_input(t_cmd *cmd)
{
	int	fd_in;
	int	i;

	i = -1;
	if (cmd->heredoc_delimiter)
	{
		fd_in = open("/tmp/heredoc", O_RDONLY);
		if (fd_in < 0)
			return (error("Failed to open heredoc"), 1);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->input_file)
		return (simple_input_utill(cmd, fd_in, i));
	return (0);
}

int	simple_output(t_cmd *cmd)
{
	int		fd_out;
	t_out	*tmp;

	if (cmd->output_files)
	{
		tmp = cmd->output_files;
		while (tmp)
		{
			if (access(tmp->output, F_OK) == 0)
			{
				if (access(tmp->output, W_OK) != 0)
					return (error("Permission denied"), 1);
			}
			if (tmp->type == 1)
				fd_out = open(tmp->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (tmp->type == 0)
				fd_out = open(tmp->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_out < 0)
				return (error("Failed to open file"), 1);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
			tmp = tmp->next;
		}
	}
	return (0);
}

void	exec_simple_command(t_main *main, int status)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error2(main, "fork error", 1);
	else if (pid == 0)
	{
		sig_red(main);
		if (!main->cmd->path)
			find_path(main, main->cmd);
		execve(main->cmd->path, main->cmd->args, main->full_env);
	}
	else
	{
		waitpid(pid, &status, 0);
		simple_cleanup(main->cmd);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
		main->exit_status = status;
		if (main->exit_status == 131)
			ft_putstr_fd("Quit: 3\n", 2);
	}
}

void	simple_exec(t_main *main)
{
	int	status;

	status = 0;
	if (check_if_builtin(main->cmd->command))
	{
		status = simple_input(main->cmd);
		status = simple_output(main->cmd);
		if (status == 0)
			status = execute_builtins(main, main->cmd);
		simple_cleanup(main->cmd);
		main->exit_status = status;
	}
	else 
		exec_simple_command(main, status);
	if (main->cmd->heredoc_delimiter)
		unlink("/tmp/heredoc");
}
