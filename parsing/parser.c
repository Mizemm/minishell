/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:49:24 by abdennac          #+#    #+#             */
/*   Updated: 2024/09/26 11:28:34 by abdennac         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../minishell.h"

int count_out(t_cmd *list)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while (list->args[i])
	{
		if (ft_strcmp(list->args[i], ">") == 0)
			count++;
		i++;
	}
	return (count);
}

int count_in(t_cmd *list)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while (list->args[i])
	{
		if (ft_strcmp(list->args[i], "<") == 0)
			count++;
		i++;
	}
	return (count);
}

void redirections(t_cmd *list)
{
	int i = 0;
	int j = 0;
	int y = 0;

	while (list->args[i])
	{
		if (ft_strcmp(list->args[i], "<") == 0)
		{
			free(list->args[i]);
			list->args[i] = NULL;
			list->input_file[y] = ft_strdup(last_arg(list, ++i));
			list->input_file[y+1] = NULL;
			free(list->args[i]);
			list->args[i] = NULL;
			y++;
		}
		else if (ft_strcmp(list->args[i], ">") == 0)
		{
			
			free(list->args[i]);
			list->args[i] = NULL;
			list->output_file[j] = ft_strdup(list->args[++i]);
			list->output_file[j + 1] = NULL;
			free(list->args[i]);
			list->args[i] = NULL;
			j++;
		}
		else if (ft_strcmp(list->args[i], ">>") == 0)
		{
			list->append_file = ft_strdup(list->args[++i]);
			break;
		}
		else if (ft_strcmp(list->args[i], "<<") == 0)
		{
			list->heredoc_delimiter = ft_strdup(list->args[++i]);
			break;
		}
		i++;
	}
}

void create_args(t_cmd *list, char **str, int ac)
{
	int i;

	i = 0;
	list->args = malloc(sizeof(char *) * (ac + 1));
	while (i < ac)
	{
		list->args[i] = ft_strdup(str[i]);
		i++;
	}
	list->args[i] = NULL;
}

t_cmd *create_list(t_cmd *list, char *tokens, char **ev, int flag)
{
	t_cmd *tmp_list;
	char **str;
	str = pipe_split(tokens, ' ');
	tmp_list = malloc(sizeof(t_cmd));
	if (!tmp_list)
		return NULL;
	create_args(tmp_list, str, count_ac(str));
	tmp_list->command = NULL;
	tmp_list->path = NULL;
	tmp_list->input_file = NULL;
	tmp_list->output_file = NULL;
	if (count_out(tmp_list) > 0)
		tmp_list->output_file = malloc(sizeof(char *) * (count_out(tmp_list) + 1));
	if (count_in(tmp_list) > 0)
		tmp_list->input_file = malloc(sizeof(char *) * (count_in(tmp_list) + 1));
	tmp_list->append_file = NULL;
	tmp_list->heredoc_delimiter = NULL;
	tmp_list->heredoc_content = NULL;
	tmp_list->pipe_out = 0;
	tmp_list->next = NULL;

	tmp_list->arg_count = count_ac(str);
	tmp_list->command = ft_strdup(str[0]);
	tmp_list->path = return_path(ev, tmp_list->command);
	if (flag > 1)
		tmp_list->pipe_out = 1;
	redirections(tmp_list);
	ft_lstadd_back(&list, tmp_list);
	return (list);
}


