/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:26 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/31 17:58:16 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env_list, char *name)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	update_env_value(t_env **env, char *name, char *value)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

int	exec_cd(t_main *main, t_cmd *cmd)
{
	if (getcwd(main->old_cwd, sizeof(main->old_cwd)) == NULL)
		return (error("getcwd error"), 1);
	if (!cmd->args[1])
	{
		main->dir = get_env_value(main->env, "HOME");
		if (!main->dir)
			return (error("cd error: HOME not set"), 1);
	}
	else if (ft_strcmp(main->cmd->args[1], "-") == 0)
	{
		main->dir = get_env_value(main->env, "OLDPWD");
		if (!main->dir)
			return (error("cd: OLDPWD not set"), 1);
		printf("%s\n", main->dir);
	}
	else
		main->dir = main->cmd->args[1];
	if (chdir(main->dir) != 0)
		return (error("minishin: cd: No such file or directory"), 1);
	update_env_value(&main->env, "OLDPWD", main->old_cwd);
	if (getcwd(main->new_cwd, sizeof(main->new_cwd)) == NULL)
		return (error("getcwd error"), 1);
	update_env_value(&main->env, "PWD", main->new_cwd);
	return (0);
}
