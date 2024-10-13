/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 11:10:51 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/13 22:34:38 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void simple_input(t_cmd *cmd)
{
	int fd_in;
	int i;

	if (cmd->heredoc_delimiter)
	{
		fd_in = open("/tmp/heredoc", O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}

	if (cmd->input_file)
	{
		i = -1;
		while (cmd->input_file[++i])
			fd_in = open(cmd->input_file[i], O_RDONLY);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}

void simple_output(t_cmd *cmd)
{
	int fd_out;
	int i;

	if (cmd->output_file)
	{
		i = -1;
		while (cmd->output_file[++i])
			fd_out = open((cmd->output_file[i]), O_WRONLY | O_CREAT, 0644);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	else if (cmd->append_file)
	{
		fd_out = open(*(cmd->append_file), O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void simple_cleanup(t_cmd *cmd)
{
	if (cmd->heredoc_delimiter)
		unlink("/tmp/heredoc0");
	if (cmd->stdin_backup != -1)
	{
		dup2(cmd->stdin_backup, STDIN_FILENO);
		close(cmd->stdin_backup);
	}
	if (cmd->stdout_backup != -1)
	{
		dup2(cmd->stdout_backup, STDOUT_FILENO);
		close(cmd->stdout_backup);
	}
}

void simple_exec(t_main *main)
{
	pid_t pid;

	if (check_if_builtin(main->cmd->command))
	{
		simple_input(main->cmd);
		simple_output(main->cmd);
		execute_builtins(main);
		simple_cleanup(main->cmd);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			error("fork error");
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			simple_input(main->cmd);
			simple_output(main->cmd);
			if (!main->cmd->path)
				error("Command not found\n");
			execve(main->cmd->path, main->cmd->args, main->full_env);
		}
		else
			waitpid(pid, NULL, 0);
		if (main->cmd->heredoc_delimiter)
			unlink("/tmp/heredoc0");
	}
}
