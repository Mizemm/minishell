/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:41:04 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/29 11:12:45 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

char *path_split(char *str, char c)
{
	int i;
	char *tmp;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0 && str[i] != c)
		i--;
	tmp = ft_strdup(str + i + 1);
	free(str);
	return (tmp);
}

void fix_path(t_cmd *cmd)
{
	if (ft_strchr(cmd->command, '/'))
	{
		cmd->path = ft_strdup(cmd->command);
		cmd->command = path_split(cmd->command, '/');
	}
	else
	{
		cmd->path = getcwd(cmd->path, 0);
		cmd->path = ft_strjoin(cmd->path, "/");
		cmd->path = ft_strjoin(cmd->path, cmd->command);
	}
}

void find_path(t_main *main, t_cmd *cmd)
{
	t_env *tmp; 
	int i = 0;
	tmp = main->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			i = 1;
		tmp = tmp->next;
	}
	if (i == 1)
	{
		fix_path(cmd);
		if (access(cmd->path, F_OK) != 0)
			error2(main, "no such file or directory", 127);
		else if (access(cmd->path, X_OK) != 0)
			error2(main, "Command not found", 127);
		else
			error2(main, "is a directory", 127);
	}
	else
	{
		fix_path(cmd);
		if (access(cmd->path, F_OK) != 0)
			error2(main, "no such file or directory", 127);
		else if (access(cmd->path, X_OK) != 0)
			error2(main, "permission denied", 126);
	}
}
