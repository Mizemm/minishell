/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:06:20 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/30 19:05:07 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	check_export(char **split)
{
	if (split[0][0] == '=' || !ft_is_alpha(split[0][0]))
		return (1);
	return (0);
}

int	is_exported(t_main *main, char *name)
{
	t_env	*tmp;

	tmp = main->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	print_export(t_main *main)
{
	t_env	*tmp1;

	tmp1 = main->env;
	while (tmp1)
	{
		printf("declare -x %s", tmp1->name);
		if (tmp1->value)
			printf("=\"%s\"\n", tmp1->value);
		else
			printf("\n");
		tmp1 = tmp1->next;
	}
}

char	**add_empty(char **split)
{
	char	**new;

	new = malloc(sizeof(char *) * 3);
	new[0] = ft_strdup(split[0]);
	new[1] = ft_strdup("");
	new[2] = NULL;
	return (new);
}
