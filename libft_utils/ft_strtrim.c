/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:35:42 by mizem             #+#    #+#             */
/*   Updated: 2024/10/30 17:03:09 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

int	ft_start(char *s1, char *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			j++;
		}
		if (set[j] != s1[i])
			return (i);
		i++;
	}
	return (i);
}

int	ft_end(char *s1, char *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1);
	j = 0;
	while (i > 0)
	{
		j = 0;
		while (set[j])
		{
			if (s1[i - 1] == set[j])
				break ;
			j++;
		}
		if (s1[i - 1] != set[j])
			return (i);
		i--;
	}
	return (i);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	int		i;
	char	*dst;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	if (!s1[i])
		return (ft_strdup(""));
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	if (start > end)
		return (ft_strdup(""));
	dst = malloc((end - start + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (start + i < end)
	{
		dst[i] = s1[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
