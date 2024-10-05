/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncoco.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:39:36 by mizem             #+#    #+#             */
/*   Updated: 2024/09/29 18:45:00 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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