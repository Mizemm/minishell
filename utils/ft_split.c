/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:29:36 by mizem             #+#    #+#             */
/*   Updated: 2024/08/31 22:45:27 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_split(char *str, char c)
{
	int		i;
	int		j;
	int		start;
	int		end;
	char	**out;
	int		wc;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	if (!str)
		return (NULL);
	wc = count_wc(str, c);
	out = malloc(sizeof(char *) * (wc + 1));
	if (!out)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		start = i;
		while (str[i] && str[i] != c)
			i++;
		end = i;
		if (start < end)
		{
			out[j] = malloc(sizeof(char) * ((end - start) + 1));
			if (!out)
				return (NULL);
			ft_strncpy(out[j], &str[start], (end - start));
			j++;
		}
	}
	out[j] = NULL;
	return (out);
}
