/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:55:01 by abdennac          #+#    #+#             */
/*   Updated: 2024/11/01 21:21:40 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!(str[i] == '\\' && str[i - 1] != '\\'))
			write(1, &str[i], 1);
	}
}

int	check_flag(char *str)
{
	int	i;

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

int	exec_echo(t_cmd *cmd)
{
	int	i;
	int	flag_n;

	i = 0;
	flag_n = 0;
	i = 1;
	while (cmd->args[i] && check_flag(cmd->args[i]))
	{
		flag_n = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_print(cmd->args[i]);
		if (cmd->args[i + 1])
			ft_print(" ");
		i++;
	}
	if (!flag_n)
		printf("\n");
	return (0);
}
