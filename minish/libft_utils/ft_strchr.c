/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:54:51 by mizem             #+#    #+#             */
/*   Updated: 2024/09/30 13:32:53 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (s[i] == '\0' && (char)c == '\0')
		return ((char *)s + i);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
		if (s[i] == '\0' && (char)c == '\0')
			return ((char *)s + i);
	}
	return (NULL);
}
