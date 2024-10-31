/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:38:03 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/31 02:41:08 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(t_main *main, int *prev_pipe_fd)
{
	if (prev_pipe_fd[0] != -1)
	{
		close(prev_pipe_fd[0]);
		close(prev_pipe_fd[1]);
	}
	if (main->cmd->stdin_backup != -1)
	{
		dup2(main->cmd->stdin_backup, STDIN_FILENO);
		close(main->cmd->stdin_backup);
	}
	if (main->cmd->stdout_backup != -1)
	{
		dup2(main->cmd->stdout_backup, STDOUT_FILENO);
		close(main->cmd->stdout_backup);
	}
}

void	unlink_files(t_main *main, int file_count)
{
	file_count = -1;
	if (main->cmd->heredoc_delimiter)
	{
		while (main->heredoc_files[++file_count])
			unlink(main->heredoc_files[file_count]);
	}
}

void	catch_signal(pid_t *child_pids, t_main *main)
{
	int	i;
	int	cmd_count;

	cmd_count = count_commands(main->cmd);
	i = -1;
	while (++i < cmd_count)
	{
		waitpid(child_pids[i], &(main->exit_status), 0);
		if (WIFEXITED(main->exit_status))
			main->exit_status = WEXITSTATUS(main->exit_status);
		else if (WIFSIGNALED(main->exit_status))
			main->exit_status = 128 + WTERMSIG(main->exit_status);
	}
}

void	pipe_exec_with_redirection(t_main *main)
{
	t_cmd	*cmd;
	pid_t	pid;
	pid_t	*child_pids;
	int		pipe_fd[2];
	int		prev_pipe_fd[2];
	int		i;

	prev_pipe_fd[0] = -1;
	prev_pipe_fd[1] = -1;
	cmd = main->cmd;
	child_pids = malloc(sizeof(pid_t) * count_commands(cmd));
	i = 0;
	main->file_count = -1;
	while (cmd)
	{
		if (cmd->heredoc_delimiter)
			main->file_count++;
		if (cmd->next && pipe(pipe_fd) < 0)
			error2(main, "pipe error", 1);
		pid = fork();
		if (pid < 0)
		{
			error("fork error");
			break ;
		}
		else if (pid == 0)
			child_exec(main, cmd, prev_pipe_fd, pipe_fd);
		else
		{
			child_pids[i++] = pid;
			if (prev_pipe_fd[0] != -1)
			{
				close(prev_pipe_fd[0]);
				close(prev_pipe_fd[1]);
			}
			if (cmd->next)
			{
				prev_pipe_fd[0] = pipe_fd[0];
				prev_pipe_fd[1] = pipe_fd[1];
			}
		}
		cmd = cmd->next;
	}
	close_fds(main, prev_pipe_fd);
	catch_signal(child_pids, main);
	free(child_pids);
	unlink_files(main, main->file_count);
}
