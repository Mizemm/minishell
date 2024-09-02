/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:09:31 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/02 01:04:33 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exec_env(t_main *main)
{
	int	i;
	t_env *env = main->env;
	
	i = -1;
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
