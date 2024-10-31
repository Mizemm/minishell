/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:15:50 by mizem             #+#    #+#             */
/*   Updated: 2024/10/31 22:22:34 by abdennac         ###   ########.fr       */
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
	int	i;

	i = -1;
	while ((*main)->env)
	{
		if ((*main)->env->name)
			free((*main)->env->name);
		if ((*main)->env->value)
			free((*main)->env->value);
		free((*main)->env);
		(*main)->env = (*main)->env->next;
	}
	if ((*main)->heredoc_files)
	{
		while ((*main)->heredoc_files[++i])
		{
			free((*main)->heredoc_files[i]);
		}
		free((*main)->heredoc_files);
		(*main)->heredoc_files = NULL;
	}
	(*main)->exit_status = 0;
	free(*main);
	*main = NULL;
}
