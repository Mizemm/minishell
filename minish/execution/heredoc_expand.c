/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:38:04 by mizem             #+#    #+#             */
/*   Updated: 2024/10/30 22:13:16 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_herdoc(char *str, char *result)
{
	free(str);
	str = ft_strdup(result);
}

char	*her_expand_1(char *str, t_main *main, char *result, int *i)
{
	char	*output;
	char	tmp[1024];
	int		j;

	j = 0;
	output = NULL;
	(*i)++;
	while (str[*i] && her_valid_name(str[*i]))
	{
		tmp[j++] = str[(*i)];
		(*i)++;
	}
	tmp[j] = '\0';
	output = put_value(main, ft_strdup(tmp));
	result = ft_strjoin(result, output);
	tmp[0] = '\0';
	return (result);
}

char	*her_expand_2(char *str, char *result, int *i)
{
	char	*tmp_arr;

	tmp_arr = malloc(2);
	tmp_arr[0] = str[(*i)];
	(*i)++;
	tmp_arr[1] = '\0';
	result = ft_strjoin(result, tmp_arr);
	free(tmp_arr);
	tmp_arr = NULL;
	return (result);
}

char	*her_big_expand(char *str, t_main *main, char *result, int *flag)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str) && str[i])
	{
		*flag = 1;
		if (str[i] == '$' && (str[i + 1] == '?' || (str[i + 1] >= 48 && str[i
						+ 1] <= 57)))
		{
			if (str[i + 1] == '?')
				result = ft_strjoin(result, ft_itoa(main->exit_status));
			i += 2;
		}
		else if (str[i] == '$')
			result = her_expand_1(str, main, result, &i);
		else
			result = her_expand_2(str, result, &i);
	}
	return (result);
}

char	*her_expand(char *str, t_main *main)
{
	char	*result;
	char	*out;
	int		flag;

	result = NULL;
	if (str)
	{
		flag = 0;
		result = her_big_expand(str, main, result, &flag);
		if (flag)
		{
			free(str);
			out = ft_strdup(result);
			free(result);
			result = NULL;
			return (out);
		}
	}
	return (str);
}
