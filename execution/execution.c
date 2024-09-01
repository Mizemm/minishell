/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:17:07 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/01 01:01:35 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void execute_builtins(t_cmd *cmd)
{
	if (ft_strcmp("echo", cmd->command) == 0)
		exec_echo(cmd);
	else if (ft_strcmp("cd", cmd->command) == 0)
		exec_cd(cmd);
	else if (ft_strcmp("pwd", cmd->command) == 0)
		excec_pwd();
	else if (ft_strcmp("export", cmd->command) == 0)
		return;
	else if (ft_strcmp("unset", cmd->command) == 0)
		return;
	else if (ft_strcmp("env", cmd->command) == 0)
		exec_env(cmd);
	else if (ft_strcmp("exit", cmd->command) == 0)
		return;
}

void execute_single_command(t_cmd *cmd)
{
	if (!cmd->path)
		error("Command not found\n");
	if (!check_if_builtin(cmd->command))
	{
		printf("$$$$$$$$$\n");
		execute_builtins(cmd);
	}
	else
		execve(cmd->path, cmd->args, cmd->full_env);
}

void execute_command(t_cmd *commands)
{
	int prev_pipe[2] = {-1, -1};
	int curr_pipe[2];
	pid_t pid;

	while (commands)
	{
		if (commands->pipe_out)
			pipe(curr_pipe);
		pid = fork();
		if (pid < 0)
			error("fork error");
		else if (pid == 0)
		{
			setup_redirections(commands, prev_pipe, curr_pipe);
			execute_single_command(commands);
		}
		else
		{
			// cleanup(commands, prev_pipe, curr_pipe);
			if (!commands->pipe_out)
				waitpid(pid, NULL, 0);
		}
		if (commands->pipe_out)
		{
			prev_pipe[0] = curr_pipe[0];
			prev_pipe[1] = curr_pipe[1];
		}
		commands = commands->next;
	}
}
