/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:57:53 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/24 11:33:00 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"


void pipe_setup(t_cmd *cmd, int prev_pipe[2], int curr_pipe[2])
{
    int fd_in;
    int fd_out;
    int i;

    cmd->stdin_backup = dup(STDIN_FILENO);
    cmd->stdout_backup = dup(STDOUT_FILENO);
    
    if (prev_pipe[0] != -1)
    {
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }
    if (cmd->pipe_out)
    {
		// printf("setting pipes\n");
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[0]);
        close(curr_pipe[1]);
        cmd->pipe_out = 0;
    }
    // if (cmd->heredoc_content)
    // {
	// 	//ba9i
    // }
}


void pipe_cleanup(t_cmd *cmd, int prev_pipe[2], int curr_pipe[2])
{
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


void redirections_setup(t_cmd *cmd, int prev_pipe[2], int curr_pipe[2])
{
    int fd_in;
    int fd_out;
    int i;

    cmd->pipe_out = 1;
    cmd->stdin_backup = dup(STDIN_FILENO);
    cmd->stdout_backup = dup(STDOUT_FILENO);
    // if (cmd->input_file)
    // {
    //     fd_in = open(*(cmd->input_file), O_RDONLY);
    //     dup2(fd_in, STDIN_FILENO);
    //     close(fd_in);
    // }
    if (prev_pipe[0] != -1)
    {
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }
    // if (cmd->output_file)
    // {
    //     i = -1;
    //     while(cmd->output_file[++i])
    //         fd_out = open((cmd->output_file[i]), O_WRONLY | O_CREAT, 0644);
    //     dup2(fd_out, STDOUT_FILENO);
    //     close(fd_out);
    // }
    // else if (cmd->append_file)
    // {
    //     fd_out = open(cmd->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    //     dup2(fd_out, STDOUT_FILENO);
    //     close(fd_out);
    // }
    if (cmd->pipe_out)
    {
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[0]);
        close(curr_pipe[1]);
        cmd->pipe_out = 0;
    }
    if (cmd->heredoc_content)
    {
		//ba9i
    }
}


/****************************************************************************************/

void simple_redirections(t_cmd *cmd)
{
    int fd_in;
    int fd_out;
    int i;

    cmd->stdin_backup = dup(STDIN_FILENO);
    cmd->stdout_backup = dup(STDOUT_FILENO);
    if (cmd->input_file)
    {
        fd_in = open(*(cmd->input_file), O_RDONLY);
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
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
        fd_out = open(cmd->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}



void simple_cleanup(t_cmd *cmd)
{
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
