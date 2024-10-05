/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:24:06 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/05 17:50:11 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstlast2(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd2_back(t_env **head, t_env *new)
{
	t_env *tmp;

	tmp = NULL;	
	if (!head || !new)
		return ;
	else if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		tmp = ft_lstlast2(*head);
		tmp->next = new;
	}	
}

void print_export(t_main *main)
{
	t_env *tmp1;
	t_expo *tmp2;

	tmp1 = main->env;
	tmp2 = main->export;

	while (tmp1)
	{
		printf("declare -x %s=\"%s\"\n", tmp1->name, tmp1->value);
		tmp1 = tmp1->next;
	}
	while (tmp2)
	{
		printf("declare -x %s=\"%s\"\n", tmp2->name, tmp2->value);
		tmp2 = tmp2->next;
	}
}

void add_to_env(t_main *main, char *str)
{
	t_env *new;
	char **split;
	split = ft_split(str, '=');

	new = malloc(sizeof(t_env));
	new->name = ft_strdup(split[0]);
	new->value = ft_strdup(split[1]);
	new->next = NULL;
	ft_lstadd2_back(&main->env, new);
}

void exec_export(t_main *main)
{
	int i;
	if (!main->cmd->args[1])
		print_export(main);
	else if (main->cmd->args[1])
	{
		i = 0;
		while (main->cmd->args[++i])
		{
			if (ft_strchr(main->cmd->args[i], '='))
				add_to_env(main, main->cmd->args[i]);
			else
				add_to_export(main, main->cmd->args[i]);
		}
	}
}
