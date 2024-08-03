/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:29:36 by mizem             #+#    #+#             */
/*   Updated: 2024/08/03 16:59:06 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:29:36 by mizem             #+#    #+#             */
/*   Updated: 2024/07/29 21:43:24 by mizem            ###   ########.fr       */
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

void	ft_strncpy(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	while (s2[i] && i < len)
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

int	count_wc(char *str, char c)
{
	int	i;
	int	wc;
	int	flag;

	i = 0;
	wc = 0;
	flag = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '"')
			flag = !flag;
		if (!flag && str[i] == c)
		{
			while (str[i] && str[i] == c)
				i++;
		}
		else
		{
			wc++;
			while (str[i] && (flag || str[i] != c))
			{
				if (str[i] == '"')
					flag = !flag;
				i++;
			}
		}
	}
	return (wc);
}

char	**pipe_split(char *str, char c)
{
	char	**out;
	int		flag;

	int i, j, start, end, wc;
	flag = 0;
	i = 0;
	j = 0;
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
		while (str[i])
		{
			if (str[i] == '"')
				flag = !flag;
			else if (str[i] == c && !flag)
				break ;
			i++;
		}
		end = i;
		if (start < end)
		{
			out[j] = malloc(sizeof(char) * ((end - start) + 1));
			if (!out[j])
				ft_free(out);
			ft_strncpy(out[j], &str[start], (end - start));
			j++;
		}
	}
	out[j] = NULL;
	return (out);
}
