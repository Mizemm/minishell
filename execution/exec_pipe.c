/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:38:03 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/31 16:47:33 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	handle_pipe_fd(t_main *main, t_cmd *cmd, int *pipe_fd)
{
	if (main->prev_pipe_fd[0] != -1)
	{
		close(main->prev_pipe_fd[0]);
		close(main->prev_pipe_fd[1]);
	}
	if (cmd->next)
	{
		main->prev_pipe_fd[0] = pipe_fd[0];
		main->prev_pipe_fd[1] = pipe_fd[1];
	}
}

void	pipe_loop(t_main *main, t_cmd *cmd, pid_t pid)
{
	int		pipe_fd[2];
	int		i;

	i = 0;
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
			child_exec(main, cmd, main->prev_pipe_fd, pipe_fd);
		else
		{
			main->child_pids[i++] = pid;
			handle_pipe_fd(main, cmd, pipe_fd);
		}
		cmd = cmd->next;
	}
}

void	pipe_exec_with_redirection(t_main *main)
{
	t_cmd	*cmd;
	pid_t	pid;

	pid = 0;
	main->prev_pipe_fd[0] = -1;
	main->prev_pipe_fd[1] = -1;
	cmd = main->cmd;
	main->child_pids = malloc(sizeof(pid_t) * count_commands(cmd));
	main->file_count = -1;
	pipe_loop(main, cmd, pid);
	close_fds(main, main->prev_pipe_fd);
	catch_signal(main->child_pids, main);
	free(main->child_pids);
	unlink_files(main, main->file_count);
}
