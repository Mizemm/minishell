/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 02:49:24 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/06 23:35:57 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_args(t_lexer *list)
{
	int wc;

	wc = 0;
	while(list && list->type != PIPE_LINE)
	{
		if (list->type == WHITE_SPACE)
			list = list->next;
		else if (list->type == REDIR_IN || list->type == REDIR_OUT || list->type == APPEND || list->type == HERE_DOC)
		{
			while (list && list->type != WORD && list->type != ENV)
				list = list->next;
			list = list->next;
		}
		else
		{
			wc++;
			list = list->next;
		}
	}
	return (wc);
}
int count_redir_out(t_lexer *list)
{
	int wc;

	wc = 0;
	while(list && list->type != PIPE_LINE)
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
	while(list && list->type != PIPE_LINE)
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
	while(list && list->type != PIPE_LINE)
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
	while(list && list->type != PIPE_LINE)
	{
		if (list->type == APPEND)
			wc++;
		list = list->next;
	}
	return (wc);
}

t_cmd *create_args(t_lexer **lexer, char **ev)
{
	t_cmd *tmp_list;
	int arg;
	int in;
	int out;
	int app;
	int her;
	
	tmp_list = malloc(sizeof(t_cmd));
	if (!tmp_list)
		return NULL;
	tmp_list->command = NULL;
	tmp_list->path = NULL;
	tmp_list->args = NULL;
	tmp_list->arg_count = count_args((*lexer));
	tmp_list->input_file = NULL;
	tmp_list->output_file = NULL;
	tmp_list->append_file = NULL;
	tmp_list->heredoc_delimiter = NULL;
	tmp_list->heredoc_content = NULL;
	tmp_list->pipe_out = 0;
	tmp_list->next = NULL;
	arg = 0;
	in = 0;
	out = 0;
	app = 0;
	her = 0;
	
	if (count_args((*lexer)) > 0)
		tmp_list->args = malloc(sizeof(char *) * (count_args((*lexer)) + 1));
	if (count_redir_in((*lexer)) > 0)
		tmp_list->input_file = malloc(sizeof(char *) * (count_redir_in((*lexer)) + 1));
	if (count_redir_out((*lexer)) > 0)
		tmp_list->output_file = malloc(sizeof(char *) * (count_redir_out((*lexer)) + 1));
	if (count_append((*lexer)) > 0)
		tmp_list->append_file = malloc(sizeof(char *) * (count_append((*lexer)) + 1));
	if (count_her((*lexer)) > 0)
		tmp_list->heredoc_delimiter = malloc(sizeof(char *) * (count_her((*lexer)) + 1));
	while ((*lexer) && (*lexer)->type != PIPE_LINE)
	{
		if ((*lexer)->type == WHITE_SPACE)
			(*lexer) = (*lexer)->next;
		else if ((*lexer)->type == REDIR_IN)
		{
			while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
				(*lexer) = (*lexer)->next;
			tmp_list->input_file[in++] = ft_strdup((*lexer)->content);
			tmp_list->input_file[in] = NULL;
			(*lexer) = (*lexer)->next;
		}
		else if ((*lexer)->type == REDIR_OUT)
		{
			while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
					(*lexer) = (*lexer)->next;
			tmp_list->output_file[out++] = ft_strdup((*lexer)->content);
			tmp_list->output_file[out] = NULL;
			(*lexer) = (*lexer)->next;
		}
		else if ((*lexer)->type == APPEND)
		{
			while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
				(*lexer) = (*lexer)->next;
			tmp_list->append_file[app++] = ft_strdup((*lexer)->content);
			tmp_list->append_file[app] = NULL;
			(*lexer) = (*lexer)->next;
		}
		else if ((*lexer)->type == HERE_DOC)
		{
			while ((*lexer) && (*lexer)->type != WORD && (*lexer)->type != ENV)
				(*lexer) = (*lexer)->next;
			tmp_list->heredoc_delimiter[her++] = ft_strdup((*lexer)->content);
			tmp_list->heredoc_delimiter[her] = NULL;
			(*lexer) = (*lexer)->next;
		}
		else
		{
			tmp_list->args[arg++] = ft_strdup((*lexer)->content);
			tmp_list->args[arg] = NULL;
			(*lexer) = (*lexer)->next;
		}
	}
	tmp_list->command = ft_strdup(tmp_list->args[0]);
	tmp_list->path = return_path(ev, tmp_list->command);
	if ((*lexer) && (*lexer)->type == PIPE_LINE)
		tmp_list->pipe_out = 1;
	return (tmp_list);
}

t_cmd *create_list(t_cmd *list, t_lexer *lexer, char **ev)
{
	while (lexer && lexer->type != PIPE_LINE)
	{
		ft_lstadd_back(&list, create_args(&lexer, ev));
		if (lexer == NULL)
			break;
		lexer = lexer->next;
	}
	// ft_free(ev);
	return (list);
}
