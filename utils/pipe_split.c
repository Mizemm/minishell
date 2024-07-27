/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:29:36 by mizem             #+#    #+#             */
/*   Updated: 2024/07/27 22:50:54 by mizem            ###   ########.fr       */
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
    int flag = 0;

    if (!str)
        return 0;

    while (str[i])
    {
        if (str[i] == '"')
            flag = !flag;
        if (flag == 0 && str[i] == c)
		{
            while (str[i] && str[i] == c)
                i++;
        }
		else if (flag == 0)
		{
            while (str[i] && str[i] != c)
			{
				if (str[i] == '"')
					break;
                i++;
			}
			wc++;
        }
		else
            i++;
	}
    return wc;
}


char **ft_split(char *str, char c)
{
	int i;
	int j;
	int start;
	int end;
	char **out;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	if (!str)
		return NULL;
	int wc = count_wc(str, c);
	out = malloc(sizeof(char *) * (wc + 1));
	if (!out)
		return NULL;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] == '"')
        {
            start = i++;
            while (str[i] && str[i] != '"')
                i++;
            end = ++i;
        }
		else
		{
			start = i;
			while (str[i] && str[i] != c)
			{
				i++;
				if (str[i] == '"')
					break;
			}
			end = i;
		}
        while (end > start && str[end - 1] == ' ')
            end--;
		if (start < end)
		{
			out[j] = malloc(sizeof(char) * ((end - start) + 1));
			if (!out)
				return NULL;
			ft_strncpy(out[j], &str[start], (end - start));
			j++;
		}
	}
	out[j] = NULL;
	return out;
}

int main()
{
	printf("<<%d>>\n", count_wc("please \"work | now   \"", '|'));
	char **str = ft_split("please \"work | now   \"", '|');
	int i = 0;
	while (str[i])
	{
		printf("<%s>\n", str[i]);
		i++;
	}
}