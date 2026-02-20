/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:45:55 by abdennac          #+#    #+#             */
/*   Updated: 2024/11/01 23:27:06 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

int	execute_builtins(t_main *main, t_cmd *cmd)
{
	if (ft_strcmp("echo", cmd->command) == 0)
		main->exit_status = exec_echo(cmd);
	else if (ft_strcmp("cd", cmd->command) == 0)
		main->exit_status = exec_cd(main, cmd);
	else if (ft_strcmp("pwd", cmd->command) == 0)
		main->exit_status = excec_pwd();
	else if (ft_strcmp("export", cmd->command) == 0)
		main->exit_status = exec_export(main, cmd);
	else if (ft_strcmp("unset", cmd->command) == 0)
		main->exit_status = exec_unset(main, cmd);
	else if (ft_strcmp("env", cmd->command) == 0)
		main->exit_status = exec_env(main);
	else if (ft_strcmp("exit", cmd->command) == 0)
		main->exit_status = exec_exit(cmd);
	return (main->exit_status);
}

int	check_if_builtin(char *str)
{
	if (!str)
		return (0);
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

int	count_commands(t_cmd *cmd)
{
	int		count;
	t_cmd	*tmp;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
