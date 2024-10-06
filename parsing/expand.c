/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 22:19:35 by mizem             #+#    #+#             */
/*   Updated: 2024/10/06 23:33:15 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*put_value(t_main *main, char *output)
{
	char *newput;
	t_env *tmp_env = main->env;
	
	newput = NULL;
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

int valid_name(char c)
{
	if((c >= 48 && c <= 58) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '_')
		return 1;
	return 0;
}
int heredoc_breakers(char c)
{
	if(c == '>' || c == '<' || c == '\t' || c == ' ')
		return 1;
	return 0;
}
char	*expand_1(t_lexer *list, t_main *main, char *result, int *i)
{
	char *output;
	char tmp[1024];
	int j;
	
	j = 0;
	output = NULL;
	(*i)++;
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
	char *tmp_arr;
	tmp_arr = malloc(2);
	tmp_arr[0] = list->content[(*i)];
	(*i)++;
	tmp_arr[1] = '\0';
	result = ft_strjoin(result, tmp_arr);
	free(tmp_arr);
	tmp_arr = NULL;
	return (result);
}
void	fill_node(t_lexer **list, char *result)
{
	free((*list)->content);
	(*list)->content = ft_strdup(result);
	// free(result);
	// result = NULL;
}
void	expand(t_lexer *list, t_main *main)
{
	char *result;
	int i;
	int flag;
	
	i = 0;
	result = NULL;
	while (list)
	{
		flag = 0;
		if (list->type == ENV && list->state != IN_QUOTE)
		{
			if (list->prev && list->prev->prev && (list->prev->type == HERE_DOC || (list->prev->prev->type == HERE_DOC && list->prev->type == WHITE_SPACE)))
			{
				while(heredoc_breakers(list->content[0]) != 1 && list->next)
					list = list->next;
				if (!list->next)
				{
					free(result);
					return ;
				}
			}
			i = 0;
			while (i < ft_strlen(list->content) && list->content[i])
			{
				flag = 1;
				if (list->content[i] == '$')
					result = expand_1(list, main, result, &i);
				else
					result = expand_2(list, result, &i);
			}
			if (flag)
				fill_node(&list, result);
		}
		free(result);
		result = NULL;
		list = list->next;
	}
}
