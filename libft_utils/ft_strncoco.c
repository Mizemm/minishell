/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncoco.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:39:36 by mizem             #+#    #+#             */
/*   Updated: 2024/10/30 17:03:38 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

char	*ft_strncoco(char *str, int size)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc((size + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (i < size && str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
