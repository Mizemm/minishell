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
	exec_echo(cmd, 0);
	// execve(cmd->path, cmd->args, cmd->environment);
}

void setup_redirections(t_cmd *cmd, int prev_pipe[2], int curr_pipe[2]) 
{
    int fd;
    int pipefd[2];

    if (cmd->input_file) 
    {
        fd = open(cmd->input_file, O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
    } 
    else if (prev_pipe[0] != -1) 
    {
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }
    if (cmd->output_file) 
    {
        fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    } 
    else if (cmd->append_file) 
    {
        fd = open(cmd->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    } 
    else if (cmd->pipe_out) 
    {
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[0]);
        close(curr_pipe[1]);
    }
    if (cmd->heredoc_content) 
    {
		//ba9i
    }
}


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
			setup_redirections(commands, prev_pipe, curr_pipe);
			execute_single_command(commands);
		}
		commands = commands->next;
	}
}
