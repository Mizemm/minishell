/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:26 by abdennac          #+#    #+#             */
/*   Updated: 2024/08/26 22:55:26 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void update_full_env(t_main *main)
{
	int count = 0;
	t_env *current = main->env;

	while (current)
	{
		count++;
		current = current->next;
	}
	main->full_env = malloc((count + 1) * sizeof(char *));
	if (!main->full_env)
		return; 
	current = main->env;
	for (int i = 0; i < count; i++)
	{
		char *entry = malloc(ft_strlen(current->name) + ft_strlen(current->value) + 2); 
		if (entry)
		{
			sprintf(entry, "%s=%s", current->name, current->value);
			main->full_env[i] = entry;
		}
		current = current->next;
	}
	main->full_env[count] = NULL;
}

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

void update_env_value(t_env *env_list, char *name, char *value)
{
	t_env *current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			current->value = ft_strdup(value);
			return;
		}
		current = current->next;
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
	update_env_value(main->env, "PWD", cwd); // Update PWD
	update_full_env(main);
	return 0;
}
