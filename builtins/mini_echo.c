/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:01 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/27 12:34:09 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

int check_flag(char *str)
{
    int i;

    if (!str)
        return (0);
    if (str[0] != '-' || str[1] != 'n')
        return (0);
    i = 1;
    while (str[i] != '\0')
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void exec_echo(t_main *main) //ba9i fiha chi l3ibat
{
    int i = 0;
    int flag_n = 0;

    while (main->cmd->args[++i] && check_flag(main->cmd->args[i]))
        flag_n = 1;
    i = 0;
    while (main->cmd->args[++i])
    {
        if (ft_strcmp(main->cmd->args[i], "-n") && main->cmd->args[i])
            printf("%s", main->cmd->args[i]);
        if (main->cmd->args[i + 1])
            printf("%c", ' ');
    }
    if (!flag_n)
            printf("%c", '\n');
}
