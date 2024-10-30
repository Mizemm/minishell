/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:35:20 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/29 22:52:08 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void simple_input(t_main *main, t_cmd *cmd)
{
    int fd_in;
    int i;

    if (cmd->heredoc_delimiter)
    {
        fd_in = open("/tmp/heredoc", O_RDONLY);
        if (fd_in < 0)
            error2(main, "Failed to open heredoc", 1);
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
                    error2(main, "Permission denied", 1);
            }
            else
                error2(main, "No such file or directory", 1);
            fd_in = open(cmd->input_file[i], O_RDONLY);
            if (fd_in < 0)
                error2(main, "Failed to open file", 1);
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
}

void simple_output(t_main *main, t_cmd *cmd)
{
    int fd_out;
    t_out *tmp;

    if (cmd->output_files)
    {
        tmp = cmd->output_files;
        while (tmp)
        {
            if (access(tmp->output, F_OK) == 0)
            {
                if (access(tmp->output, W_OK) != 0)
                    error2(main, "Permission denied", 1);
            }
            if (tmp->type == 1)
                fd_out = open(tmp->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else if (tmp->type == 0)
                fd_out = open(tmp->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd_out < 0)
                error2(main, "Failed to open file", 1);
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
            tmp = tmp->next;
        }
    }
}

void simple_cleanup(t_cmd *cmd)
{
	if (cmd->heredoc_delimiter)
		unlink("/tmp/heredoc");
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
void simple_exec(t_main *main)
{
	pid_t pid;
	int status;

	if (check_if_builtin(main->cmd->command))
	{
		// simple_input(main, main->cmd);
		// simple_output(main, main->cmd);
		execute_builtins(main, main->cmd);
		simple_cleanup(main->cmd);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			error2(main, "fork error", 1);
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			simple_input(main, main->cmd);
			simple_output(main, main->cmd);
			if (!main->cmd->path)
				find_path(main, main->cmd);
			execve(main->cmd->path, main->cmd->args, main->full_env);
		}
		else
		{
			waitpid(pid, &status, 0);
		    simple_cleanup(main->cmd);
			if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				status = 128 + WTERMSIG(status);
			main->exit_status = status;
		}
	}
	if (main->cmd->heredoc_delimiter)
		unlink("/tmp/heredoc");
}
