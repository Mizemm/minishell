/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:09:31 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/03 17:50:27 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void exec_env(t_main *main)
{
    t_env *env = main->env;
    char *pwd = NULL;

    while (env)
    {
        if (ft_strcmp(env->name, "PWD") == 0)
            pwd = env->value;
        env = env->next;
    }

    env = main->env;
    while (env)
    {
        if (ft_strcmp(env->name, "OLDPWD") == 0 &&
				pwd && ft_strcmp(env->value, pwd) == 0)
            env = env->next;
        if (env->value)
            printf("%s=%s\n", env->name, env->value);
        env = env->next;
    }
}
