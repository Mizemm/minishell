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

void update_full_env(t_cmd *cmd)
{
	int count = 0;
	t_env *current = cmd->env;

	// Count the number of environment variables
	while (current)
	{
		count++;
		current = current->next;
	}
	// Free the old full_env if necessary
	// if (cmd->full_env)
	// 	free(cmd->full_env);
	// Allocate space for the new full_env array
	cmd->full_env = malloc((count + 1) * sizeof(char *));
	if (!cmd->full_env)
		return; // Handle allocation failure
	// Populate the full_env array
	current = cmd->env;
	for (int i = 0; i < count; i++)
	{
		char *entry = malloc(strlen(current->name) + strlen(current->value) + 2); // +2 for '=' and '\0'
		if (entry)
		{
			sprintf(entry, "%s=%s", current->name, current->value);
			cmd->full_env[i] = entry;
		}
		current = current->next;
	}
	cmd->full_env[count] = NULL; // Null-terminate the array
}

char *get_env_value(t_env *env_list, const char *name)
{
	t_env *current = env_list;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
			return current->value;
		current = current->next;
	}
	return NULL;
}

void update_env_value(t_env *env_list, const char *name, const char *value)
{
	t_env *current = env_list;
	while (current)
	{
		if (strcmp(current->name, name) == 0)
		{
			current->value = strdup(value);
			return;
		}
		current = current->next;
	}
}

int exec_cd(t_cmd *cmd)
{
	char *dir;
	char cwd[1024];

	if (cmd->arg_count < 2)
	{
		dir = get_env_value(cmd->env, "HOME");
		if (!dir)
			error("cd error: HOME not set");
	}
	else
		dir = cmd->args[1];
	if (chdir(dir) != 0) // change directory
		error("cd error");
	if (getcwd(cwd, sizeof(cwd)) == NULL) // Get new directory
		error("getcwd error");
	update_env_value(cmd->env, "PWD", cwd); // Update PWD
	update_full_env(cmd);
	return 0;
}
