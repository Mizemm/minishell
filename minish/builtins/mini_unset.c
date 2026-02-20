/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:01:48 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/30 17:20:06 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_node(t_env **head, t_env *node_to_free)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (current == node_to_free)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	exec_unset(t_main *main, t_cmd *cmd)
{
	t_env	*tmp1;
	int		i;

	i = 0;
	while (cmd->args[++i])
	{
		if (ft_strchr(cmd->args[i], '='))
			return (error("unset: not a valid identifier"), 1);
		tmp1 = main->env;
		while (tmp1)
		{
			if (ft_strcmp(tmp1->name, cmd->args[i]) == 0)
			{
				free_env_node(&main->env, tmp1);
				break ;
			}
			tmp1 = tmp1->next;
		}
	}
	return (0);
}
