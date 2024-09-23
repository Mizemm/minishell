/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:17:07 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/23 05:24:28 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void error(char *str)
{
	printf("%s\n", str);
	exit(1);
}
int check_if_builtin(char *str)
{
	if (ft_strcmp("echo", str) == 0)
		return (0);
	if (ft_strcmp("cd", str) == 0)
		return (0);
	if (ft_strcmp("pwd", str) == 0)
		return (0);
	if (ft_strcmp("export", str) == 0)
		return (0);
	if (ft_strcmp("unset", str) == 0)
		return (0);
	if (ft_strcmp("env", str) == 0)
		return (0);
	if (ft_strcmp("exit", str) == 0)
		return (0);
	return (1);
}

void execute_builtins(t_main *main)
{
	if (ft_strcmp("echo", main->cmd->command) == 0)
		exec_echo(main);
	else if (ft_strcmp("cd", main->cmd->command) == 0)
		exec_cd(main);
	else if (ft_strcmp("pwd", main->cmd->command) == 0)
		excec_pwd();
	else if (ft_strcmp("export", main->cmd->command) == 0)
		return;
	else if (ft_strcmp("unset", main->cmd->command) == 0)
		return;
	else if (ft_strcmp("env", main->cmd->command) == 0)
		exec_env(main);
	else if (ft_strcmp("exit", main->cmd->command) == 0)
		return;
}

void execute_single_command(t_main *main)
{
	if (!main->cmd->path)
		error("Command not found\n");
	if (!check_if_builtin(main->cmd->command))
	{
		// printf("$$$$$$$$$\n");
		execute_builtins(main);
	}
	else
		execve(main->cmd->path, main->cmd->args, main->full_env);
}

void execute_command(t_main *main)
{
	int prev_pipe[2] = {-1, -1};
	int curr_pipe[2];
	pid_t pid;

	if (!check_if_builtin(main->cmd->command) && !main->cmd->input_file &&
			!main->cmd->output_file && !main->cmd->pipe_out)
	{
		printf("******* exec in parent*********\n");
		execute_builtins(main);
	}
	else
	{
		printf("******* exec in child*********\n");
		while (main->cmd)
		{
			if (main->cmd->pipe_out)
				pipe(curr_pipe);
			pid = fork();
			if (pid < 0)
				error("fork error");
			else if (pid == 0)
			{
				setup_redirections(main->cmd, prev_pipe, curr_pipe);
				execute_single_command(main);
			}
			else
			{
				// cleanup(main->cmd, prev_pipe, curr_pipe);
				if (!main->cmd->pipe_out)
					waitpid(pid, NULL, 0);
			}
			if (main->cmd->pipe_out)
			{
				prev_pipe[0] = curr_pipe[0];
				prev_pipe[1] = curr_pipe[1];
			}
			main->cmd = main->cmd->next;
		}
	}
}
