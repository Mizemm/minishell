/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:49:24 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/05 17:14:35 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_args(t_lexer *list)
{
	int wc;

	wc = 0;
	while(list)
	{
		if (list->type != REDIR_OUT && list->type != REDIR_IN && list->type != HERE_DOC && list->type != APPEND && list->type != PIPE_LINE && list->type != WHITE_SPACE)
			wc++;
		list = list->next;
	}
	return (wc);
}
int count_redir_out(t_lexer *list)
{
	int wc;

	wc = 0;
	while(list)
	{
		if (list->type == REDIR_OUT)
			wc++;
		list = list->next;
	}
	return (wc);
}
int count_redir_in(t_lexer *list)
{
	int wc;

	wc = 0;
	while(list)
	{
		if (list->type == REDIR_IN)
			wc++;
		list = list->next;
	}
	return (wc);
}
int count_her(t_lexer *list)
{
	int wc;

	wc = 0;
	while(list)
	{
		if (list->type == HERE_DOC)
			wc++;
		list = list->next;
	}
	return (wc);
}
int count_append(t_lexer *list)
{
	int wc;

	wc = 0;
	while(list)
	{
		if (list->type == APPEND)
			wc++;
		list = list->next;
	}
	return (wc);
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

// t_cmd *create_list(t_cmd *list, t_lexer *lexer, char **ev)
// {
// 	t_cmd *tmp_list;
// 	tmp_list = malloc(sizeof(t_cmd));
// 	if (!tmp_list)
// 		return NULL;
// 	create_args(tmp_list , count_ac(str));
// 	tmp_list->command = NULL;
// 	tmp_list->path = NULL;
// 	tmp_list->input_file = NULL;
// 	tmp_list->output_file = NULL;
// 	if (count_out(tmp_list) > 0)
// 		tmp_list->output_file = malloc(sizeof(char *) * (count_out(tmp_list) + 1));
// 	if (count_in(tmp_list) > 0)
// 		tmp_list->input_file = malloc(sizeof(char *) * (count_in(tmp_list) + 1));
// 	tmp_list->append_file = NULL;
// 	tmp_list->heredoc_delimiter = NULL;
// 	tmp_list->heredoc_content = NULL;
// 	tmp_list->pipe_out = 0;
// 	tmp_list->next = NULL;

// 	tmp_list->arg_count = count_ac(str);
// 	tmp_list->command = ft_strdup(str[0]);
// 	tmp_list->path = return_path(ev, tmp_list->command);
// 	if (flag > 1)
// 		tmp_list->pipe_out = 1;
// 	redirections(tmp_list);
// 	ft_lstadd_back(&list, tmp_list);
// 	dp_free(ev);
// 	dp_free(str);
// 	free(tokens);
// 	return (list);
// }
