/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:17:07 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/24 11:26:37 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void execute_single_command(t_main *main)
{
	if (check_if_builtin(main->cmd->command))
		execute_builtins(main);
	else
		execve(main->cmd->path, main->cmd->args, main->full_env);
}

void pipe_exec(t_main *main)
{
	pid_t pid;

	int prev_pipe[2] = {-1, -1};
	int curr_pipe[2];

	if (main->cmd->pipe_out)
		pipe(curr_pipe);
	pid = fork();
	if (pid < 0)
		error("fork error");
	else if (pid == 0)
	{
		if (main->cmd->input_file || main->cmd->output_file || main->cmd->append_file)
			redirections_setup(main->cmd, prev_pipe, curr_pipe);
		else
			pipe_setup(main->cmd, prev_pipe, curr_pipe);
		execute_single_command(main);
	}
	else
	{
		pipe_cleanup(main->cmd, prev_pipe, curr_pipe);
		if (!main->cmd->pipe_out)
			waitpid(pid, NULL, 0);
	}
	if (main->cmd->pipe_out)
	{
		prev_pipe[0] = curr_pipe[0];
		prev_pipe[1] = curr_pipe[1];
	}
}

/***********************************************************************************/

void simple_exec(t_main *main)
{
	pid_t pid;

	if (check_if_builtin(main->cmd->command))
	{
		simple_redirections(main->cmd);
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
			simple_redirections(main->cmd);
			if (!main->cmd->path)
				error("Command not found\n");
			execve(main->cmd->path, main->cmd->args, main->full_env);
		}
		else
			waitpid(pid, NULL, 0);
	}
}

void execute_command(t_main *main)
{
	while (main->cmd)
	{
		printf("pipe out : %d\n", main->cmd->pipe_out);
		main->cmd->pipe_out = 1;
		if (!main->cmd->pipe_out)
		{
			simple_exec(main);
		}
		else
		{
			printf("\n********\n\n");
			pipe_exec(main);
		}
		main->cmd = main->cmd->next;
	}
}
