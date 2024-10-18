/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:45:55 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/18 01:29:55 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void execute_builtins(t_main *main, t_cmd *cmd)
{
	if (ft_strcmp("echo", cmd->command) == 0)
		main->exit_status = exec_echo(cmd);
	else if (ft_strcmp("cd", main->cmd->command) == 0)
		main->exit_status = exec_cd(main);
	else if (ft_strcmp("pwd", main->cmd->command) == 0)
		main->exit_status = excec_pwd();
	else if (ft_strcmp("export", main->cmd->command) == 0)
		main->exit_status = exec_export(main);
	else if (ft_strcmp("unset", main->cmd->command) == 0)
		main->exit_status = exec_unset(main);
	else if (ft_strcmp("env", main->cmd->command) == 0)
		main->exit_status = exec_env(main);
	else if (ft_strcmp("exit", main->cmd->command) == 0)
		main->exit_status = exec_exit(main);
}

int check_if_builtin(char *str)
{
	if (ft_strcmp("echo", str) == 0)
		return (1);
	if (ft_strcmp("cd", str) == 0)
		return (1);
	if (ft_strcmp("pwd", str) == 0)
		return (1);
	if (ft_strcmp("export", str) == 0)
		return (1);
	if (ft_strcmp("unset", str) == 0)
		return (1);
	if (ft_strcmp("env", str) == 0)
		return (1);
	if (ft_strcmp("exit", str) == 0)
		return (1);
	return (0);
}
int count_commands(t_cmd *cmd)
{
	int count;
	t_cmd *tmp;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void child_exec(t_main *main, t_cmd *cmd, int *prev_pipe_fd, int file_count, int *pipe_fd)
{
	signal(SIGINT, SIG_DFL);
	handle_output_redirection(cmd, pipe_fd);
	handle_input_redirection(cmd, main, prev_pipe_fd, file_count);
	execute_single_command(main, cmd);
	main->exit_status = 127;
	exit(127);
}