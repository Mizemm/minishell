/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:13:08 by mizem             #+#    #+#             */
/*   Updated: 2024/08/01 09:47:10 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dst;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	dst = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '/';
	i = 0;
	while (i < ft_strlen(s2))
	{
		dst[(ft_strlen(s1) + 1) + i] = s2[i];
		i++;
	}
	dst[(ft_strlen(s1) + 1) + i] = '\0';
	return (dst);
}
