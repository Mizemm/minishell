/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:57:53 by abdennac          #+#    #+#             */
/*   Updated: 2024/08/27 10:42:46 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void setup_redirections(t_cmd *cmd, int prev_pipe[2], int curr_pipe[2])
{
    int fd;
    int pipefd[2];

    cmd->stdin_backup = dup(STDIN_FILENO);
    cmd->stdout_backup = dup(STDOUT_FILENO);
    
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
        fd = open(cmd->output_file, O_WRONLY | O_CREAT, 0644);
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

void cleanup(t_cmd *cmd, int prev_pipe[2], int curr_pipe[2])
{
    // Restore the original STDIN and STDOUT
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

    if (prev_pipe[0] != -1) 
    {
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }
    if (curr_pipe[0] != -1) 
    {
        close(curr_pipe[0]);
        close(curr_pipe[1]);
    }
}
