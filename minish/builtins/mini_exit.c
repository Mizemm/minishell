/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:03:20 by abdennac          #+#    #+#             */
/*   Updated: 2024/11/01 21:18:16 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	f_atoi(char *str)
{
	long	sum;
	long	sign;
	long	found;

	sum = 0;
	sign = 1;
	found = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
		|| *str == '\r')
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

void	print_error(t_cmd *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

int	exec_exit(t_cmd *cmd)
{
	int	exit_status;
	int	i;

	exit_status = 0;
	ft_putstr_fd("exit\n", 2);
	if (cmd->args[1])
	{
		i = -1;
		while (cmd->args[1][++i])
		{
			if (i == 0 && (cmd->args[1][i] == '-' || cmd->args[1][i] == '+') 
				&& cmd->args[1][i + 1])
				continue ;
			if ((cmd->args[1][i] < '0' || cmd->args[1][i] > '9')
				|| f_atoi(cmd->args[1]) > LLONG_MAX)
				print_error(cmd);
		}
		exit_status = ft_atoi(cmd->args[1]);
		if (cmd->args[2])
			return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	}
	exit(exit_status);
	return (0);
}
