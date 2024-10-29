/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:03:20 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/29 12:39:39 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

long	f_atoi(char *str)
{
	long	sum;
	long	sign;
	long	found;

	sum = 0;
	sign = 1;
	found = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && found)
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * 10 + *str - '0';
		else
			found = 0;
		str++;
	}
	return (sign * sum);
}

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
            if ((main->cmd->args[1][i] < '0' || main->cmd->args[1][i] > '9') || f_atoi(main->cmd->args[1]) > INT_MAX)
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

