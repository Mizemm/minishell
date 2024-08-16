/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:49:24 by abdennac          #+#    #+#             */
/*   Updated: 2024/08/15 19:42:53 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *last_arg(t_cmd *list, int i)
{
	char *tmp;
	while (list->args[i] != NULL)
	{
		tmp = list->args[i];
		i++;
	}
	return tmp;
}
int count_ac(char **str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int path_check(char *s)
{
	int i;
	char str[5] = "PATH";

	i = 0;
	while (s[i] && s[i] == str[i])
		i++;
	if (i == 4)
		return (1);
	return (0);
}
char **environment(char *env)
{
	int i;
	char **tmp;

	tmp = NULL;
	i = 0;
	if (env)
		tmp = pipe_split(&env[i], ':');
	return (tmp);
}
char *return_path(char **ev, char *str)
{
	int i;
	char *tmp;

	i = 0;
	while (ev[i])
	{
		tmp = ft_strjoin(ev[i], str);
		if (access(tmp, X_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (0);
}
void redirections(t_cmd *list)
{
	int i = 0;
	while (list->args[i])
	{
		if (ft_strcmp(list->args[i], "<") == 0)
			list->input_file = ft_strdup(last_arg(list, ++i));
		else if (ft_strcmp(list->args[i], ">") == 0)
		{
			list->output_file = ft_strdup(list->args[++i]);
			break;
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

void create(t_cmd *tmp_list, char **str, int ac)
{
	int i;
	
	i = 0;
	tmp_list->args = malloc(sizeof(char *) * (ac + 1));
	while (i < ac)
	{
		tmp_list->args[i] = ft_strdup(str[i]);
		i++;
	}
	tmp_list->args[i] = NULL;
}

t_cmd *create_list(t_cmd *list, char *tokens, char **ev, int flag)
{
	t_cmd	*tmp_list;
	char	**str;
	int		i;

	i = 0;
	str = pipe_split(tokens, ' ');
	tmp_list = malloc(sizeof(t_cmd));
	if (!tmp_list)
		return NULL;
	
	tmp_list->command = NULL;
    tmp_list->path = NULL;
    tmp_list->input_file = NULL;
    tmp_list->output_file = NULL;
    tmp_list->append_file = NULL;
    tmp_list->heredoc_delimiter = NULL;
	tmp_list->pipe_out = 0;
    tmp_list->next = NULL;
	
	tmp_list->command = ft_strdup(str[0]);
	tmp_list->path = return_path(ev, tmp_list->command);
	tmp_list->arg_count = count_ac(str);
	if (flag > 1)
		tmp_list->pipe_out = 1;
	create(tmp_list, str, count_ac(str));
	redirections(tmp_list);	
	ft_lstadd_back(&list, tmp_list);
	return (tmp_list);
}
