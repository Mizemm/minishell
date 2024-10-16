/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:26 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/30 09:39:55 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

char *get_env_value(t_env *env_list, char *name)
{
    t_env *current = env_list;
    while (current)
    {
        if (ft_strcmp(current->name, name) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

void update_env_value(t_env **env, char *name, char *value)
{
    t_env *current = *env;
    while (current)
    {
        if (ft_strcmp(current->name, name) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        current = current->next;
    }
}

int exec_cd(t_main *main)
{
    char *dir;
    char old_cwd[1024];
    char new_cwd[1024];

    if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
        error("getcwd error");
    if (main->cmd->arg_count < 2)
    {
        dir = get_env_value(main->env, "HOME");
        if (!dir)
            error("cd error: HOME not set");
    }
    else if (ft_strcmp(main->cmd->args[1], "-") == 0)
    {
        dir = get_env_value(main->env, "OLDPWD");
        if (!dir)
            error("cd: OLDPWD not set");
        printf("%s\n", dir);
    }
    else 
        dir = main->cmd->args[1];
    if (chdir(dir) != 0)
        error("cd error");
    update_env_value(&main->env, "OLDPWD", old_cwd);
    if (getcwd(new_cwd, sizeof(new_cwd)) == NULL)
        error("getcwd error");
    update_env_value(&main->env, "PWD", new_cwd);
    return 0;
}

