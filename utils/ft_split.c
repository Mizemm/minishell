/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:29:36 by mizem             #+#    #+#             */
/*   Updated: 2024/07/22 16:51:21 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strncpy(char *s1, char *s2, int len)
{
	int i = 0;
	while (s2[i] && i < len)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

int count_wc(char *str, char c)
{
	int i = 0;
	int wc = 0;
	if (!str)
		return 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		wc++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (wc);
}
char **ft_split(char *str, char c)
{
	int i = 0;
	int j = 0;
	int start = 0;
	int end = 0;
	if (!str)
		return NULL;
	int wc = count_wc(str, c);
	char **out = malloc(sizeof(char *) * (wc + 1));
	if (!out)
		return NULL;
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
			ft_strncpy(out[j], &str[start], (end - start));
			j++;
		}
	}
	out[j] = NULL;
	return out;
}
