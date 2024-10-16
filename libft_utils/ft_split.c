/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:19:21 by mizem             #+#    #+#             */
/*   Updated: 2024/10/16 13:49:15 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

int	count_wc(char *str, char c)
{
	int i = 0;
	int wc = 0;
	
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			wc++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (wc);
}
char	**ft_split(char *str, char c)
{
	int i;
	int j;
	int k;
	int wc;
	
	i = 0;
	j = 0;
	k = 0;
	wc = count_wc(str, c);
	char **out = malloc(sizeof(char *) * (wc + 1));
	if (!out)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		j = i;
		while (str[i] && str[i] != c)
			i++;
		if (i > j)
		{
			out[k] = malloc((i - j) + 1);
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}
