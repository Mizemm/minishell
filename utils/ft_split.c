/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:29:36 by mizem             #+#    #+#             */
/*   Updated: 2024/07/20 12:51:15 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int wc = count_wc(str, c);
	char **out = malloc(sizeof(char *) * (wc + 1));
	if (!out || !str)
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
