/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:09:31 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/29 11:10:26 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void add_old_pwd(t_main *main)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    new->name = ft_strdup("OLDPWD");
    new->value = ft_strdup(getcwd(NULL, 0));
    new->next = NULL;
    ft_lstadd_back_env(&main->env, new);
}

void add_pwd(t_main *main)
{
    t_env *new;

    new = malloc(sizeof(t_env));
    new->name = ft_strdup("PWD");
    new->value = ft_strdup(getcwd(NULL, 0));
    new->next = NULL;
    ft_lstadd_back_env(&main->env, new);
}

int exec_env(t_main *main)
{
    t_env *env;
    char *pwd;

    if (!main->env)
    {
        add_old_pwd(main);
        add_pwd(main);
    }

    env = main->env;
    pwd = NULL;
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
    return (0);
}
