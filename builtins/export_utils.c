/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:06:20 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/04 21:51:02 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

int ft_is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
int check_export(char **split)
{
	int i;
	
	i = 0;
	if (split[0][0] == '=' || !ft_is_alpha(split[0][0]))
		return (1);
	return (0);
}

