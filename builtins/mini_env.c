/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:09:31 by abdennac          #+#    #+#             */
/*   Updated: 2024/08/31 22:59:23 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exec_env(t_cmd *cmd)
{
	int	i;
	t_env *env = cmd->env;
	
	i = -1;
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
