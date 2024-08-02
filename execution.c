/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:17:07 by abdennac          #+#    #+#             */
/*   Updated: 2024/08/02 15:11:14 by abdennac         ###   ########.fr       */
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
void execute_command(t_cmd *commands)
{
	if (commands->pipe_out > 0)
		execute_single_command(commands);
}