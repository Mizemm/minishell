/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:01 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/30 10:41:00 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

void ft_print(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if(!(str[i] == '\\' && str[i - 1] != '\\'))
            printf("%c", str[i]);
    }
}

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

void exec_echo(t_main *main)
{
    int i = 1;
    int flag_n = 0;

    while (main->cmd->args[i] && check_flag(main->cmd->args[i]))
    {
        flag_n = 1;
        i++;
    }

    while (main->cmd->args[i])
    {
        ft_print(main->cmd->args[i]);
        if (main->cmd->args[i + 1])
            printf(" ");
        i++;
    }

    if (!flag_n)
        printf("\n");
}

