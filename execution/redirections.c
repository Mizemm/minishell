/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:57:53 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/29 21:27:52 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void handle_input_redirection(t_cmd *cmd, t_main *main, int *prev_pipe_fd, int file_count)
{
    int fd_in;
    int i;

    if (prev_pipe_fd[0] != -1)
    {
        dup2(prev_pipe_fd[0], STDIN_FILENO);
        close(prev_pipe_fd[0]);
        close(prev_pipe_fd[1]);
    }

    if (cmd->heredoc_delimiter)
    {
        fd_in = open(main->heredoc_files[file_count], O_RDONLY);
        if (fd_in < 0)
        {
            error("Heredoc file open error");
            return;
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }

    if (cmd->input_file)
    {
        i = -1;
        while (cmd->input_file[++i])
        {
            if (access(cmd->input_file[i], F_OK) == 0)
            {
                if (access(cmd->input_file[i], R_OK) != 0)
                {
                    error("Permission denied for input file");
                    return;
                }
            }
            else
            {
                error("Input file not found");
                return;
            }

            fd_in = open(cmd->input_file[i], O_RDONLY);
            if (fd_in < 0)
            {
                error("Input file open error");
                return;
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
    }
}

void handle_output_redirection(t_cmd *cmd, int *pipe_fd)
{
    int fd_out;
    t_out *tmp;

    if (cmd->next)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }
    if (cmd->output_files)
    {
        tmp = cmd->output_files;
        while (tmp)
        {
            if (access(tmp->output, F_OK) == 0)
            {
                if (access(tmp->output, W_OK) != 0)
                    error("Permission denied");
            }
            if (tmp->type == 1)
                fd_out = open(tmp->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else if (tmp->type == 0)
                fd_out = open(tmp->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd_out < 0)
                error("Failed to open file");
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
            tmp = tmp->next;
        }
    }
}

