/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:56:43 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/20 10:46:20 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void print_export(t_main *main)
{
	t_env *tmp1;

	tmp1 = main->env;
	while (tmp1)
	{
		printf("declare -x %s", tmp1->name);
		if (tmp1->value)
			printf("=\"%s\"\n",tmp1->value);
		else
			printf("\n");
		tmp1 = tmp1->next;
	}
}

int is_exported(t_main *main, char *name)
{
	t_env *tmp;
	tmp = main->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void update_value(t_main *main, char **split)
{
	t_env *tmp;

	tmp = main->env;
	if (!split[1])
		return;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, split[0]) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(split[1]);
			break;
		}
		tmp = tmp->next;
	}
}

void add_to_env(t_main *main, char **split)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	new->name = ft_strdup(split[0]);
	if (split[1])
		new->value = ft_strdup(split[1]);
	else 
		new->value = NULL;
	new->next = NULL;
	ft_lstadd_back_env(&main->env, new);
}

int is_valide(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (1);
	}
	return (0);
}

int exec_export(t_main *main, t_cmd *cmd)
{
	int i;
	char **split;
	int flag;

	flag = 0;
	if (!cmd->args[1])
		print_export(main);
	else
	{
		i = 0;
		while (cmd->args[++i])
		{
			if (is_valide(cmd->args[i]))
			{
				error("export: not a valid identifier");
				flag = 1;
			}
			split = ft_split(cmd->args[i], '=');
			if (!check_export(split))
			{
				if (is_exported(main, split[0]))
					update_value(main, split);
				else
					add_to_env(main, split);
			}
			ft_free(split);
		}
	}
	if (flag == 1)
		return (1);
	return (0);
}
