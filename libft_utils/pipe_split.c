/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:29:36 by mizem             #+#    #+#             */
/*   Updated: 2024/09/25 17:50:49 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

int	mini_count(char *str, char c, int i, int flag)
{
	int	wc;

	wc = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
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
				if (str[i] == '"' || str[i] == 39)
					flag = !flag;
				i++;
			}
		}
	}
	return (wc);
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
	wc = mini_count(str, c, i, flag);
	return (wc);
}

int	allocate_out(char **out, char *str, int start, int end)
{
	if (start < end)
	{
		*out = malloc(sizeof(char) * ((end - start) + 1));
		if (!*out)
			ft_free(out);
		ft_strncpy(*out, &str[start], (end - start));
		return (1);
	}
	else
		return (0);
}

void	mini_split(char **out, char *str, char c, int i)
{
	int	start;
	int	end;
	int	flag;

	flag = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		start = i;
		while (str[i])
		{
			if (str[i] == '"' || str[i] == 39)
				flag = !flag;
			else if (str[i] == c && !flag)
				break ;
			i++;
		}
		end = i;
		if (allocate_out(out, str, start, end))
			out++;
	}
	*out = NULL;
}

char	**pipe_split(char *str, char c)
{
	char	**out;
	int		i;
	int		wc;

	i = 0;
	if (!str)
		return (NULL);
	wc = count_wc(str, c);
	out = malloc(sizeof(char *) * (wc + 1));
	if (!out)
		return (NULL);
	mini_split(out, str, c, i);
	return (out);
}
