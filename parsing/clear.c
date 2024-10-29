/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:15:50 by mizem             #+#    #+#             */
/*   Updated: 2024/10/29 21:37:31 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear(t_cmd *cmd, char *line)
{
	if (cmd)
		clear_cmd_list(cmd);
	if (*line)
		free(line);
}

void	clear_all(t_main **main)
{
	while ((*main)->env)
	{
		if ((*main)->env->name)
			free((*main)->env->name);
		if ((*main)->env->value)
			free((*main)->env->value);
		free((*main)->env);
		(*main)->env = (*main)->env->next;
	}
	(*main)->exit_status = 0;
	free(*main);
	*main = NULL;
}
