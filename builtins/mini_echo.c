/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:01 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/23 11:25:57 by abdennac         ###   ########.fr       */
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

    while (++i < main->cmd->arg_count && check_flag(main->cmd->args[i]))
        flag_n = 1;
    // Print argument, separated by space.
    while (i < main->cmd->arg_count)
    {
        printf("%s", main->cmd->args[i]);
        if (i < main->cmd->arg_count - 1)
            printf("%c", ' ');
        i++;
    }
    // Print a newline if the -n flag was not used.
    if (!flag_n)
            printf("%c", '\n');
}
