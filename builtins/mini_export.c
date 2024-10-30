/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:56:43 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/30 19:14:47 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_value(t_main *main, char **split)
{
	t_env	*tmp;

	tmp = main->env;
	if (!split[1])
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, split[0]) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(split[1]);
			break ;
		}
		tmp = tmp->next;
	}
}

void	add_to_env(t_main *main, char **split)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->name = ft_strdup(split[0]);
	if (split[1])
		new->value = ft_strdup(split[1]);
	else
		new->value = NULL;
	new->next = NULL;
	ft_lstadd_back_env(&main->env, new);
}

int	is_valide(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	export_loop(t_main *main, t_cmd *cmd, int i, int flag)
{
	char	**split;

	if (is_valide(cmd->args[i]))
	{
		error("export: not a valid identifier");
		flag = 1;
	}
	split = ft_split(cmd->args[i], '=');
	if (ft_strchr(cmd->args[i], '=') && !split[1])
		split = add_empty(split);
	if (!check_export(split))
	{
		if (is_exported(main, split[0]))
			update_value(main, split);
		else
			add_to_env(main, split);
	}
	ft_free(split);
	return (flag);
}

int	exec_export(t_main *main, t_cmd *cmd)
{
	int		i;
	int		flag;

	flag = 0;
	if (!cmd->args[1])
		print_export(main);
	else
	{
		i = 0;
		while (cmd->args[++i])
			flag = export_loop(main, cmd, i, flag);
	}
	return (flag);
}
