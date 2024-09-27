/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:03:20 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/27 12:28:45 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void exec_exit(t_main *main)
{
    int exit_status;

    exit_status = 0;

    printf("exit\n");
    if (main->cmd->args[1])
    {
        int i = -1;
        while (main->cmd->args[1][++i])
        {
            if (main->cmd->args[1][i] < '0' || main->cmd->args[1][i] > '9')
            {
                printf("minishell: exit: %s: numeric argument required\n", main->cmd->args[1]);
                exit(255);
            }
        }
        exit_status = ft_atoi(main->cmd->args[1]);
        if (main->cmd->args[2])
        {
            printf("minishell: exit: too many arguments\n");
            return;
        }
    }

    exit(exit_status);
}

