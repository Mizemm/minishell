/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:17:07 by abdennac          #+#    #+#             */
/*   Updated: 2024/08/10 16:04:28 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void execute_single_command(t_cmd *cmd)
{
	if (!cmd->path)
		error("Command not found\n");
	execve(cmd->path, cmd->args, cmd->environment);
}

// setup_redirections(t_cmd *commands,int prev_pipe, int curr_pipe)
// {
	
// }
void execute_command(t_cmd *commands)
{
	int prev_pipe[2] = {-1, -1};
	int curr_pipe[2];
	while (commands)
	{
		if (commands->pipe_out)
			pipe(curr_pipe);
		pid_t pid = fork();
		if (pid == 0)
		{
			// Child process
			// setup_redirections(commands, prev_pipe, curr_pipe);
			execute_single_command(commands);
		}
		commands = commands->next;
	}
}
