/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:03:20 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/17 00:51:01 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

int exec_exit(t_main *main)
{
    int exit_status;

    exit_status = 0;
    ft_putstr_fd("exit\n", 2);
    if (main->cmd->args[1])
    {
        int i = -1;
        while (main->cmd->args[1][++i])
        {
            if (main->cmd->args[1][i] < '0' || main->cmd->args[1][i] > '9')
            {
                ft_putstr_fd("minishell: exit: ", 2);
                ft_putstr_fd(main->cmd->args[1], 2);
                ft_putstr_fd(": numeric argument required\n", 2);
                exit(255);
            }
        }
        exit_status = ft_atoi(main->cmd->args[1]);
        if (main->cmd->args[2])
        {
            ft_putstr_fd("minishell: exit: too many arguments\n", 2);
            return (1);
        }
    }
    exit(exit_status);
    return (0);
}

