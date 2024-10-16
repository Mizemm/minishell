/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                 +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/08/01 10:17:07 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/26 11:22:35 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void	execute_single_command(t_main *main, t_cmd *cmd)
{
	if (check_if_builtin(cmd->command))
		execute_builtins(main, cmd);
	else
		execve(cmd->path, cmd->args, main->full_env);
}

void	pipe_exec_with_redirection(t_main *main)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		prev_pipe_fd[2] = {-1, -1};
	t_cmd	*cmd;
	int		cmd_count;
	pid_t	*child_pids;
	int		i;
	int		file_count;

	cmd = main->cmd;
	cmd_count = count_commands(cmd);
	child_pids = malloc(sizeof(pid_t) * cmd_count);
	i = 0;
	file_count = -1;
	while (cmd)
	{
		if (cmd->heredoc_delimiter)
			file_count++;
		if (cmd->next && pipe(pipe_fd) < 0)
			error("pipe error");
		pid = fork();
		if (pid < 0)
			error("fork error");
		else if (pid == 0) // Child process
		{
			signal(SIGINT, SIG_DFL);
			handle_output_redirection(cmd, pipe_fd);
			handle_input_redirection(cmd, main, prev_pipe_fd, file_count);
			execute_single_command(main, cmd);
			exit(0);
		}
		else // Parent process
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
	if (prev_pipe_fd[0] != -1) // Close remaining pipes
	{
		close(prev_pipe_fd[0]);
		close(prev_pipe_fd[1]);
	}
	i = -1;
	while (++i < cmd_count) // Wait for all child processes to finish
		waitpid(child_pids[i], NULL, 0);
	free(child_pids);
	if (main->cmd->heredoc_delimiter)
	{
		while (main->heredoc_files[++file_count])
			unlink(main->heredoc_files[file_count]);
	}
}

// void	execute_command(t_main *main)
// {
// 	main->cmd->stdin_backup = dup(STDIN_FILENO);
// 	main->cmd->stdout_backup = dup(STDOUT_FILENO);

// 		if (!main->cmd->next && main->cmd)
// 			simple_exec(main);
// 		else if (main->cmd)
// 			pipe_exec_with_redirection(main);
// }

void	execute_command(t_main *main)
{
	t_cmd	*cmd;
	cmd = main->cmd;
	signal(SIGINT, SIG_IGN);
	main->cmd->stdin_backup = dup(STDIN_FILENO);
	main->cmd->stdout_backup = dup(STDOUT_FILENO);
	while (main->cmd)
	{
		if (!main->cmd->next)
		{
			dprintf(2, "%s\n", main->cmd->command);
			simple_exec(main);
		}
		else
		{
			pipe_exec_with_redirection(main);
			// Skip to the end of the command list
			while (main->cmd->next)
				main->cmd = main->cmd->next;
		}
		main->cmd = main->cmd->next;
	}
	main->cmd = cmd;
}
