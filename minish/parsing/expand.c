/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:19:35 by mizem             #+#    #+#             */
/*   Updated: 2024/11/01 01:47:19 by abdennac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_value(t_main *main, char *output)
{
	char	*newput;
	t_env	*tmp_env;

	newput = NULL;
	tmp_env = main->env;
	while (main->env)
	{
		if (ft_strcmp(output, main->env->name) == 0)
		{
			newput = ft_strdup(main->env->value);
			main->env = tmp_env;
			return (free(output), newput);
		}
		else
			main->env = main->env->next;
	}
	main->env = tmp_env; 
	return (NULL);
}

char	*expand_1(t_lexer *list, t_main *main, char *result, int *i)
{
	char	*output;
	char	tmp[1024];
	int		j;

	j = 0;
	output = NULL;
	(*i)++;
	if (list->content[(*i)] == '\0')
		return (result = ft_strdup("$"));
	while (list->content[*i] && valid_name(list->content[*i]))
	{
		tmp[j++] = list->content[(*i)];
		(*i)++;
	}
	tmp[j] = '\0';
	output = put_value(main, ft_strdup(tmp));
	result = ft_strjoin(result, output);
	tmp[0] = '\0';
	return (result);
}

char	*expand_2(t_lexer *list, char *result, int *i)
{
	char	*tmp_arr;

	tmp_arr = malloc(2);
	tmp_arr[0] = list->content[(*i)];
	(*i)++;
	tmp_arr[1] = '\0';
	result = ft_strjoin(result, tmp_arr);
	free(tmp_arr);
	tmp_arr = NULL;
	return (result);
}

char	*big_expand(t_lexer *list, t_main *main, char *result, int *flag)
{
	int	i;

	i = 0;
	while (i < ft_strlen(list->content) && list->content[i])
	{
		*flag = 1;
		if (list->content[i] == '$' && (list->content[i + 1] == '?' 
				|| (list->content[i + 1] >= 48 && list->content[i + 1] <= 57)))
		{
			if (list->content[i + 1] == '?')
				result = ft_strjoin(result, ft_itoa(main->exit_status));
			i += 2;
		}
		else if (list->content[i] == '$')
			result = expand_1(list, main, result, &i);
		else
			result = expand_2(list, result, &i);
	}
	return (result);
}

void	expand(t_lexer *list, t_main *main)
{
	char	*result;
	int		flag;

	result = NULL;
	while (list)
	{
		flag = 0;
		if (list->type == ENV && list->state != IN_QUOTE)
		{
			if (valid_condition(list))
			{
				skip_her(&list, result);
				if (!list->next)
					return ;
			}
			result = big_expand(list, main, result, &flag);
			if (flag)
				fill_node(&list, result);
		}
		free(result);
		result = NULL;
		list = list->next;
	}
}
