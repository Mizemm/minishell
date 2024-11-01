/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 22:10:31 by abdennac          #+#    #+#             */
/*   Updated: 2024/11/01 23:12:13 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_single_command(t_main *main, t_cmd *cmd)
{
	if (check_if_builtin(cmd->command))
	{
		execute_builtins(main, cmd);
		exit(main->exit_status);
	}
	else
	{
		if (!cmd->path)
			find_path(main, cmd);
		execve(cmd->path, cmd->args, main->full_env);
	}
}

void	child_exec(t_main *main, t_cmd *cmd, int *prev_pipe_fd, int *pipe_fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_output_redirection(cmd, pipe_fd);
	handle_input_redirection(cmd, main, prev_pipe_fd);
	execute_single_command(main, cmd);
	main->exit_status = 127;
	exit(127);
}

void	execute_command(t_main *main)
{
	main->cmd->stdin_backup = dup(STDIN_FILENO);
	main->cmd->stdout_backup = dup(STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);

	if (!main->cmd->next && main->cmd)
		simple_exec(main);
	else if (main->cmd)
		pipe_exec_with_redirection(main);

}
