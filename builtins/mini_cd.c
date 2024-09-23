/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:26 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/23 03:46:43 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

char *get_env_value(t_env *env_list, char *name)
{
	t_env *current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return current->value;
		current = current->next;
	}
	return NULL;
}

void update_env_value(t_main *main, char *name, char *value)
{
	while (main->env)
	{
		if (ft_strcmp(main->env->name, name) == 0)
		{
			// printf("old pwd = %s\n", main->env->value);
			free(main->env->value);
			main->env->value = ft_strdup(value);
			return;
		}
		main->env = main->env->next;
	}
}

int exec_cd(t_main *main)
{
	char *dir;
	char cwd[1024];

	if (main->cmd->arg_count < 2)
	{
		dir = get_env_value(main->env, "HOME");
		if (!dir)
			error("cd error: HOME not set");
	}
	else
		dir = main->cmd->args[1];
	if (chdir(dir) != 0) // change directory
		error("cd error");
	if (getcwd(cwd, sizeof(cwd)) == NULL) // Get new directory
		error("getcwd error");
	update_env_value(main, "PWD", cwd); // Update PWD
	return 0;
}
